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
	ARCH_MOVE_BLOCK,
	MOVE_BLOCK,
	CIRCLE_MOVE_BLOCK,
	REFLACT_BLOCK,
	BLOCK_TYPE_MAX,
};

struct BlockData
{
	bool active;
	bool isReflact;
	int handle;
	MapChipType type;
	VECTOR pos;
	VECTOR move;
	float width;
	float height;
	VECTOR startPos;
	VECTOR prevPos;
	float sin;
	float cos;
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
	bool isReflact;
};
static const BlockMasterData BLOCK_MASTER_DATA[BLOCK_TYPE_MAX] =
{
	{ 0, 0, false },			// MAP_CHIP_NONE
	{ 50, 50, false },		// NORMAL_BLOCK
	{ 50, 50, false },			// SLOPE_BLOCK
	{ 50, 100, false },			// AUTO_DOOR
	{ 150, 50, false },	// ARCH_MOVE_BLOCK
	{ 150, 50, false },			// MOVE_BLOCK
	{ 150, 50, false },	// CIRCLE_MOVE_BLOCK
	{ 50, 100, true },		// REFLACT_BLOCK
};
