#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Camera/Camera.h"
#include "../Map/MapManager.h"

// アニメーション用パラメータ
struct PlayerAnimationParam
{
	int interval;
	int frameNum;
	int width;
	int height;
};
const PlayerAnimationParam PLAYER_ANIM_PARAM[PLAYER_ANIM_MAX] =
{
	8, 4, 72, 72,
	5, 8, 72, 72,
	8, 2, 72, 72,
	8, 2, 72, 72,
	8, 1, 72, 72,
};

// プレイヤー設定関連
#define PLAYER_WIDTH	(72.0f)
#define PLAYER_HEIGHT	(72.0f)
#define PLAYER_RADIUS	(36.0f)
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)
#define PLAYER_MOVE_SPEED (3.0f)

// ジャンプ力
#define PLAYER_JUMP_POWER (12.0f)
// 重力
#define PLAYER_GRAVITY (0.4f)

// マップ衝突判定用のプレイヤーサイズ補正
#define PLAYER_MAP_COLLISION_OFFSET (0.05f)
// 矩形判定の位置補正
#define PLAYER_BOX_COLLISION_OFFSET_X (24)
#define PLAYER_BOX_COLLISION_OFFSET_Y (20)
// 矩形判定のサイズ
#define PLAYER_BOX_COLLISION_WIDTH (20)
#define PLAYER_BOX_COLLISION_HEIGHT (44)
// 坂の吸い寄せ範囲
#define PLAYER_SLOPE_ATTRACTION (14.0f)
// 落下判定になるY移動量
#define PLAYER_FALL_Y_MOVE (PLAYER_GRAVITY * 3.0f)
// キャラクターの周囲何マスまでチェックするか
#define PLAYER_CHECK_ROUND_NUM (2)

PlayerData g_PlayerData = { 0 };
PlayerData g_PrevPlayerData = { 0 };
BoxCollision g_Collision = { 0 };

// このCPPでのみ使用する関数の宣言
void StartPlayerAnimation(PlayerAnimationType anim);	// アニメーション再生
void UpdatePlayerAnimation();							// アニメーション更新

// 当たり判定付き移動
void MoveWithCollision();

// 当たり判定後の押し出し処理
bool ResolveCollision();
void PushNormalBlockX(float x, float w, float hitX);
void PushNormalBlockY(float y, float h, float hitY);
void PushNormalSlopeX(float x, float w, float hitX);
void PushNormalSlopeY(float x, float y, float w, float h, float hitX, float hitY);

// 着地処理
void LadingPlayer();

void InitPlayer()
{
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.active = false;
	g_PlayerData.playAnim = PLAYER_ANIM_NONE;

	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		InitAnimation(&g_PlayerData.animation[i]);
	}

	// 構造体はmemsetで0初期化できる
	memset(&g_PlayerData.boxCollision, 0, sizeof(g_PlayerData.boxCollision));
}

void LoadPlayer()
{
	g_PlayerData.animation[PLAYER_ANIM_IDLE].handle = LoadGraph("Data/Player/PlayerIdle.png");
	g_PlayerData.animation[PLAYER_ANIM_RUN].handle = LoadGraph("Data/Player/PlayerRun.png");
	g_PlayerData.animation[PLAYER_ANIM_JUMP].handle = LoadGraph("Data/Player/PlayerJump.png");
	g_PlayerData.animation[PLAYER_ANIM_FALL].handle = LoadGraph("Data/Player/PlayerFall.png");
	g_PlayerData.animation[PLAYER_ANIM_LANDING].handle = LoadGraph("Data/Player/PlayerLanding.png");
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;

	// 矩形判定設定
	g_PlayerData.boxCollision.posX = g_PlayerData.posX + PLAYER_BOX_COLLISION_OFFSET_X;
	g_PlayerData.boxCollision.posY = g_PlayerData.posY + PLAYER_BOX_COLLISION_OFFSET_Y;
	g_PlayerData.boxCollision.width = PLAYER_BOX_COLLISION_WIDTH;
	g_PlayerData.boxCollision.height = PLAYER_BOX_COLLISION_HEIGHT;

	// 待機アニメーションから開始する
	StartPlayerAnimation(PLAYER_ANIM_IDLE);
}

void StepPlayer()
{
	// 死んでいたら何もしない
	if (!g_PlayerData.active)
	{
		return;
	}

	// 前回のデータとして記憶	
	g_PrevPlayerData = g_PlayerData;

	// X移動量は毎回リセットする
	g_PlayerData.moveX = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.moveY += PLAYER_GRAVITY;

	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = true;
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;
	}

	// Z入力
	if (IsTriggerKey(KEY_Z))
	{
		g_PlayerData.moveY = -PLAYER_JUMP_POWER;
	}
}

void UpdatePlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 当たり判定付き移動
	MoveWithCollision();

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_PlayerData.moveY < 0.0f || g_PlayerData.moveY > PLAYER_FALL_Y_MOVE)
	{
		g_PlayerData.isAir = true;
	}

	// まだ当たってるかもしれないので
	// 何回か当たり判定と押し出しをやる
	bool isHit = ResolveCollision();
	for (int i = 0; i < 2 && isHit == true; i++)
	{
		isHit = ResolveCollision();
	}

	// アニメーション更新
	UpdatePlayerAnimation();
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// カメラ取得
	CameraData camera = GetCamera();

	// アニメーション描画でプレイヤーを描画する
	PlayerAnimationType animType = g_PlayerData.playAnim;
	AnimationData* animData = &g_PlayerData.animation[animType];
	DrawAnimation(animData, g_PlayerData.posX - camera.posX, g_PlayerData.posY - camera.posY, g_PlayerData.isTurn);

	// 当たり判定を描画
	//float x, y, w, h;
	//CalcBoxCollision(g_PlayerData, x, y, w, h);
	//DrawBox((int)(x - camera.posX), (int)(y - camera.posY), (int)(x + w - camera.posX), (int)(y + h - camera.posY), GetColor(255, 255, 255), false);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "プレイヤーの座標＝[%f, %f]", g_PlayerData.posX, g_PlayerData.posY);
}

void FinPlayer()
{
	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		DeleteGraph(g_PlayerData.animation[i].handle);
	}
}

PlayerData GetPlayer()
{
	return g_PlayerData;
}

void StartPlayerAnimation(PlayerAnimationType anim)
{
	// 再生中のアニメーションであれば何もしない
	if (anim == g_PlayerData.playAnim) return;

	// 再生中アニメーション設定
	g_PlayerData.playAnim = anim;

	// 再生に必要なデータを取得
	AnimationData* animData = &g_PlayerData.animation[anim];
	PlayerAnimationParam animParam = PLAYER_ANIM_PARAM[anim];

	// アニメーション再生
	StartAnimation(animData, g_PlayerData.posX, g_PlayerData.posY, animParam.interval, animParam.frameNum, animParam.width, animParam.height, true);
}

void UpdatePlayerAnimation()
{
	// 地上にいるか
	if (!g_PlayerData.isAir)
	{
		// 横に移動していれば走っている
		if (g_PlayerData.moveX < 0.0f || g_PlayerData.moveX > 0.0f)
		{
			// 走るアニメーション
			StartPlayerAnimation(PLAYER_ANIM_RUN);
		}
		else
		{
			// 移動していなければ待機
			StartPlayerAnimation(PLAYER_ANIM_IDLE);
		}
	}
	// 空中にいる
	else
	{
		// 上昇していればジャンプアニメーション
		if (g_PlayerData.moveY < 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_JUMP);
		}
		// 下降していれば落下アニメーション
		else if (g_PlayerData.moveY > 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_FALL);
		}
	}

	// アニメーション更新
	PlayerAnimationType animType = g_PlayerData.playAnim;
	AnimationData* animData = &g_PlayerData.animation[animType];
	UpdateAnimation(animData);
}

void LadingPlayer()
{
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.isAir = false;
}

void MoveWithCollision()
{
	// CheckMapCollision関数を呼ぶとこれらの変数に値が入る
	float hitX = 0, hitY = 0;
	int hitType = 0;

	// 当たり判定ボックスの位置をプレイヤーの位置に揃える
	g_PlayerData.boxCollision.posX = g_PlayerData.posX + PLAYER_BOX_COLLISION_OFFSET_X;
	g_PlayerData.boxCollision.posY = g_PlayerData.posY + PLAYER_BOX_COLLISION_OFFSET_Y;

	// X軸だけプレイヤーと当たり判定ボックスを移動させる
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.boxCollision.posX += g_PlayerData.moveX;

	// わかりやすく変数にする
	float x = g_PlayerData.boxCollision.posX;
	float y = g_PlayerData.boxCollision.posY;
	float w = g_PlayerData.boxCollision.width;
	float h = g_PlayerData.boxCollision.height;

	// マップと当たり判定
	if (CheckMapCollision(x, y, w, h, PLAYER_CHECK_ROUND_NUM, hitX, hitY, hitType))
	{
		switch (hitType)
		{
			case NORMAL_BLOCK: PushNormalBlockX(x, w, hitX);
			case SLOPE_BLOCK:  PushNormalSlopeX(x, w, hitX);
		}
	}

	// 当たり判定ボックスの位置をプレイヤーの位置に揃える
	g_PlayerData.boxCollision.posX = g_PlayerData.posX + PLAYER_BOX_COLLISION_OFFSET_X;

	// Y軸だけプレイヤーと当たり判定ボックスを移動させる
	g_PlayerData.posY += g_PlayerData.moveY;
	// ボックス判定位置計算
	g_PlayerData.boxCollision.posY += g_PlayerData.moveY;

	// わかりやすく変数にする
	x = g_PlayerData.boxCollision.posX;
	y = g_PlayerData.boxCollision.posY;
	w = g_PlayerData.boxCollision.width;
	h = g_PlayerData.boxCollision.height;

	// マップと当たり判定
	if (CheckMapCollision(x, y, w, h, PLAYER_CHECK_ROUND_NUM, hitX, hitY, hitType))
	{
		switch (hitType)
		{
			case NORMAL_BLOCK: PushNormalBlockY(y, h, hitY);
			case SLOPE_BLOCK:  PushNormalSlopeY(x, y, w, h, hitX, hitY);
		}
	}
}

bool ResolveCollision()
{
	bool isHit = false;

	// CheckMapCollision関数を呼ぶとこれらの変数に値が入る
	float hitX = 0, hitY = 0;
	int hitType = 0;

	// 当たり判定ボックスの位置をプレイヤーの位置に揃える
	g_PlayerData.boxCollision.posX = g_PlayerData.posX + PLAYER_BOX_COLLISION_OFFSET_X;
	g_PlayerData.boxCollision.posY = g_PlayerData.posY + PLAYER_BOX_COLLISION_OFFSET_Y;

	// わかりやすく変数にする
	float x = g_PlayerData.boxCollision.posX;
	float y = g_PlayerData.boxCollision.posY;
	float w = g_PlayerData.boxCollision.width;
	float h = g_PlayerData.boxCollision.height;

	// マップと当たり判定
	if (CheckMapCollision(x, y, w, h, PLAYER_CHECK_ROUND_NUM, hitX, hitY, hitType))
	{
		switch (hitType)
		{
		case NORMAL_BLOCK: PushNormalBlockX(x, w, hitX);
		case SLOPE_BLOCK:  PushNormalSlopeX(x, w, hitX);
		}

		isHit = true;
	}

	// 当たり判定ボックスの位置をプレイヤーの位置に揃える
	g_PlayerData.boxCollision.posX = g_PlayerData.posX + PLAYER_BOX_COLLISION_OFFSET_X;

	// わかりやすく変数にする
	x = g_PlayerData.boxCollision.posX;
	y = g_PlayerData.boxCollision.posY;
	w = g_PlayerData.boxCollision.width;
	h = g_PlayerData.boxCollision.height;

	// マップと当たり判定
	if (CheckMapCollision(x, y, w, h, PLAYER_CHECK_ROUND_NUM, hitX, hitY, hitType))
	{
		switch (hitType)
		{
		case NORMAL_BLOCK: PushNormalBlockY(y, h, hitY);
		case SLOPE_BLOCK:  PushNormalSlopeY(x, y, w, h, hitX, hitY);
		}

		isHit = true;
	}

	return isHit;
}

void PushNormalBlockX(float x, float w, float hitX)
{
	// 左からあたったか
	if (g_PlayerData.moveX > 0.0f)
	{
		// 左に押し出す
		g_PlayerData.posX -= (x + w) - hitX;
	}
	// 右からあたったか
	else if (g_PlayerData.moveX < 0.0f)
	{
		// 右に押し出す
		g_PlayerData.posX += (hitX + MAP_CHIP_WIDTH) - x;
	}

	// 移動量は0にする
	g_PlayerData.moveX = 0.0f;
}

void PushNormalBlockY(float y, float h, float hitY)
{
	// 上からあたったか
	if (g_PlayerData.moveY > 0.0f)
	{
		// 上に押し出す
		g_PlayerData.posY -= (y + h) - hitY;
		// 着地
		LadingPlayer();
	}
	// 下からあたったか
	else if (g_PlayerData.moveY < 0.0f)
	{
		// 下に押し出す
		g_PlayerData.posY += (hitY + MAP_CHIP_HEIGHT) - y;
		// 移動量は0にする
		g_PlayerData.moveY = 0.0f;
	}
}

void PushNormalSlopeX(float x, float w, float hitX)
{
}

void PushNormalSlopeY(float x, float y, float w, float h, float hitX, float hitY)
{
	// 上からあたったか
	if (g_PlayerData.moveY > 0.0f)
	{
		// 坂道の始点（左側）
		float startX = hitX;
		float startY = hitY + MAP_CHIP_HEIGHT;
		// 坂道の終点（右側）
		float endX = hitX + MAP_CHIP_WIDTH;
		float endY = hitY;
		// プレイヤーの足先のX座標
		float playerFootX = x + w;
		// プレイヤーの足先座標は坂の端を超えてはいけない
		if (playerFootX < hitX) playerFootX = hitX;
		if (playerFootX > (hitX + MAP_CHIP_WIDTH)) playerFootX = (hitX + MAP_CHIP_WIDTH);

		// ① 傾きの値は「Yの増加量 / Xの増加量」


		// ② 始点の値と傾きの値を使って切片を計算する


		// ③ プレイヤーのX座標の中心から坂道の高さ(Y座標を計算する)
		float slopeY = 0.0f;

		// 坂の高さからある程度上から吸い寄せないと、下るときに浮いてしまう
		if ((y + h) >= (slopeY - PLAYER_SLOPE_ATTRACTION))
		{
			// 着地
			LadingPlayer();

			// 坂とめり込んでいる分だけ上へ移動
			g_PlayerData.posY -= (y + h) - slopeY;
		}
	}
}

