#pragma once
#include "DxLib.h"
#include "../Object/Object.h"

class NormalCamera : public Object
{
public:
	NormalCamera();
	virtual ~NormalCamera();

	virtual void Update() override;

private:
	VECTOR m_TargetPos;
}
