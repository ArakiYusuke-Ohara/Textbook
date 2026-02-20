#include "Block.h"
#include "AutoDoor.h"
#include "ArchMoveBlock.h"
#include "MoveBlock.h"
#include "CircleMoveBlock.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionParameter.h"

BlockData g_Blocks[BLOCK_MAX] = { 0 };
int g_BlockHandle[BLOCK_TYPE_MAX] = { 0 };

void InitBlock()
{
	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		block->active = false;
		block->pos = {};
		block->move = {};
		block->type = MAP_CHIP_NONE;
		block->width = 0.0f;
		block->height = 0.0f;
		block->startPos = {};
		block->prevPos = {};
	}
}

void LoadBlock()
{
	g_BlockHandle[NORMAL_BLOCK] = LoadGraph("Data/Map/NormalBlock.png");
	g_BlockHandle[SLOPE_BLOCK] = LoadGraph("Data/Map/SlopeBlock.png");
	g_BlockHandle[AUTO_DOOR] = LoadGraph("Data/Map/AutoDoor.png");
	g_BlockHandle[ARCH_MOVE_BLOCK] = LoadGraph("Data/Map/MoveBlock.png");
	g_BlockHandle[MOVE_BLOCK] = LoadGraph("Data/Map/MoveBlock.png");
	g_BlockHandle[CIRCLE_MOVE_BLOCK] = LoadGraph("Data/Map/MoveBlock.png");
}

void StartBlock()
{
	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		// 配置位置を記憶
		block->startPos.x = block->pos.x;
		block->startPos.y = block->pos.y;

		// タイプごとの開始処理
		switch (block->type)
		{
			case ARCH_MOVE_BLOCK:	StartArchMoveBlock(block);	break;

			default: break;
		}
	}
}

void StepBlock()
{
	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		// 全ブロック共通処理
		// 前回の座標を記録
		block->prevPos.x = block->pos.x;
		block->prevPos.y = block->pos.y;

		// タイプごとのステップ処理
		switch (block->type)
		{
			case AUTO_DOOR:			StepAutoDoor(block);	break;
			case ARCH_MOVE_BLOCK:	StepArchMoveBlock(block);	break;
			case MOVE_BLOCK:		StepMoveBlock(block);	break;
			case CIRCLE_MOVE_BLOCK:	StepCircleMoveBlock(block);	break;

			default:	break;
		}
	}
}

void UpdateBlock()
{
	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		// タイプごとの更新処理
		switch (block->type)
		{
			case AUTO_DOOR:			UpdateAutoDoor(block);	break;
			case ARCH_MOVE_BLOCK:	UpdateArchMoveBlock(block);	break;
			case MOVE_BLOCK:		UpdateMoveBlock(block);	break;
			case CIRCLE_MOVE_BLOCK:	UpdateCircleMoveBlock(block);	break;

			default:	break;
		}
	}
}

void DrawBlock()
{
	// スクロールのためカメラを取得
	CameraData camera = GetCamera();

	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		if (block->active)
		{
			DrawGraph((int)(block->pos.x - camera.pos.x), (int)(block->pos.y - camera.pos.y), block->handle, TRUE);
		}
	}
}

void FinBlock()
{
	for (int i = 0; i < BLOCK_TYPE_MAX; i++)
	{
		DeleteGraph(g_BlockHandle[i]);
	}
}

void ResolveNormalBlockX(Body* body, const BlockData* block)
{
	// 左からあたったか
	if (body->move.x > 0.0f)
	{
		// 左に押し出す
		body->pos.x -= (body->pos.x + body->width) - block->pos.x;
	}
	// 右からあたったか
	else if (body->move.x < 0.0f)
	{
		// 右に押し出す
		body->pos.x += (block->pos.x + block->width) - body->pos.x;
	}

	// 移動量は0にする
	body->move.x = 0.0f;
}

void ResolveNormalBlockY(Body* body, const BlockData* block)
{
	// 上からあたったか
	if (body->move.y > 0.0f)
	{
		// 上に押し出す
		body->pos.y -= (body->pos.y + body->height) - block->pos.y;
		// 着地
		body->isAir = false;
	}
	// 下からあたったか
	else if (body->move.y < 0.0f)
	{
		// 下に押し出す
		body->pos.y += (block->pos.y + block->height) - body->pos.y;
	}

	// 移動量は0にする
	body->move.y = 0.0f;
}

BlockData* CreateBlock(MapChipType type, VECTOR pos)
{
	// 未使用のブロックを探す
	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		if (!block->active)
		{
			// ブロック生成
			block->active = true;
			block->handle = g_BlockHandle[type];
			block->pos = pos;
			block->type = type;
			block->width = (float)BLOCK_MASTER_DATA[type].width;
			block->height = (float)BLOCK_MASTER_DATA[type].height;
			return block;
		}
	}

	return nullptr;
}

BlockData* GetBlocks()
{
	return g_Blocks;
}
