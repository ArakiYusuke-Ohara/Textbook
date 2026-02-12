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
const BlockData* CheckMapPlayerCollision();	// マップとの当たり判定チェック

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

	// マップと当たり判定
	if (CheckMapCollision(g_PlayerData.posX, g_PlayerData.posY, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_CHECK_ROUND_NUM,
		hitX, hitY))
	{
		// 左からあたったか
		if (g_PlayerData.moveX > 0.0f)
		{
			// 左に押し出す

		}
		// 右からあたったか
		else if (g_PlayerData.moveX < 0.0f)
		{
			// 右に押し出す

		}

		// 移動量は0にする

	}

	// Y軸だけプレイヤーを移動させる


	// マップと当たり判定
	if (CheckMapCollision(g_PlayerData.posX, g_PlayerData.posY, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_CHECK_ROUND_NUM,
		hitX, hitY))
	{
		// 上からあたったか
		if (g_PlayerData.moveY > 0.0f)
		{
			// 上に押し出す

			// 着地したので空中フラグを折る
			g_PlayerData.isAir = false;
		}
		// 下からあたったか
		else if (g_PlayerData.moveY < 0.0f)
		{
			// 下に押し出す

		}

		// 移動量は0にする

	}

}

const BlockData* CheckMapPlayerCollision()
{
	// プレイヤーの足元の座標をマップチップのインデックスに変換
	int playerX = (int)(g_PlayerData.posX / MAP_CHIP_WIDTH);
	int playerY = (int)((g_PlayerData.posY + PLAYER_HEIGHT) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = playerX - PLAYER_CHECK_ROUND_NUM;
	int top = playerY - PLAYER_CHECK_ROUND_NUM;
	// プレイヤーの右下にあるマップチップインデックス
	int right = playerX + PLAYER_CHECK_ROUND_NUM;
	int bottom = playerY + PLAYER_CHECK_ROUND_NUM;
	// 左上から3マスずつチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// わかりやすくするために変数に代入
			float playerX = g_PlayerData.posX;
			float playerY = g_PlayerData.posY;
			float playerW = PLAYER_WIDTH;
			float playerH = PLAYER_HEIGHT;

			// ブロックを取り出して当たり判定
			MapChipData mapChipData = GetMapChipData(x, y);
			// マップチップが0の場合は何もない
			if (mapChipData.mapChip == 0) continue;

			BlockData* block = mapChipData.data;

			// 当たったブロックを返却
			if (CheckSquareSquare(playerX, playerY, playerW, playerH, block->pos.x, block->pos.y, block->width, block->height))
			{
				return block;
			}
		}
	}

	// 当たってなければnullを返却
	return nullptr;
}
