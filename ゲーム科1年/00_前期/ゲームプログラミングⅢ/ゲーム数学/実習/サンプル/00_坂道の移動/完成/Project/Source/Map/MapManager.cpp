#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "../Player/Player.h"

// キャラクターの周囲何マスまでチェックするか
#define CHECK_ROUND_NUM (2)

void CheckNormalX(int left, int top, int right, int bottom);
void CheckNormalY(int left, int top, int right, int bottom);
void CheckSlopeX(int left, int top, int right, int bottom);
void CheckSlopeY(int left, int top, int right, int bottom);

void InitMap()
{
}

void LoadMap()
{
	LoadMapChipData();
	LoadBlock();
}

void StartMap()
{
	CreateMap();
}

void DrawMap()
{
	// ブロック描画
	DrawBlock();
}

void FinMap()
{
}

void ChceckMapPlayerCollision()
{
	PlayerData player = GetPlayer();
	// プレイヤーの足元の座標をマップチップのインデックスに変換
	int playerX = (int)(player.posX / MAP_CHIP_WIDTH);
	int playerY = (int)((player.posY + PLAYER_HEIGHT) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = playerX - CHECK_ROUND_NUM;
	int top = playerY - CHECK_ROUND_NUM;
	// プレイヤーの右下にあるマップチップインデックス
	int right = playerX + CHECK_ROUND_NUM;
	int bottom = playerY + CHECK_ROUND_NUM;

	CheckSlopeY(left, top, right, bottom);
	CheckNormalY(left, top, right, bottom);
	CheckSlopeX(left, top, right, bottom);
	CheckNormalX(left, top, right, bottom);
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

