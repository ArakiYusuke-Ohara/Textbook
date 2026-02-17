#include "Block.h"
#include "../Camera/Camera.h"

BlockData g_Blocks[BLOCK_MAX] = { 0 };
int g_BlockHandle[BLOCK_TYPE_MAX] = { 0 };


void InitBlock()
{
	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		block->active = false;
		block->posX = 0.0f;
		block->posY = 0.0f;
		block->type = MAP_CHIP_NONE;
		block->width = 0.0f;
		block->height = 0.0f;
	}
}

void LoadBlock()
{
	g_BlockHandle[NORMAL_BLOCK] = LoadGraph("Data/Map/NormalBlock.png");
	g_BlockHandle[SLOPE_BLOCK] = LoadGraph("Data/Map/SlopeBlock.png");
}

void StartBlock()
{
}

void StepBlock()
{
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
			DrawGraph((int)(block->posX - camera.posX), (int)(block->posY - camera.posY), block->handle, TRUE);
		}
	}
}

void FinBlock()
{
}

BlockData* CreateBlock(MapChipType type, float posX, float posY)
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
			block->posX = posX;
			block->posY = posY;
			block->type = type;
			block->width = MAP_CHIP_WIDTH;
			block->height = MAP_CHIP_HEIGHT;
			return block;
		}
	}

	return nullptr;
}

BlockData* GetBlocks()
{
	return g_Blocks;
}
