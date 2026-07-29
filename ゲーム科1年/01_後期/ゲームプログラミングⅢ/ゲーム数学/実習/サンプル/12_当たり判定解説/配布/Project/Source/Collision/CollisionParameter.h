#pragma once

// ‘O•ûéŒ¾
struct BlockData;

struct Body
{
	bool isAir;
	VECTOR pos;
	VECTOR move;
	float width;
	float height;
	float radius;
	float reflactPower;
	VECTOR prevPos;
	const BlockData* hitBlock;
	const BlockData* groundBlock;
};
