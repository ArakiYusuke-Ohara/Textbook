#pragma once

// “–‚½‚è”»’è¬”Œë·‹–—e’l
#define COLLISION_EPS (0.001f)

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
	const Body* hitBody;
	const Body* groundBody;
};
