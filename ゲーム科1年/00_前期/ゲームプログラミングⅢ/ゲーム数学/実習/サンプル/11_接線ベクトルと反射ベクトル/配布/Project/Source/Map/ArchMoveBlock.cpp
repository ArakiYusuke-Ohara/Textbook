#include "ArchMoveBlock.h"
#include "MapParameter.h"
#include "../Collision/CollisionParameter.h"

#define ARCH_WIDTH	(200.0f)
#define ARCH_HEIGHT	(100.0f)
#define ARCH_SPEED	(0.5f)

void StartArchMoveBlock(BlockData* block)
{
	block->move.x = ARCH_SPEED;
}

void StepArchMoveBlock(BlockData* block)
{
	// 端まで行ったら向きを反転
	if (block->pos.x > (block->startPos.x + ARCH_WIDTH) || block->pos.x < block->startPos.x)
	{
		block->move.x = -block->move.x;
	}
}

void UpdateArchMoveBlock(BlockData* block)
{
	// 右へ移動
	block->pos.x += block->move.x;

	// わかりやすい名前の変数に格納
	float x = block->startPos.x;
	float y = block->startPos.y;
	float h = block->startPos.x + (ARCH_WIDTH * 0.5f);
	float k = block->startPos.y - ARCH_HEIGHT;

	// ① 放物線の方程式に初期位置と頂点座標を代入してaを求める
	float a = (y - k) / ((x - h) * (x - h));

	// ② 現在のX座標と頂点座標とaを代入してY座標を求める
	block->pos.y = a * ((block->pos.x - h) * (block->pos.x - h)) + k;

	// 移動量を計算しておく
	block->move.x = block->pos.x - block->prevPos.x;
	block->move.y = block->pos.y - block->prevPos.y;
}

void ResolveArchMoveBlockX(Body* body, const BlockData* block)
{
	// 左からあたったか
	if ((body->prevPos.x + body->width) <= block->prevPos.x)
	{
		// 左に押し出す
		body->pos.x -= (body->pos.x + body->width) - block->pos.x;
	}
	// 右からあたったか
	else if (body->prevPos.x >= (block->prevPos.x + block->width))
	{
		// 右に押し出す
		body->pos.x += (block->pos.x + block->width) - body->pos.x;
	}

	// 移動量は0にする
	body->move.x = 0.0f;

}

void ResolveArchMoveBlockY(Body* body, const BlockData* block)
{
	// 上からあたったか
	if ((body->prevPos.y + body->height) <= block->prevPos.y)
	{
		// 上に押し出す
		body->pos.y -= (body->pos.y + body->height) - block->pos.y;
		// 着地
		body->isAir = false;
		// 足元ブロックとして登録
		body->groundBlock = block;
		// 移動量は0にする
		body->move.y = 0.0f;
	}
	// 下からあたったか
	else if (body->prevPos.y >= (block->prevPos.y + block->height))
	{
		// 下に押し出す
		body->pos.y += (block->pos.y + block->height) - body->pos.y;
		// 移動量はブロックに合わせる
		body->move.y = block->move.y;

	}

}
