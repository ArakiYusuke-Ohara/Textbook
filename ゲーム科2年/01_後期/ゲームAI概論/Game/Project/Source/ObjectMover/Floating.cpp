#include "Floating.h"
#include "../MyMath/MyMath.h"
#include <math.h>

Floating::Floating()
{
	for (int i = 0; i < 3; i++)
	{
		m_LockFlag[i] = false;
	}
	m_Angle = VGet(0.0f, 0.0f, 0.0f);
	m_StartPos = VGet(0.0f, 0.0f, 0.0f);
	m_Param = {};
}

Floating::~Floating()
{
}

void Floating::Play()
{
	ObjectMoverBase::Play();

	m_Angle = VGet(0.0f, 0.0f, 0.0f);
}

void Floating::Update()
{
	VECTOR pos = {};
	// X
	if (!m_LockFlag[0])
	{
		pos.x = m_StartPos.x + sinf(m_Angle.x) * m_Param.width.x;
		(*m_ObjectPos).x = pos.x;
		m_Angle.x = MyMath::RadianNormalize(m_Angle.x);
	}
	// Y
	if (!m_LockFlag[1])
	{
		pos.y = m_StartPos.y + sinf(m_Angle.y) * m_Param.width.y;
		(*m_ObjectPos).y = pos.y;
		m_Angle.y = MyMath::RadianNormalize(m_Angle.y);
	}
	// Z
	if (!m_LockFlag[2])
	{
		pos.z = m_StartPos.z + sinf(m_Angle.z) * m_Param.width.z;
		(*m_ObjectPos).z = pos.z;
		m_Angle.z = MyMath::RadianNormalize(m_Angle.z);
	}

	m_Angle = MyMath::VecAdd(m_Angle, m_Param.speed);
}
