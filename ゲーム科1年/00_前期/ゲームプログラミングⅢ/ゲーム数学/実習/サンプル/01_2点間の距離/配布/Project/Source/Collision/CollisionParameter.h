#pragma once

// ‘O•ûéŒ¾
struct BlockData;

struct Body
{
	bool isAir;
	float posX;
	float posY;
	float moveX;
	float moveY;
	float width;
	float height;
	const BlockData* groundBlock;
};
