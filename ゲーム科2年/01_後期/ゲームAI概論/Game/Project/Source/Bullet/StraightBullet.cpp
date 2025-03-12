#include "DxLib.h"
#include "StraightBullet.h"
#include "../MyMath/MyMath.h"
#include "../Player/PlayerManager.h"

StraightBullet::StraightBullet()
{
}

StraightBullet::~StraightBullet()
{
}

void StraightBullet::Step()
{
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
}

void StraightBullet::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
}

void StraightBullet::Draw()
{
	MV1DrawModel(m_Handle);
}

BulletBase* StraightBullet::Clone()
{
	StraightBullet* clone = new StraightBullet;
	*clone = *this;

	clone->m_Handle = MV1DuplicateModel(m_Handle);
	return clone;
}
