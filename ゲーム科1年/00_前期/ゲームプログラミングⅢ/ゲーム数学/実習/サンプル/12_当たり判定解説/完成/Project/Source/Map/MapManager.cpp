#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "SlopeBlock.h"
#include "AutoDoor.h"
#include "ArchMoveBlock.h"
#include "MoveBlock.h"
#include "CircleMoveBlock.h"
#include "ReflactBlock.h"
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
void ResolveMapCollision(Body* self, int range)
{
	// 当たったブロック情報をリセット
	self->groundBlock = NULL;
	self->hitBlock = NULL;

	// X軸解決
	ResolveMapCollisionX(self, range);
	// Y軸解決
	ResolveMapCollisionY(self, range);
}

void ResolveMapCollisionX(Body* self, int range)
{
	// 座標を添字に変換
	int x = (int)((self->pos.x + self->width / 2) / MAP_CHIP_WIDTH);
	int y = (int)((self->pos.y + self->height / 2) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = x - range;
	int top = y - range;
	// プレイヤーの右下にあるマップチップインデックス
	int right = x + range;
	int bottom = y + range;

	// X軸だけ移動する
	self->pos.x += self->move.x;

	// 坂を先に解決しないと付近のブロックに引っかかる
	PreviewSlope(self, range);

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
			if (CheckSquareSquare(self, &block->body))
			{
				// 衝突解決
				ResolveMapchipX(self, mapChipData);
				// 当たったブロックを登録
				self->hitBlock = &block->body;
			}
		}
	}
}

void ResolveMapCollisionY(Body* self, int range)
{
	// 座標を添字に変換
	int x = (int)((self->pos.x + self->width / 2) / MAP_CHIP_WIDTH);
	int y = (int)((self->pos.y + self->height / 2) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = x - range;
	int top = y - range;
	// プレイヤーの右下にあるマップチップインデックス
	int right = x + range;
	int bottom = y + range;

	// Y軸だけ移動する
	self->pos.y += self->move.y;

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
			if (CheckSquareSquare(self, &block->body))
			{
				// 衝突解決
				ResolveMapchipY(self, mapChipData);
				// 当たったブロックを登録
				self->hitBlock = &block->body;
			}
		}
	}
}

/// <summary>
/// X軸の衝突解決
/// </summary>
/// <param name="body">当たり判定ボディ</param>
/// <param name="mapchip">マップチップ</param>
void ResolveMapchipX(Body* self, const MapChipData* mapchip)
{
	switch (mapchip->type)
	{
	case SLOPE_BLOCK:
		// 坂ブロック
		ResolveSlopeBlockX(self, mapchip->data);
		break;
	case REFLACT_BLOCK:
		// 反射ブロック
		ResolveReflactBlockX(self, mapchip->data);
		break;
	default:
		// それ以外は通常の衝突解決
		ResolveCollisionX(self, &mapchip->data->body);
		break;
	}
}

/// <summary>
/// Y軸の衝突解決
/// </summary>
/// <param name="body">当たり判定ボディ</param>
/// <param name="mapchip">マップチップ</param>
void ResolveMapchipY(Body* self, const MapChipData* mapchip)
{
	switch (mapchip->type)
	{
	case SLOPE_BLOCK:
		// 坂ブロック
		ResolveSlopeBlockY(self, mapchip->data);
		break;
	case REFLACT_BLOCK:
		// 円移動ブロック
		ResolveReflactBlockY(self, mapchip->data);
		break;
	default:
		// それ以外は通常の衝突解決
		ResolveCollisionY(self, &mapchip->data->body);
		break;
	}
}

void PreviewSlope(Body* body, int range)
{
	// 座標を添字に変換
	int x = (int)((body->pos.x + body->width / 2) / MAP_CHIP_WIDTH);
	int y = (int)((body->pos.y + body->height / 2) / MAP_CHIP_HEIGHT);
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
			if (CheckSquareSquare(body, &block->body))
			{
				// 衝突解決
				PreviewSlopeBlock(body, block);
			}
		}
	}
}
