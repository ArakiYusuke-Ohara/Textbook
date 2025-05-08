#pragma once
#include "DxLib.h"
#include "EffectParameter.h"


class SpriteAnimation
{
public:
	SpriteAnimation();
	~SpriteAnimation();

public:
	void Step();
	void Draw();

	void Setup(int handle, const SpriteAnimationParam* param, VECTOR pos, int interval);

public:
	bool IsActive() const { return m_Active; }

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetInterval(int interval) { m_Interval = interval; }

private:
	bool m_Active;
	int m_Handle;
	int m_NowFrame;
	int m_Timer;
	int m_Interval;
	VECTOR m_Pos;
	const SpriteAnimationParam* m_Param;
};