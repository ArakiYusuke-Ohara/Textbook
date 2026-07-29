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
	VECTOR prevPos;
	const BlockData* groundBlock;
};
