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
	COLLISION_TAG_PLAYER1,			// プレイヤー
	COLLISION_TAG_PLAYER2,			// プレイヤー
	COLLISION_TAG_PLAYER3,			// プレイヤー
	COLLISION_TAG_PLAYER4,			// プレイヤー
	COLLISION_TAG_PLAYER1_BULLET,	// プレイヤーバレット
	COLLISION_TAG_PLAYER2_BULLET,	// プレイヤーバレット
	COLLISION_TAG_PLAYER3_BULLET,	// プレイヤーバレット
	COLLISION_TAG_PLAYER4_BULLET,	// プレイヤーバレット
	COLLISION_TAG_NONE = -1
};
