#pragma once

enum ItemType
{
	ITEM_TYPE_SPEED_UP,
	ITEM_TYPE_BULLET_UP,
	ITEM_TYPE_MAX
};

struct ItemParameter
{
	int id;
	float value;
	const char* path;
};

const ItemParameter ITEM_MASTER_PARAM[ITEM_TYPE_MAX] = {
	{ITEM_TYPE_SPEED_UP,  2.0f, "Data/Item/SpeedUp.png"},
	{ITEM_TYPE_BULLET_UP, 1.0f, "Data/Item/BulletUp.png"},
};
