#include "BGObject.h"
#include "../ObjectMover/Floating.h"
#include "../Player/PlayerManager.h"

BGObject::BGObject()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_FloatingMover = nullptr;
}

BGObject::~BGObject()
{
	Fin();
}

void BGObject::Create(int handle)
{
	m_Handle = MV1DuplicateModel(handle);
	m_Active = true;
}

void BGObject::Update()
{
	if (m_FloatingMover)
	{
		m_FloatingMover->Update();
	}

	VECTOR pos = PlayerManager::GetInstance()->ConvertPlayerLocalPos(m_Pos);
	MV1SetPosition(m_Handle, pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void BGObject::Draw()
{
	MV1DrawModel(m_Handle);
}

void BGObject::Fin()
{
	MV1DeleteModel(m_Handle);
}

void BGObject::	SetFloatingMover(Floating* mover) 
{ 
	m_FloatingMover = mover; 
	m_FloatingMover->SetObjectPos(&m_Pos);
	m_FloatingMover->SetStartPos(m_Pos);
}

