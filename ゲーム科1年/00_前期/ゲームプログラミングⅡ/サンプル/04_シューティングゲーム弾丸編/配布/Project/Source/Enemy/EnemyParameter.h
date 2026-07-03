#pragma once

#define ENEMY_MAX			(256)	// ìØéÌóﬁÇÃìGÇÃç≈ëÂèoåªêî

// ìGÇÃéÌóﬁ
enum EnemyType
{
	ENEMY_TYPE_FLIES,
	ENEMY_TYPE_DRAGON_FLY,
	ENEMY_TYPE_KAPU,
};

// ìGÇÃäÓî’Ç∆Ç»ÇÈã§í ÉfÅ[É^
struct EnemyBaseData
{
	int type;
	bool active;
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
};

// Fliesä÷òA ////////////////////////////////
#define ENEMY_FLIES_MAX			(32)
#define ENEMY_FLIES_RADIUS		(16.0f)	// îºåa
#define ENEMY_FLIES_WIDTH		(32.0f)	// â°ïù
#define ENEMY_FLIES_HEIGHT		(32.0f)	// ècïù


struct EnemyFliesData
{
	EnemyBaseData base;
	bool isMoveChange;
};

//////////////////////////////////////////////

// DragonFlyä÷òA ////////////////////////////////
#define ENEMY_DRAGON_FLY_MAX		(32)
#define ENEMY_DRAGON_FLY_RADIUS		(16.0f)	// îºåa
#define ENEMY_DRAGON_FLY_WIDTH		(32.0f)	// â°ïù
#define ENEMY_DRAGON_FLY_HEIGHT		(32.0f)	// ècïù

struct EnemyDragonFlyData
{
	EnemyBaseData base;
	int timer;
	int directionY;
	bool isMoveChange;
};

//////////////////////////////////////////////

// Kapuä÷òA ////////////////////////////////
#define ENEMY_KAPU_MAX			(32)
#define ENEMY_KAPU_RADIUS		(32.0f)	// îºåa
#define ENEMY_KAPU_WIDTH		(64.0f)	// â°ïù
#define ENEMY_KAPU_HEIGHT		(64.0f)	// ècïù

struct EnemyKapuData
{
	EnemyBaseData base;
	int bulletTimer;
	int hp;
	bool isMoveChange;
};

//////////////////////////////////////////////

