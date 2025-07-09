#include "EffekseerForDXLib.h"
#include "EffekseerEffectBase.h"

EffekseerEffectBase::EffekseerEffectBase()
{
	m_Active = false;
	m_Is2D = false;
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
}

EffekseerEffectBase::~EffekseerEffectBase()
{

}
