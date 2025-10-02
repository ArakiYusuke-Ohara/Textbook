#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "AutoDoor.h"
#include "ArchBlock.h"
#include "../Player/Player.h"

// キャラクターの周囲何マスまでチェックするか
#define CHECK_ROUND_NUM (2)

void CheckNormalX(int left, int top, int right, int bottom);
void CheckNormalY(int left, int top, int right, int bottom);
void CheckSlopeX(int left, int top, int right, int bottom);
void CheckSlopeY(int left, int top, int right, int bottom);
void CheckAutoDoorX();
void CheckAutoDoorY();
void CheckArchBlockX();
void CheckArchBlockY();

void InitMap()
{
	InitAutoDoor();
	InitArchBlock();
}

void LoadMap()
{
	LoadMapChipData();
	LoadBlock();
	LoadAutoDoor();
	LoadArchBlock();
}

void StartMap()
{
	CreateMap();
	StartAutoDoor();
	StartArchBlock();
}

void StepMap()
{
	StepAutoDoor();
	StepArchBlock();
}

void UpdateMap()
{
	UpdateAutoDoor();
	UpdateArchBlock();
}

void DrawMap()
{
	// ブロック描画
	DrawBlock();

	// 自動ドア描画
	DrawAutoDoor();

	// 放物線移動ブロック描画
	DrawArchBlock();
}

void FinMap()
{
	FinBlock();

	FinAutoDoor();

	FinArchBlock();
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

	PlayerMoveX();
	CheckSlopeX(left, top, right, bottom);
	CheckNormalX(left, top, right, bottom);
	CheckAutoDoorX();
	CheckArchBlockX();

	PlayerMoveY();
	CheckSlopeY(left, top, right, bottom);
	CheckNormalY(left, top, right, bottom);
	CheckAutoDoorY();
	CheckArchBlockY();
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

void CheckArchBlockX()
{
	// 放物線移動ブロック取得
	ArchBlockData archBlock = GetArchBlockData();
	// プレイヤーとの当たり判定
	PlayerHitArchBlockX(archBlock);
}

void CheckArchBlockY()
{
	// 放物線移動ブロック取得
	ArchBlockData archBlock = GetArchBlockData();
	// プレイヤーとの当たり判定
	PlayerHitArchBlockY(archBlock);
}

