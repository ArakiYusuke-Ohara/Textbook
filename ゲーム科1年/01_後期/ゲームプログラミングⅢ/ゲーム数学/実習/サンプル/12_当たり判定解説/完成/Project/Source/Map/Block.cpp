#include "Block.h"
#include "AutoDoor.h"
#include "ArchMoveBlock.h"
#include "MoveBlock.h"
#include "CircleMoveBlock.h"
#include "ReflactBlock.h"
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
		block->isReflact = false;
		block->body = {};
		block->type = MAP_CHIP_NONE;
		block->startPos = {};
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
	g_BlockHandle[REFLACT_BLOCK] = LoadGraph("Data/Map/ReflactBlock.png");
}

void StartBlock()
{
	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		// 配置位置を記憶
		block->startPos.x = block->body.pos.x;
		block->startPos.y = block->body.pos.y;

		// タイプごとの開始処理
		switch (block->type)
		{
			case ARCH_MOVE_BLOCK:	StartArchMoveBlock(block);	break;
			case REFLACT_BLOCK:		StartReflactBlock(block);	break;

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
		block->body.prevPos = block->body.pos;

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
			DrawGraph((int)(block->body.pos.x - camera.pos.x), (int)(block->body.pos.y - camera.pos.y), block->handle, TRUE);
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
			block->body.pos = pos;
			block->type = type;
			block->body.width = (float)BLOCK_MASTER_DATA[type].width;
			block->body.height = (float)BLOCK_MASTER_DATA[type].height;
			block->isReflact = BLOCK_MASTER_DATA[type].isReflact;
			return block;
		}
	}

	return nullptr;
}

BlockData* GetBlocks()
{
	return g_Blocks;
}
