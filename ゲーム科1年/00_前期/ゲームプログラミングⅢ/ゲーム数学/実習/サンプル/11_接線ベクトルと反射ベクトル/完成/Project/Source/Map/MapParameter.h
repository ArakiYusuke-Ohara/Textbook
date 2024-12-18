#pragma once
#include "DxLib.h"

#define BLOCK_MAX 1024
#define MAP_CHIP_X_NUM (64)
#define MAP_CHIP_Y_NUM (18)
#define MAP_CHIP_WIDTH (50.0f)
#define MAP_CHIP_HEIGHT (50.0f)

#define AUTO_DOOR_WIDTH (50.0f)
#define AUTO_DOOR_HEIGHT (100.0f)

#define ARCH_BLOCK_WIDTH (150.0f)
#define ARCH_BLOCK_HEIGHT (50.0f)
#define ARCH_BLOCK_SPEED (0.5f)

#define REFLACT_BLOCK_WIDTH (50.0f)
#define REFLACT_BLOCK_HEIGHT (100.0f)


enum MapChipType
{
	MAP_CHIP_NONE,
	NORMAL_BLOCK,
	SLOPE_BLOCK,
	MAP_CHIP_TYPE_MAX,
};

enum MoveBlockMode
{
	MOVE_BLOCK_MODE_ARCH,	// ï˙ï®ê¸à⁄ìÆ
	MOVE_BLOCK_MODE_SIN,	// Sinîgà⁄ìÆ
	MOVE_BLOCK_MODE_CIRCLE,	// â~à⁄ìÆ
	MOVE_BLOCK_MODE_NONE = -1
};

struct BlockData
{
	bool active;
	int handle;
	MapChipType type;
	VECTOR pos;
};

struct MapChipData
{
	int mapChip;
	BlockData* data;
};

struct AutoDoorData
{
	bool active;
	bool isOpen;
	VECTOR pos;
	VECTOR startPos;
	int handle;
};

struct MoveBlockData
{
	bool active;
	int handle;
	int dir;
	VECTOR pos;
	VECTOR startPos;
	VECTOR oldPos;
	VECTOR archTopPos;
	float sinAngle;
	float sinRange;
	float circleAngle;
	MoveBlockMode mode;
};

struct ReflactBlockData
{
	bool active;
	int handle;
	VECTOR pos;
	VECTOR normal;
};
