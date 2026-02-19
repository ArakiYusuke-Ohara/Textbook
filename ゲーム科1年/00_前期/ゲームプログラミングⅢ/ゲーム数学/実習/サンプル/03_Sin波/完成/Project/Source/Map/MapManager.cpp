#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "SlopeBlock.h"
#include "AutoDoor.h"
#include "ArchMoveBlock.h"
#include "MoveBlock.h"
#include "../Player/Player.h"
#include "../Collision/Collision.h"
#include "../Collision/CollisionParameter.h"

// このCPPしか使わない関数
void ResolveMapchipX(Body* body, const MapChipData* mapchip);
void ResolveMapchipY(Body* body, const MapChipData* mapchip);
void PreviewSlope(Body* body, int range);

void InitMap()
{
	InitBlock();
}

void LoadMap()
{
	LoadMapChipData();
	LoadBlock();
}

void StartMap()
{
	CreateMap();
	StartBlock();
}

void StepMap()
{
	StepBlock();
}

void UpdateMap()
{
	UpdateBlock();
}

void DrawMap()
{
	// ブロック描画
	DrawBlock();
}

void FinMap()
{
	FinBlock();
}

/// <summary>
/// マップと衝突解決
/// </summary>
/// <param name="body"></param>
/// <param name="range"></param>
void ResolveMapCollision(Body* body, int range)
{
	// 足元ブロック情報をリセット
	body->groundBlock = NULL;

	// X軸解決
	ResolveMapCollisionX(body, range);
	// Y軸解決
	ResolveMapCollisionY(body, range);
}

void ResolveMapCollisionX(Body* body, int range)
{
	// 座標を添字に変換
	int x = (int)((body->posX + body->width / 2) / MAP_CHIP_WIDTH);
	int y = (int)((body->posY + body->height / 2) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = x - range;
	int top = y - range;
	// プレイヤーの右下にあるマップチップインデックス
	int right = x + range;
	int bottom = y + range;

	// X軸だけ移動する
	body->posX += body->moveX;

	// 坂を先に解決しないと付近のブロックに引っかかる
	PreviewSlope(body, range);

	// 左上からチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ取得
			const MapChipData* mapChipData = GetMapChipData(x, y);

			// フラグチェック
			if (!mapChipData->isCollision) continue;
			// タイプ無しは無視
			if (mapChipData->type == MAP_CHIP_NONE) continue;

			// ブロックを取り出して当たり判定
			BlockData* block = mapChipData->data;
			if (CheckSquareSquare(body->posX, body->posY, body->width, body->height,
				block->posX, block->posY, block->width, block->height))
			{
				// 衝突解決
				ResolveMapchipX(body, mapChipData);
			}
		}
	}
}

void ResolveMapCollisionY(Body* body, int range)
{
	// 座標を添字に変換
	int x = (int)((body->posX + body->width / 2) / MAP_CHIP_WIDTH);
	int y = (int)((body->posY + body->height / 2) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = x - range;
	int top = y - range;
	// プレイヤーの右下にあるマップチップインデックス
	int right = x + range;
	int bottom = y + range;

	// Y軸だけ移動する
	body->posY += body->moveY;

	// 左上からチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ取得
			const MapChipData* mapChipData = GetMapChipData(x, y);

			// フラグチェック
			if (!mapChipData->isCollision) continue;
			// タイプ無しは無視
			if (mapChipData->type == MAP_CHIP_NONE) continue;

			// ブロックを取り出して当たり判定
			BlockData* block = mapChipData->data;
			if (CheckSquareSquare(body->posX, body->posY, body->width, body->height,
				block->posX, block->posY, block->width, block->height))
			{
				// 衝突解決
				ResolveMapchipY(body, mapChipData);
			}
		}
	}
}

/// <summary>
/// X軸の衝突解決
/// </summary>
/// <param name="body">当たり判定ボディ</param>
/// <param name="mapchip">マップチップ</param>
void ResolveMapchipX(Body* body, const MapChipData* mapchip)
{
	switch (mapchip->type)
	{
	case NORMAL_BLOCK:
		// 通常ブロック
		ResolveNormalBlockX(body, mapchip->data);
		break;
	case SLOPE_BLOCK:
		// 坂ブロック
		ResolveSlopeBlockX(body, mapchip->data);
		break;
	case AUTO_DOOR:
		// 自動ドア
		ResolveAutoDoorX(body, mapchip->data);
		break;
	case ARCH_MOVE_BLOCK:
		// 放物線移動
		ResolveArchMoveBlockX(body, mapchip->data);
		break;
	case MOVE_BLOCK:
		// 放物線移動
		ResolveMoveBlockX(body, mapchip->data);
		break;
	default:
		break;
	}
}

/// <summary>
/// Y軸の衝突解決
/// </summary>
/// <param name="body">当たり判定ボディ</param>
/// <param name="mapchip">マップチップ</param>
void ResolveMapchipY(Body* body, const MapChipData* mapchip)
{
	switch (mapchip->type)
	{
	case NORMAL_BLOCK:
		// 通常ブロック
		ResolveNormalBlockY(body, mapchip->data);
		break;
	case SLOPE_BLOCK:
		// 坂ブロック
		ResolveSlopeBlockY(body, mapchip->data);
		break;
	case AUTO_DOOR:
		// 自動ドア
		ResolveAutoDoorY(body, mapchip->data);
		break;
	case ARCH_MOVE_BLOCK:
		// 放物線移動
		ResolveArchMoveBlockY(body, mapchip->data);
		break;
	case MOVE_BLOCK:
		// 放物線移動
		ResolveMoveBlockY(body, mapchip->data);
		break;
	default:
		break;
	}
}

void PreviewSlope(Body* body, int range)
{
	// 座標を添字に変換
	int x = (int)((body->posX + body->width / 2) / MAP_CHIP_WIDTH);
	int y = (int)((body->posY + body->height / 2) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = x - range;
	int top = y - range;
	// プレイヤーの右下にあるマップチップインデックス
	int right = x + range;
	int bottom = y + range;

	// 左上からチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ取得
			const MapChipData* mapChipData = GetMapChipData(x, y);

			// フラグチェック
			if (!mapChipData->isCollision) continue;
			// 坂以外は無視
			if (mapChipData->type != SLOPE_BLOCK) continue;

			// ブロックを取り出して当たり判定
			BlockData* block = mapChipData->data;
			if (CheckSquareSquare(body->posX, body->posY, body->width, body->height,
				block->posX, block->posY, block->width, block->height))
			{
				// 衝突解決
				PreviewSlopeBlock(body, block);
			}
		}
	}
}
