#pragma once

#define ITEM_WIDTH 40
#define ITEM_HEIGHT 40
#define ITEM_SPAWN_INTERVAL 600

enum ItemID
{
	ITEM_ID_SPEED_UP,
	ITEM_ID_BULLET_UP,
	ITEM_ID_MAX
};

struct ItemParameter
{
	int id;
	float value;
	const char* path;
};

const ItemParameter ITEM_MASTER_PARAM[ITEM_ID_MAX] = {
	{ITEM_ID_SPEED_UP,  2.0f, "Data/Item/SpeedUp.png"},
	{ITEM_ID_BULLET_UP, 1.0f, "Data/Item/BulletUp.png"},
};
