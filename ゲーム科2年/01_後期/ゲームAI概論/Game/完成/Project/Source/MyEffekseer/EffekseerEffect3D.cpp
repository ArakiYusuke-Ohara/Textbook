#include "EffekseerForDXLib.h"
#include "EffekseerEffect3D.h"
#include "EffekseerEffectBase.h"

EffekseerEffect3D::EffekseerEffect3D()
{

}

EffekseerEffect3D::~EffekseerEffect3D()
{
}

void EffekseerEffect3D::Step()
{
	// çƒê∂íÜÇ©Ç«Ç§Ç©
	if (IsEffekseer3DEffectPlaying(m_Handle) != 0)
	{
		m_Active = false;
	}
}

void EffekseerEffect3D::Update()
{
	if (!m_Active) return;

	// à íuê›íË
	SetPosPlayingEffekseer3DEffect(m_Handle, m_Pos.x, m_Pos.y, m_Pos.z);
	// ägèkê›íË
	SetScalePlayingEffekseer3DEffect(m_Handle, m_Scale.x, m_Scale.y, m_Scale.z);
}

void EffekseerEffect3D::Play(int handle)
{
	m_Handle = PlayEffekseer3DEffect(handle);
	m_Active = true;
	m_Is2D = false;
}

void EffekseerEffect3D::Stop()
{
	StopEffekseer3DEffect(m_Handle);
	m_Active = false;
}
