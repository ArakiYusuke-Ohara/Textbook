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
	float distanceX = block->startPosX - player.body.posX;

	// ② 自動ドアとプレイヤーがY軸でどれだけ離れているか計算する
	float distanceY = block->startPosY - player.body.posY;

	// ③ 公式より２点間の距離を計算する
	float distance = sqrtf(distanceX * distanceX + distanceY * distanceY);

	// ④ ２点間の距離がAUTO_DOOR_OPEN_DISTANCE以下であればisOpenフラグをtrueにする
	if (distance <= AUTO_DOOR_OPEN_DISTANCE)
	{
		isOpen = true;
	}

	// isOpenがtrueなら上昇、falseなら下降
	block->moveY = isOpen ? -AUTO_DOOR_SPEED : AUTO_DOOR_SPEED;
}

void UpdateAutoDoor(BlockData* block)
{
	// 移動
	block->posX += block->moveX;
	block->posY += block->moveY;

	// 位置制限
	if (block->posY < block->startPosY - AUTO_DOOR_HEIGHT)
	{
		block->posY = block->startPosY - AUTO_DOOR_HEIGHT;
		block->moveY = 0.0f;
	}
	else if (block->posY > (block->startPosY))
	{
		block->posY = block->startPosY;
		block->moveY = 0.0f;
	}
}

void ResolveAutoDoorX(Body* body, const BlockData* block)
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

void ResolveAutoDoorY(Body* body, const BlockData* block)
{
	// 上からあたったか
	if (body->moveY > 0.0f)
	{
		// 上に押し出す
		body->posY -= (body->posY + body->height) - block->posY;
		// 着地
		body->isAir = false;
		// 足元ブロックとして登録
		body->groundBlock = block;
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
