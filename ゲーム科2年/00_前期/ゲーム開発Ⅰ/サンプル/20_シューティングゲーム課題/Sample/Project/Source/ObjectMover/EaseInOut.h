#pragma once

#include "DxLib.h"
#include "ObjectMoverBase.h"
#include "ObjectMoverParameter.h"

class EaseInOut : public ObjectMoverBase
{
public:
	EaseInOut();
	~EaseInOut();

private:
	enum State {
		EASE_IN,
		WAIT,
		EASE_OUT,
		STATE_MAX
	};

public:
	void Play() override;
	void Update() override;

private:
	void UpdateEaseIn();
	void UpdateWait();
	void UpdateEaseOut();
	void StartEaseMove(VECTOR start, VECTOR end, int time);
	void UpdateEaseMove();

public:
	void SetParam(const EaseInOutParam* param) { m_Param = param; }

private:
	int m_Timer;
	float m_Radian;
	float m_RadianSpeed;
	VECTOR m_StartPos;
	VECTOR m_TargetVec;
	State m_State;
	const EaseInOutParam* m_Param;
	void (EaseInOut::* m_StepFunc[STATE_MAX])();
};
