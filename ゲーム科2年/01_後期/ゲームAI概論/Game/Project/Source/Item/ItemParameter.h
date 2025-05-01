#pragma once

#define ITEM_WIDTH 40
#define ITEM_HEIGHT 40

enum ItemID
{
	ITEM_ID_PLAYER_SPEED_UP,
	ITEM_ID_BULLET_RAPID_UP,
	ITEM_ID_BULLET_SPEED_UP,
	ITEM_ID_MAX
};

struct ItemParameter
{
	int id;
	float value;
	const char* path;
};

const ItemParameter ITEM_MASTER_PARAM[ITEM_ID_MAX] = {
	{ITEM_ID_PLAYER_SPEED_UP,	1.0f,	"Data/Item/SpeedUp.png"},
	{ITEM_ID_BULLET_RAPID_UP,	0.5f,	"Data/Item/BulletRapidUp.png"},
	{ITEM_ID_BULLET_SPEED_UP,	0.5f,	"Data/Item/BulletSpeedUp.png"},
};
