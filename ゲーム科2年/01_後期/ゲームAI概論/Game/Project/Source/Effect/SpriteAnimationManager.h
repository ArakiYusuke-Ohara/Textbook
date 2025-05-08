#pragma once
#include <vector>
#include "DxLib.h"
#include "../Singleton/Singleton.h"
#include "EffectParameter.h"

class SpriteAnimation;

class SpriteAnimationManager : public Singleton<SpriteAnimationManager>
{
public:
	SpriteAnimationManager();
	~SpriteAnimationManager();

public:
	void Load();
	void Step();
	void Draw();
	void Fin();

public:
	SpriteAnimation* Play(SpriteAnimationType type, VECTOR pos, int interval);

private:
	std::vector<SpriteAnimation*> m_Animations;
	int* m_Handles;
};