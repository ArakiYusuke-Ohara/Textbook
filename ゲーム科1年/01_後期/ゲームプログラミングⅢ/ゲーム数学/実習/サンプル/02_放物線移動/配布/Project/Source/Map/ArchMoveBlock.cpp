#include "ArchMoveBlock.h"
#include "MapParameter.h"
#include "../Collision/CollisionParameter.h"

#define ARCH_WIDTH	(200.0f)
#define ARCH_HEIGHT	(100.0f)
#define ARCH_SPEED	(0.5f)

void StartArchMoveBlock(BlockData* block)
{
	block->moveX = ARCH_SPEED;
}

void StepArchMoveBlock(BlockData* block)
{
	// 端まで行ったら向きを反転
	if (block->posX > (block->startPosX + ARCH_WIDTH) || block->posX < block->startPosX)
	{
		block->moveX = -block->moveX;
	}
}

void UpdateArchMoveBlock(BlockData* block)
{
	// 右へ移動
	block->posX += block->moveX;

	// わかりやすい名前の変数に格納
	float x = block->startPosX;
	float y = block->startPosY;
	float h = block->startPosX + (ARCH_WIDTH * 0.5f);
	float k = block->startPosY - ARCH_HEIGHT;

	// ① 放物線の方程式に初期位置と頂点座標を代入してaを求める


	// ② 現在のX座標と頂点座標とaからY座標を求める
	//    計算結果はblock->posYに代入する
	block->posY = 0.0f;
}

void ResolveArchMoveBlockX(Body* body, const BlockData* block)
{
	// 左からあたったか
	if ((body->prevPosX + body->width) <= block->prevPosX)
	{
		// 左に押し出す
		body->posX -= (body->posX + body->width) - block->posX;
	}
	// 右からあたったか
	else if (body->prevPosX >= (block->prevPosX + block->width))
	{
		// 右に押し出す
		body->posX += (block->posX + block->width) - body->posX;
	}

	// 移動量は0にする
	body->moveX = 0.0f;

}

void ResolveArchMoveBlockY(Body* body, const BlockData* block)
{
	// 上からあたったか
	if ((body->prevPosY + body->height) <= block->prevPosY)
	{
		// 上に押し出す
		body->posY -= (body->posY + body->height) - block->posY;
		// 着地
		body->isAir = false;
		// 足元ブロックとして登録
		body->groundBlock = block;
		// 移動量は0にする
		body->moveY = 0.0f;
	}
	// 下からあたったか
	else if (body->prevPosY >= (block->prevPosY + block->height))
	{
		// 下に押し出す
		body->posY += (block->posY + block->height) - body->posY;
		// 移動量はブロックに合わせる
		body->moveY = block->posY - block->prevPosY;

	}

}
