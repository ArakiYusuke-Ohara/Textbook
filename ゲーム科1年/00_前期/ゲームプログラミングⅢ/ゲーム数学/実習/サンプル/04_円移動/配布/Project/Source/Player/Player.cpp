#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Camera/Camera.h"


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
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)
#define PLAYER_MOVE_SPEED (4.0f)

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
#define PLAYER_SLOPE_ATTRACTION (8.0f)
// 落下判定になるY移動量
#define PLAYER_FALL_Y_MOVE (PLAYER_GRAVITY * 3.0f)

PlayerData g_PlayerData = { 0 };
PlayerData g_PrevPlayerData = { 0 };

// このCPPでのみ使用する関数の宣言
void StartPlayerAnimation(PlayerAnimationType anim);	// アニメーション再生
void UpdatePlayerAnimation();							// アニメーション更新
// 当たり判定ボックス情報を計算する
void CalcBoxCollision(PlayerData player, float& x, float& y, float& w, float& h);
// 着地処理
void LandingPlayer();
// 押し出し処理
bool PlayerPushOutX(float targetX, float targetY, float targetW, float targetH, bool checkRight, bool checkLeft);
bool PlayerPushOutY(float targetX, float targetY, float targetW, float targetH, float attract = 0.0f);
// 状態処理
void SetState(PlayerState state);
void ReleaseState(PlayerState state);
bool IsState(PlayerState state);

void InitPlayer()
{
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.state = 0;
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
	g_PlayerData.boxCollision.posX = PLAYER_BOX_COLLISION_OFFSET_X;
	g_PlayerData.boxCollision.posY = PLAYER_BOX_COLLISION_OFFSET_Y;
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
		SetState(PLAYER_RUN);
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;
		SetState(PLAYER_RUN);
	}
	else
	{
		ReleaseState(PLAYER_RUN);
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

	// 上昇している
	if (g_PlayerData.moveY < 0.0f)
	{
		SetState(PLAYER_AIR);
		ReleaseState(PLAYER_FALL);
	}
	// 落ちている
	else if (g_PlayerData.moveY > PLAYER_FALL_Y_MOVE)
	{
		SetState(PLAYER_AIR);
		SetState(PLAYER_FALL);
	}

	// 移動処理
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;

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

void SetState(PlayerState state)
{
	g_PlayerData.state |= state;
}

void ReleaseState(PlayerState state)
{
	g_PlayerData.state &= ~state;
}

bool IsState(PlayerState state)
{
	return g_PlayerData.state & state;
}


bool PlayerPushOutX(float targetX, float targetY, float targetW, float targetH, bool checkRight, bool checkLeft)
{
	bool isHit = false;

	PlayerData player = g_PlayerData;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	// ターンフラグは前回のものにしないと反転した分ずれる
	player.isTurn = g_PrevPlayerData.isTurn;

	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(player, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		targetX, targetY, targetW, targetH))
	{
		isHit = true;

		// 左からあたったか
		if (checkLeft && player.moveX > 0.0f)
		{
			// 左に押し出す
			g_PlayerData.posX -= (x + w) - targetX;
		}
		// 右からあたったか
		else if (checkRight && player.moveX < 0.0f)
		{
			// 右に押し出す
			g_PlayerData.posX += (targetX + targetW) - x;
		}
	}

	return isHit;
}

bool PlayerPushOutY(float targetX, float targetY, float targetW, float targetH, float attract)
{
	bool isHit = false;

	PlayerData player = g_PlayerData;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	// X移動を戻し、縦に当たっているかチェック
	player.posX = g_PrevPlayerData.posX;
	player.posY = g_PlayerData.posY;

	// ターンフラグは前回のものにしないと反転した分ずれる
	player.isTurn = g_PrevPlayerData.isTurn;

	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(player, x, y, w, h);

	// まだ当たっているなら縦に当たっている
	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		targetX, targetY - attract, targetW, targetH + attract))
	{
		isHit = true;

		// 上からあたったか
		if ((y + h) >= targetY - attract && (y + h) <= (targetY + targetH + attract))
		{
			// 着地
			LandingPlayer();
			// 上に押し出す
			g_PlayerData.posY -= (y + h) - targetY;
			ReleaseState(PLAYER_AIR);
		}
		// 下からあたったか
		else if (y >= targetY && y <= (targetY + targetH))
		{
			// 下に押し出す
			g_PlayerData.posY += (targetY + targetH) - y;

			// 落下中でなければY移動量を0にする
			if (!IsState(PLAYER_FALL))
			{
				g_PlayerData.moveY = 0.0f;
				SetState(PLAYER_FALL);
			}
		}
	}

	return isHit;
}

void PlayerHitNormalBlockX(MapChipData mapChipData, bool checkRight, bool checkLeft)
{
	BlockData* block = mapChipData.data;
	PlayerPushOutX(block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, checkRight, checkLeft);
}

void PlayerHitNormalBlockY(MapChipData mapChipData)
{
	BlockData* block = mapChipData.data;
	PlayerPushOutY(block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT);
}

void PlayerHitSlopeBlockX(MapChipData mapChipData)
{
	// 右側から当たったかだけチェックする
	PlayerHitNormalBlockX(mapChipData, false, false);
}

void PlayerHitSlopeBlockY(MapChipData mapChipData)
{
	PlayerData player = g_PlayerData;

	// X移動を戻し、縦に当たっているかチェック
	player.posX = g_PrevPlayerData.posX;
	player.posY = g_PlayerData.posY;

	// ターンフラグは前回のものにしないと反転した分ずれる
	player.isTurn = g_PrevPlayerData.isTurn;

	// ボックスコリジョンの座標と幅を計算する
	float x, y, w, h;
	CalcBoxCollision(player, x, y, w, h);

	// 坂道の始点（左側）
	float startX = mapChipData.data->pos.x;
	float startY = mapChipData.data->pos.y + MAP_CHIP_HEIGHT;
	// 坂道の終点（右側）
	float endX = mapChipData.data->pos.x + MAP_CHIP_WIDTH;
	float endY = mapChipData.data->pos.y;
	// プレイヤーの足元のX座標
	float playerFootX = x + w;

	// プレイヤーが坂道上にいなければ何もしない
	if (playerFootX < startX || playerFootX > endX) return;

	// 傾きの値は「Xの増加量 / Yの増加量」
	float a = (endX - startX) / (endY - startY);

	// 始点の値と傾きの値を使って切片を計算する
	float b = startY - a * startX;

	// プレイヤーのX座標の中心から坂道の高さ(Y座標を計算する)
	float slopeY = a * playerFootX + b;

	// 坂の高さからある程度上から吸い寄せないと、下るときに浮いてしまう
	if ((y + h) > (slopeY - PLAYER_SLOPE_ATTRACTION))
	{
		// 着地
		LandingPlayer();

		// 坂とめり込んでいる分だけ上へ移動
		g_PlayerData.posY -= (y + h) - slopeY;
	}
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
	if (!IsState(PLAYER_AIR))
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

void CalcBoxCollision(PlayerData player, float& x, float& y, float& w, float& h)
{
	x = player.isTurn ?
		player.posX + PLAYER_WIDTH - player.boxCollision.posX - player.boxCollision.width :
		player.posX + player.boxCollision.posX;
	y = player.posY + player.boxCollision.posY;
	w = player.boxCollision.width;
	h = player.boxCollision.height;
}

void LandingPlayer()
{
	g_PlayerData.moveY = 0.0f;
	ReleaseState(PLAYER_AIR);
	ReleaseState(PLAYER_FALL);
}

void PlayerHitAutoDoorX(AutoDoorData autoDoor)
{
	PlayerPushOutX(autoDoor.posX, autoDoor.posY, AUTO_DOOR_WIDTH, AUTO_DOOR_HEIGHT, true, true);
}

void PlayerHitAutoDoorY(AutoDoorData autoDoor)
{
	PlayerPushOutY(autoDoor.posX, autoDoor.posY, AUTO_DOOR_WIDTH, AUTO_DOOR_HEIGHT);
}

void PlayerHitMoveBlockX(MoveBlockData moveBlock)
{
	PlayerPushOutX(moveBlock.posX, moveBlock.posY, ARCH_BLOCK_WIDTH, ARCH_BLOCK_HEIGHT, true, true);
}

void PlayerHitMoveBlockY(MoveBlockData moveBlock)
{
	bool isHit = PlayerPushOutY(moveBlock.posX, moveBlock.posY, ARCH_BLOCK_WIDTH, ARCH_BLOCK_HEIGHT, 8.0f);

	// ヒットしていて
	if (isHit)
	{
		// 上に乗っていたら横移動を追従させる
		if (g_PlayerData.moveY >= 0.0f && !IsState(PLAYER_AIR))
		{
			g_PlayerData.posX += moveBlock.posX - moveBlock.oldX;
		}

	}
}
