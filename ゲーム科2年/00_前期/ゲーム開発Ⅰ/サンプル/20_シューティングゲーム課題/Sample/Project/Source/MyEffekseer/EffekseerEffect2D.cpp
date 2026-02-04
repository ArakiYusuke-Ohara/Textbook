#include "EffekseerForDXLib.h"
#include "EffekseerEffect2D.h"
#include "EffekseerEffectBase.h"

EffekseerEffect2D::EffekseerEffect2D()
{

}

EffekseerEffect2D::~EffekseerEffect2D()
{
}

void EffekseerEffect2D::Step()
{
	// çƒê∂íÜÇ©Ç«Ç§Ç©
	if (IsEffekseer2DEffectPlaying(m_Handle) != 0)
	{
		m_Active = false;
	}
}

void EffekseerEffect2D::Update()
{
	if (!m_Active) return;

	// à íuê›íË
	SetPosPlayingEffekseer2DEffect(m_Handle, m_Pos.x, m_Pos.y, 0.0f);
}

void EffekseerEffect2D::Play(int handle)
{
	m_Handle = PlayEffekseer2DEffect(handle);
	m_Active = true;
	m_Is2D = true;
}

void EffekseerEffect2D::Stop()
{
	StopEffekseer2DEffect(m_Handle);
	m_Active = false;
}
