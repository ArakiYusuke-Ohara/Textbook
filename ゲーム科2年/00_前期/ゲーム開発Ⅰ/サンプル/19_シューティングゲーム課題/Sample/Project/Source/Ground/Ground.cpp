#include "Ground.h"

Ground::Ground()
{
	m_Handle = 0;
	m_TextureV = 0.0f;
	m_ScrollSpeed = 0.0f;
}

Ground::~Ground()
{
	Fin();
}

void Ground::Init()
{
}

void Ground::Load(const char* path)
{
	m_Handle = MV1LoadModel(path);
}

void Ground::Start()
{
}

void Ground::Step()
{
}

void Ground::Update()
{
	// テクスチャ座標を移動
	m_TextureV -= m_ScrollSpeed;

	// -1～0をループ
	if (m_TextureV < -1.0f)
	{
		m_TextureV += 1.0f;
	}

	MV1SetFrameTextureAddressTransform(m_Handle, 0, 0.0f, m_TextureV, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
}

void Ground::Draw()
{
	MV1DrawModel(m_Handle);
}

void Ground::Fin()
{
	MV1DeleteModel(m_Handle);
}


