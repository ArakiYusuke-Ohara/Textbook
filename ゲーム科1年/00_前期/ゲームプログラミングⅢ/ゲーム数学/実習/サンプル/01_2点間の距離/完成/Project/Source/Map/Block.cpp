#include "Block.h"
#include "AutoDoor.h"
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
		block->posX = 0.0f;
		block->posY = 0.0f;
		block->moveX = 0.0f;
		block->moveY = 0.0f;
		block->type = MAP_CHIP_NONE;
		block->width = 0.0f;
		block->height = 0.0f;
		block->startPosX = 0.0f;
		block->startPosY = 0.0f;
	}
}

void LoadBlock()
{
	g_BlockHandle[NORMAL_BLOCK] = LoadGraph("Data/Map/NormalBlock.png");
	g_BlockHandle[SLOPE_BLOCK] = LoadGraph("Data/Map/SlopeBlock.png");
	g_BlockHandle[AUTO_DOOR] = LoadGraph("Data/Map/AutoDoor.png");
}

void StartBlock()
{
	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		// 配置位置を記憶
		block->startPosX = block->posX;
		block->startPosY = block->posY;
	}
}

void StepBlock()
{
	BlockData* block = g_Blocks;
	for (int i = 0; i < BLOCK_MAX; i++, block++)
	{
		// タイプごとのステップ処理
		switch (block->type)
		{
			case AUTO_DOOR:	StepAutoDoor(block);	break;
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
			case AUTO_DOOR:	UpdateAutoDoor(block);	break;
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
			DrawGraph((int)(block->posX - camera.posX), (int)(block->posY - camera.posY), block->handle, TRUE);
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
	if (body->moveX > 0.0f)
	{
		// 左に押し出す
		body->posX -= (body->posX + body->width) - block->posX;
	}
	// 右からあたったか
	else if (body->moveX < 0.0f)
	{
		// 右に押し出す
		body->posX += (block->posX + block->width) - body->posX;
	}

	// 移動量は0にする
	body->moveX = 0.0f;
}

void ResolveNormalBlockY(Body* body, const BlockData* block)
{
	// 上からあたったか
	if (body->moveY > 0.0f)
	{
		// 上に押し出す
		body->posY -= (body->posY + body->height) - block->posY;
		// 着地
		body->isAir = false;
	}
	// 下からあたったか
	else if (body->moveY < 0.0f)
	{
		// 下に押し出す
		body->posY += (block->posY + block->height) - body->posY;
	}

	// 移動量は0にする
	body->moveY = 0.0f;
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
