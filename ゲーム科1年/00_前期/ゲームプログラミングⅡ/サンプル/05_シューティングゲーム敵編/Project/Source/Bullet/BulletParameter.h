#pragma once

#define BULLET_MAX (128)
#define BULLET_RADIUS (15.0f)
#define BULLET_LIFE (120)
#define BULLET_SPEED (20.0f)

// íeÇÃÉfÅ[É^
struct BulletData
{
	bool active;
	int handle;
	int life;
	float posX;
	float posY;
	float moveX;
	float moveY;
};
