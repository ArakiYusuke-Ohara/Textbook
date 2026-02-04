#pragma once

#include "DxLib.h"
#include "ObjectMoverBase.h"
#include "ObjectMoverParameter.h"

class Floating : public ObjectMoverBase
{
public:
	Floating();
	~Floating();

public:
	void Play()override;
	void Update()override;

public:
	void SetParam(FloatingParam param) { m_Param = param; }
	void SetMove(VECTOR move) { m_Move = move; }
	void SetStartPos(VECTOR pos) { m_StartPos = pos; }
	void SetLockX(bool lock) { m_LockFlag[0] = lock; }
	void SetLockY(bool lock) { m_LockFlag[1] = lock; }
	void SetLockZ(bool lock) { m_LockFlag[2] = lock; }

private:
	bool m_LockFlag[3];
	VECTOR m_Angle;
	VECTOR m_StartPos;
	VECTOR m_Move;
	FloatingParam m_Param;
};
