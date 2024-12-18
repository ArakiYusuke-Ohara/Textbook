#include "Sky.h"

Sky::Sky()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
}

Sky::~Sky()
{
	Fin();
}

void Sky::Init()
{
}

void Sky::Load(const char* path)
{
	m_Handle = MV1LoadModel(path);
}

void Sky::Start()
{
}

void Sky::Step()
{
}

void Sky::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void Sky::Draw()
{
	MV1DrawModel(m_Handle);
}

void Sky::Fin()
{
	MV1DeleteModel(m_Handle);
}


