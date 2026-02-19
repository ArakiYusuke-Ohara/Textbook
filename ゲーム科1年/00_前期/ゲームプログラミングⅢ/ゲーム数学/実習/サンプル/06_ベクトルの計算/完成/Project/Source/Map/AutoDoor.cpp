#include "DxLib.h"
#include "AutoDoor.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include <math.h>

#define AUTO_DOOR_OPEN_DISTANCE (200.0f)
#define AUTO_DOOR_SPEED (4.0f)

#define AUTO_DOOR_WIDTH (50.0f)
#define AUTO_DOOR_HEIGHT (100.0f)

void StepAutoDoor(BlockData* block)
{
	bool isOpen = false;
	PlayerData player = GetPlayer();

	// ① 自動ドアとプレイヤーがX軸でどれだけ離れているか計算する
	float distanceX = block->startPos.x - player.body.pos.x;

	// ② 自動ドアとプレイヤーがY軸でどれだけ離れているか計算する
	float distanceY = block->startPos.y - player.body.pos.y;

	// ③ 公式より２点間の距離を計算する
	float distance = sqrtf(distanceX * distanceX + distanceY * distanceY);

	// ④ ２点間の距離がAUTO_DOOR_OPEN_DISTANCE以下であればisOpenフラグをtrueにする
	if (distance <= AUTO_DOOR_OPEN_DISTANCE)
	{
		isOpen = true;
	}

	// isOpenがtrueなら上昇、falseなら下降
	block->move.y = isOpen ? -AUTO_DOOR_SPEED : AUTO_DOOR_SPEED;
}

void UpdateAutoDoor(BlockData* block)
{
	// 移動
	block->pos.x += block->move.x;
	block->pos.y += block->move.y;

	// 位置制限
	if (block->pos.y < block->startPos.y - AUTO_DOOR_HEIGHT)
	{
		block->pos.y = block->startPos.y - AUTO_DOOR_HEIGHT;
		block->move.y = 0.0f;
	}
	else if (block->pos.y > (block->startPos.y))
	{
		block->pos.y = block->startPos.y;
		block->move.y = 0.0f;
	}
}

void ResolveAutoDoorX(Body* body, const BlockData* block)
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

void ResolveAutoDoorY(Body* body, const BlockData* block)
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
