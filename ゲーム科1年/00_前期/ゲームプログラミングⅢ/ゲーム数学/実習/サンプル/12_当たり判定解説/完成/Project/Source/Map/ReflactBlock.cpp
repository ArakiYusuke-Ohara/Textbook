#include "DxLib.h"
#include "ReflactBlock.h"
#include "../Player/Player.h"
#include "../Math/MyMath.h"

void StartReflactBlock(BlockData* block)
{
	block->body.reflact = true;
}

void ResolveReflactBlockX(Body* body, const BlockData* block)
{
	// 左からあたったか
	if (body->move.x > 0.0f)
	{
		// 左に押し出す
		body->pos.x -= (body->pos.x + body->width) - block->body.pos.x;
		if (body->reflactPower > 0.0f)
		{
			// 左向き法線で反射
			VECTOR ref = VecReflact(body->move, VGet(-1.0f, 0.0f, 0.0f));
			body->move = VecScale(ref, body->reflactPower);
		}
		else
		{
			// 反射しない
			body->move.x = 0.0f;
		}
	}
	// 右からあたったか
	else if (body->move.x < 0.0f)
	{
		// 右に押し出す
		body->pos.x += (block->body.pos.x + block->body.width) - body->pos.x;
		if (body->reflactPower > 0.0f)
		{
			// 右向き法線で反射
			VECTOR ref = VecReflact(body->move, VGet(1.0f, 0.0f, 0.0f));
			body->move = VecScale(ref, body->reflactPower);
		}
		else
		{
			// 反射しない
			body->move.x = 0.0f;
		}
	}
}

void ResolveReflactBlockY(Body* body, const BlockData* block)
{
	// 上からあたったか
	if (body->move.y > 0.0f)
	{
		// 上に押し出す
		body->pos.y -= (body->pos.y + body->height) - block->body.pos.y;
		// 着地
		body->isAir = false;

		if (body->reflactPower > 0.0f)
		{
			// 上向き法線で反射
			VECTOR ref = VecReflact(body->move, VGet(0.0f, -1.0f, 0.0f));
			body->move = VecScale(ref, body->reflactPower);
		}
		else
		{
			// 反射しない
			body->move.y = 0.0f;
		}
	}
	// 下からあたったか
	else if (body->move.y < 0.0f)
	{
		// 下に押し出す
		body->pos.y += (block->body.pos.y + block->body.height) - body->pos.y;
		if (body->reflactPower > 0.0f)
		{
			// 下向き法線で反射
			VECTOR ref = VecReflact(body->move, VGet(0.0f, 1.0f, 0.0f));
			body->move = VecScale(ref, body->reflactPower);
		}
		else
		{
			// 反射しない
			body->move.y = 0.0f;
		}
	}
}
