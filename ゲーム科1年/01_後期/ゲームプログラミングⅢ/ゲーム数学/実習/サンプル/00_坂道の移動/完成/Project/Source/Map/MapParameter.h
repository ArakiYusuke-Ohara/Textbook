#pragma once
#include "DxLib.h"

#define BLOCK_MAX 1024
#define MAP_CHIP_X_NUM (64)
#define MAP_CHIP_Y_NUM (18)
#define MAP_CHIP_WIDTH (50.0f)
#define MAP_CHIP_HEIGHT (50.0f)

enum MapChipType
{
	MAP_CHIP_NONE,
	NORMAL_BLOCK,
	SLOPE_BLOCK,
	AUTO_DOOR,
	BLOCK_TYPE_MAX,
};

struct BlockData
{
	bool active;
	int handle;
	MapChipType type;
	float posX;
	float posY;
	float moveX;
	float moveY;
	float width;
	float height;
	float startPosX;
	float startPosY;
	float prevPosX;
	float prevPosY;
};

struct MapChipData
{
	bool isCollision;
	int type;
	BlockData* data;
};

struct BlockMasterData
{
	int width;
	int height;
};
static const BlockMasterData BLOCK_MASTER_DATA[BLOCK_TYPE_MAX] =
{
	{ 0, 0 },	// MAP_CHIP_NONE
	{ 50, 50 },		// NORMAL_BLOCK
	{ 50, 50 },		// SLOPE_BLOCK
	{ 50, 100 },	// AUTO_DOOR
};
