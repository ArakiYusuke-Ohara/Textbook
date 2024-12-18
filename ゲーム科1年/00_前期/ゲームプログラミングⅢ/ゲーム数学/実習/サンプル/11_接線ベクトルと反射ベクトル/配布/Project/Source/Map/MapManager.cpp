#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "AutoDoor.h"
#include "MoveBlock.h"
#include "ReflactBlock.h"
#include "../Player/Player.h"
#include "../Bullet/StraightBullet.h"

// キャラクターの周囲何マスまでチェックするか
#define CHECK_ROUND_NUM (2)

void CheckNormalX(int left, int top, int right, int bottom);
void CheckNormalY(int left, int top, int right, int bottom);
void CheckSlopeX(int left, int top, int right, int bottom);
void CheckSlopeY(int left, int top, int right, int bottom);
void CheckAutoDoorX();
void CheckAutoDoorY();
void CheckMoveBlockX();
void CheckMoveBlockY();
void CheckReflactBlock();

void InitMap()
{
	InitAutoDoor();
	InitMoveBlock();
	InitReflactBlock();
}

void LoadMap()
{
	LoadMapChipData();
	LoadBlock();
	LoadAutoDoor();
	LoadMoveBlock();
	LoadReflactBlock();
}

void StartMap()
{
	CreateMap();
	StartAutoDoor();
	StartMoveBlock();
	StartReflactBlock();
}

void StepMap()
{
	StepAutoDoor();
	StepMoveBlock();
	StepReflactBlock();
}

void UpdateMap()
{
	UpdateAutoDoor();
	UpdateMoveBlock();
	UpdateReflactBlock();
}

void DrawMap()
{
	// ブロック描画
	DrawBlock();

	// 自動ドア描画
	DrawAutoDoor();

	// 移動ブロック描画
	DrawMoveBlock();

	// 反射ブロック描画
	DrawReflactBlock();
}

void FinMap()
{
	FinBlock();

	FinAutoDoor();

	FinMoveBlock();

	FinReflactBlock();
}

void ChceckMapPlayerCollision()
{
	PlayerData player = GetPlayer();
	// プレイヤーの足元の座標をマップチップのインデックスに変換
	int playerX = (int)(player.pos.x / MAP_CHIP_WIDTH);
	int playerY = (int)((player.pos.y + PLAYER_HEIGHT) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = playerX - CHECK_ROUND_NUM;
	int top = playerY - CHECK_ROUND_NUM;
	// プレイヤーの右下にあるマップチップインデックス
	int right = playerX + CHECK_ROUND_NUM;
	int bottom = playerY + CHECK_ROUND_NUM;


	CheckSlopeY(left, top, right, bottom);
	CheckNormalY(left, top, right, bottom);
	CheckAutoDoorY();
	CheckMoveBlockY();
	CheckSlopeX(left, top, right, bottom);
	CheckNormalX(left, top, right, bottom);
	CheckAutoDoorX();
	CheckMoveBlockX();

	CheckReflactBlock();
}

void CheckNormalX(int left, int top, int right, int bottom)
{
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			MapChipData mapChipData = GetMapChipData(x, y);

			// MAP_CHIP_NONEの場合は何もしない
			if (mapChipData.mapChip != NORMAL_BLOCK) continue;

			PlayerHitNormalBlockX(mapChipData);
		}
	}
}

void CheckNormalY(int left, int top, int right, int bottom)
{
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			MapChipData mapChipData = GetMapChipData(x, y);

			// MAP_CHIP_NONEの場合は何もしない
			if (mapChipData.mapChip != NORMAL_BLOCK) continue;

			PlayerHitNormalBlockY(mapChipData);
		}
	}
}

void CheckSlopeX(int left, int top, int right, int bottom)
{
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			MapChipData mapChipData = GetMapChipData(x, y);

			// MAP_CHIP_NONEの場合は何もしない
			if (mapChipData.mapChip != SLOPE_BLOCK) continue;

			PlayerHitSlopeBlockX(mapChipData);
		}
	}
}

void CheckSlopeY(int left, int top, int right, int bottom)
{
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			MapChipData mapChipData = GetMapChipData(x, y);

			// MAP_CHIP_NONEの場合は何もしない
			if (mapChipData.mapChip != SLOPE_BLOCK) continue;

			PlayerHitSlopeBlockY(mapChipData);
		}
	}
}

void CheckAutoDoorX()
{
	// 自動ドアデータ取得
	AutoDoorData autoDoor = GetAutoDoorData();
	// プレイヤーと自動ドアの当たり判定
	PlayerHitAutoDoorX(autoDoor);
}

void CheckAutoDoorY()
{
	// 自動ドアデータ取得
	AutoDoorData autoDoor = GetAutoDoorData();
	// プレイヤーと自動ドアの当たり判定
	PlayerHitAutoDoorY(autoDoor);
}

void CheckMoveBlockX()
{
	// 移動ブロック取得
	MoveBlockData archBlock = GetMoveBlockData();
	// プレイヤーとの当たり判定
	PlayerHitMoveBlockX(archBlock);
}

void CheckMoveBlockY()
{
	// 移動ブロック取得
	MoveBlockData archBlock = GetMoveBlockData();
	// プレイヤーとの当たり判定
	PlayerHitMoveBlockY(archBlock);
}

void CheckReflactBlock()
{
	// 反射ブロック取得
	ReflactBlockData reflactBlock = GetReflactBlock();

	// 反射ブロックとバレットの当たり判定
	StraightBulletData* bullet = GetStraightBullet();
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		if (bullet->active)
		{
			if (CheckSquareSquare(reflactBlock.pos, REFLACT_BLOCK_WIDTH, REFLACT_BLOCK_HEIGHT,
				bullet->pos, bullet->width, bullet->height))
			{
				// バレット側の衝突処理
				StraightBulletHitReflactBlock(bullet, &reflactBlock);
			}
		}
	}

}
