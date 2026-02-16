#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Sound/SoundManager.h"
#include "../Map/MapChip.h"
#include "../Map/MapManager.h"

// プレイヤー設定関連
#define PLAYER_WIDTH (50.0f)
#define PLAYER_HEIGHT (50.0f)
#define PLAYER_RADIUS	(36.0f)
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)
#define PLAYER_MOVE_SPEED (4.0f)

// ジャンプ力
#define PLAYER_JUMP_POWER (-12.0f)
// 重力
#define PLAYER_GRAVITY (0.4f)

// 矩形判定のサイズ
#define PLAYER_BOX_COLLISION_WIDTH (50)
#define PLAYER_BOX_COLLISION_HEIGHT (50)

// キャラクターの周囲何マスまでチェックするか
#define PLAYER_CHECK_ROUND_NUM (2)

// このCPPでしか使わない関数
void MovePlayerWithCollision();	// 当たり判定付き移動

PlayerData g_PlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.active = false;
}

void LoadPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Player/Player.png");
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;
}

void StepPlayer()
{
	// 死んでいたら何もしない
	if (!g_PlayerData.active)
	{
		return;
	}

	// X移動量は毎回リセットする
	g_PlayerData.moveX = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.moveY += PLAYER_GRAVITY;

	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	}

	// Z入力
	if (IsTriggerKey(KEY_Z))
	{
		g_PlayerData.moveY = PLAYER_JUMP_POWER;
	}
}

void UpdatePlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 当たり判定付きで移動
	MovePlayerWithCollision();

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_PlayerData.moveY < 0.0f || g_PlayerData.moveY > PLAYER_GRAVITY)
	{
		g_PlayerData.isAir = true;
	}
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 小数誤差が起きるので描画位置は四捨五入する
	DrawGraph((int)(g_PlayerData.posX + 0.5f), (int)(g_PlayerData.posY + 0.5f), g_PlayerData.handle, TRUE);
}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

void MovePlayerWithCollision()
{
	// CheckMapCollision関数を呼ぶと当たった物体の座標が入る
	float hitX = 0, hitY = 0;

	// X軸だけプレイヤーを移動させる
	g_PlayerData.posX += g_PlayerData.moveX;

	// マップと当たり判定
	if (CheckMapCollision(g_PlayerData.posX, g_PlayerData.posY, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_CHECK_ROUND_NUM,
		hitX, hitY))
	{
		// 左からあたったか
		if (g_PlayerData.moveX > 0.0f)
		{
			// 左に押し出す
			g_PlayerData.posX -= (g_PlayerData.posX + PLAYER_WIDTH) - hitX;
		}
		// 右からあたったか
		else if (g_PlayerData.moveX < 0.0f)
		{
			// 右に押し出す
			g_PlayerData.posX += (hitX + MAP_CHIP_WIDTH) - g_PlayerData.posX;
		}

		// 移動量は0にする
		g_PlayerData.moveX = 0.0f;
	}

	// Y軸だけプレイヤーを移動させる
	g_PlayerData.posY += g_PlayerData.moveY;

	// マップと当たり判定
	if (CheckMapCollision(g_PlayerData.posX, g_PlayerData.posY, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_CHECK_ROUND_NUM,
		hitX, hitY))
	{
		// 上からあたったか
		if (g_PlayerData.moveY > 0.0f)
		{
			// 上に押し出す
			g_PlayerData.posY -= (g_PlayerData.posY + PLAYER_HEIGHT) - hitY;
			g_PlayerData.isAir = false;
		}
		// 下からあたったか
		else if (g_PlayerData.moveY < 0.0f)
		{
			// 下に押し出す
			g_PlayerData.posY += (hitY + MAP_CHIP_HEIGHT) - g_PlayerData.posY;
		}

		// 移動量は0にする
		g_PlayerData.moveY = 0.0f;
	}

}
