#pragma once

#define STRAIGHT_BULLET_MAX (1024)

// 発射する弾丸のカテゴリ
enum BulletCategory
{
	BULLET_CATEGORY_STRAIGHT,
};

// 直線弾の種類
enum StraightBulletType
{
	STRAIGHT_BULLET_TYPE_PLAYER_NORMAL,	// プレイヤーの通常弾
	STRAIGHT_BULLET_TYPE_KAPU,			// カプが撃つ弾
	STRAIGHT_BULLET_TYPE_MAX
};

// バレットのパラメータ
struct BulletParameter
{
	char path[64];
	BulletCategory category;
	int life;
	int damage;
	int collisionTag;
	int hitEffect;
	float speed;
	float radius;
};

// 発射に必要なデータ
struct FireBulletData
{
	int life;
	float posX;
	float posY;
	float moveX;
	float moveY;
};

