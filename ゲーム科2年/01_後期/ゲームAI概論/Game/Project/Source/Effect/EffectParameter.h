#pragma once

enum class SpriteAnimationType
{
	NONE = -1,
	ITEM_SPEED_UP,
	ITEM_RAPID_UP,
	ITEM_BULLET_SPEED_UP,
	MAX
};

struct SpriteAnimationParam
{
	const char* path;	// 画像パス
	int frameNum;		// フレーム数
	int frameWidth;		// 1コマの横幅
	int frameHeight;	// 1コマの縦幅
};

const SpriteAnimationParam SPRITE_ANIM_MASTER_PARAM[] =
{
	{ "Data/Play/Item/SpeedUp.png", 4, 40, 40 },
	{ "Data/Play/Item/BulletRapidUp.png", 4, 40, 40 },
	{ "Data/Play/Item/BulletSpeedUp.png", 4, 40, 40 },
};
