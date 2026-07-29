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
	block->body.move.y = isOpen ? -AUTO_DOOR_SPEED : AUTO_DOOR_SPEED;
}

void UpdateAutoDoor(BlockData* block)
{
	// 移動
	block->body.pos.x += block->body.move.x;
	block->body.pos.y += block->body.move.y;

	// 位置制限
	if (block->body.pos.y < block->startPos.y - AUTO_DOOR_HEIGHT)
	{
		block->body.pos.y = block->startPos.y - AUTO_DOOR_HEIGHT;
		block->body.move.y = 0.0f;
	}
	else if (block->body.pos.y > (block->startPos.y))
	{
		block->body.pos.y = block->startPos.y;
		block->body.move.y = 0.0f;
	}
}

