#pragma once

enum class SpriteAnimationType
{
	NONE = -1,
	BULLET_HIT,
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
	{ "Data/", 6, 40, 40 },
};
