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
#define PLAYER_RADIUS	(36.0f)
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)
#define PLAYER_MOVE_SPEED (3.0f)
#define PLAYER_WIDTH (20)
#define PLAYER_HEIGHT (44)

// ジャンプ力
#define PLAYER_JUMP_POWER (12.0f)
// 重力
#define PLAYER_GRAVITY (0.4f)

// 描画位置補正
#define PLAYER_DRAW_OFFSET_X (-24)
#define PLAYER_DRAW_OFFSET_Y (-20)
// 落下判定になるY移動量
#define PLAYER_FALL_Y_MOVE (PLAYER_GRAVITY * 3.0f)
// キャラクターの周囲何マスまでチェックするか
#define PLAYER_CHECK_ROUND_NUM (2)

PlayerData g_PlayerData = { 0 };

// このCPPでのみ使用する関数の宣言
void StartPlayerAnimation(PlayerAnimationType anim);	// アニメーション再生
void UpdatePlayerAnimation();							// アニメーション更新

void InitPlayer()
{
	g_PlayerData.active = false;
	g_PlayerData.body = {};
	g_PlayerData.playAnim = PLAYER_ANIM_NONE;

	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		InitAnimation(&g_PlayerData.animation[i]);
	}
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

	// 初期位置
	g_PlayerData.body.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.body.posY = PLAYER_DEFAULT_POS_Y;

	// サイズ
	g_PlayerData.body.width = PLAYER_WIDTH;
	g_PlayerData.body.height = PLAYER_HEIGHT;

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

	// X移動量は毎回リセットする
	g_PlayerData.body.moveX = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.body.moveY += PLAYER_GRAVITY;

	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.body.moveX = -PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = true;
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.body.moveX = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;
	}

	// Z入力
	if (IsTriggerKey(KEY_Z))
	{
		g_PlayerData.body.moveY = -PLAYER_JUMP_POWER;
	}
}

void UpdatePlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 当たり判定付き移動
	MoveWithMapCollision(&g_PlayerData.body, PLAYER_CHECK_ROUND_NUM);

	// 坂の当たり判定
	SlopeCollision(&g_PlayerData.body, PLAYER_CHECK_ROUND_NUM);

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_PlayerData.body.moveY < 0.0f || g_PlayerData.body.moveY > PLAYER_FALL_Y_MOVE)
	{
		g_PlayerData.body.isAir = true;
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

	// 画像の余白が大きいため位置調整が必要
	int x = (int)(g_PlayerData.body.posX + PLAYER_DRAW_OFFSET_X - camera.posX);
	int y = (int)(g_PlayerData.body.posY + PLAYER_DRAW_OFFSET_Y - camera.posY);

	// アニメーション描画でプレイヤーを描画する
	PlayerAnimationType animType = g_PlayerData.playAnim;
	AnimationData* animData = &g_PlayerData.animation[animType];
	DrawAnimation(animData, x, y, g_PlayerData.isTurn);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "プレイヤーの座標＝[%f, %f]", g_PlayerData.body.posX, g_PlayerData.body.posY);
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
	StartAnimation(animData, g_PlayerData.body.posX, g_PlayerData.body.posY, animParam.interval, animParam.frameNum, animParam.width, animParam.height, true);
}

void UpdatePlayerAnimation()
{
	// 地上にいるか
	if (!g_PlayerData.body.isAir)
	{
		// 横に移動していれば走っている
		if (g_PlayerData.body.moveX < 0.0f || g_PlayerData.body.moveX > 0.0f)
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
		if (g_PlayerData.body.moveY < 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_JUMP);
		}
		// 下降していれば落下アニメーション
		else if (g_PlayerData.body.moveY > 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_FALL);
		}
	}

	// アニメーション更新
	PlayerAnimationType animType = g_PlayerData.playAnim;
	AnimationData* animData = &g_PlayerData.animation[animType];
	UpdateAnimation(animData);
}
