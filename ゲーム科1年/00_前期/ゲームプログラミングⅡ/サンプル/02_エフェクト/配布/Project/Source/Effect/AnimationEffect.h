#pragma once
#include "AnimationEffectParameter.h"

// 画面に表示できるエフェクトの最大数
#define ANIMATION_EFFECT_MAX 255

// エフェクトデータ
struct AnimationEffectData
{
	bool active;
	int handle;
	int nowFrame;
	int frameNum;
	int frameWidth;
	int frameHeight;
	int timer;
	int interval;
	float posX;
	float posY;
};

// 各関数の宣言
void InitAnimationEffect();
void LoadAnimationEffect();
void StepAnimationEffect();
void UpdateAnimationEffect();
void DrawAnimationEffect();
void FinAnimationEffect();

// エフェクト開始
void PlayAnimationEffect(AnimationEffectType type, float posX, float posY, int interval);

