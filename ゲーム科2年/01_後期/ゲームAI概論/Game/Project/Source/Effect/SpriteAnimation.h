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

	void Setup(int handle, const SpriteAnimationParam* param, VECTOR pos, int interval, bool loop = false);

public:
	bool IsActive() const { return m_Active; }
	bool IsHide() const { return m_Hide; }

	void SetActive(bool active) { m_Active = active; }
	void SetHide(bool hide) { m_Hide = hide; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetInterval(int interval) { m_Interval = interval; }

private:
	bool m_Active;
	bool m_Hide;
	bool m_Loop;
	int m_Handle;
	int m_NowFrame;
	int m_Timer;
	int m_Interval;
	VECTOR m_Pos;
	const SpriteAnimationParam* m_Param;
};