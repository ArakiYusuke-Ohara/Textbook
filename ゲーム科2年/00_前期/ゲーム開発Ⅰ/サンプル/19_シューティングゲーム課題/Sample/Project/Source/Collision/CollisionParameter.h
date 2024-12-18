#pragma once

enum CollisionType
{
	COLLISION_AABB,
	COLLISION_SPHERE,
	COLLISION_TYPE_NONE = -1
};

// 弾の当たり判定で区別をつけるためのタグ
enum CollisionTag
{
	COLLISION_TAG_PLAYER,			// プレイヤー
	COLLISION_TAG_ENEMY,			// エネミー
	COLLISION_TAG_PLAYER_BULLET,	// プレイヤーバレット
	COLLISION_TAG_ENEMY_BULLET,		// エネミーバレット
	COLLISION_TAG_NONE = -1
};
