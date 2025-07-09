#include "DxLib.h"
#include "Easing.h"
#include <cmath>

float (*Easing::m_EasingFunc[4])(float) = {
	& EaseInSlide,
	& EaseOutSlide,
	& EaseOutElastic,
	& EaseInOutElastic,
};

Easing::Easing()
{
	m_Active = false;
	m_Type = -1;
	m_Time = 0;
	m_TimeCounter = 0;
	m_Progress = 0.0f;
	m_Value = 0.0f;
}

Easing::~Easing()
{
}

void Easing::Play(int type, int time, bool reverse)
{
	m_Active = true;
	m_Reverse = reverse;
	m_Type = type;
	m_Time = time;
	m_TimeCounter = 0;
	m_Progress = 0.0f;
	m_Value = 0.0f;
}

void Easing::Update()
{
	if (m_Time <= 0) return;

	// 進行度を進める
	m_Progress = (float)m_TimeCounter / (float)m_Time;

	// 逆再生対応
	if (m_Reverse)m_Progress = 1.0f - m_Progress;

	// イージング関数から曲線の値を取得
	m_Value = (*m_EasingFunc[m_Type])(m_Progress);


	// 指定時間になったら止める
	if (IsEnd())
	{
		m_Progress = 1.0f;

		// 自動削除がONなら非アクティブ
		if (m_AutoDelete) m_Active = false;
	}
	else
	{
		// タイマーを進める
		m_TimeCounter++;
	}

}

// ここからEasing関数群

float Easing::EaseInSlide(float progress)
{
	return 1.0f - std::cosf((progress * DX_PI_F) / 2.0f);
}

float Easing::EaseOutSlide(float progress)
{
	return std::sinf((progress * DX_PI_F) / 2.0f);
}

float Easing::EaseOutElastic(float progress)
{
	if (progress == 0) return 0.0f;  // 初期値
	if (progress == 1) return 1.0f;  // 終了値

	const float c = (2.0f * DX_PI_F) / 3.0f;
	return std::pow(2.0f, -10.0f * progress)* std::sinf((progress * 10.0f - 0.75f) * c) + 1.0f;
}

float Easing::EaseInOutElastic(float progress)
{
	if (progress == 0) return 0.0f;  // 初期値
	if (progress == 1) return 1.0f;  // 終了値

	const float c = (2.0f * DX_PI_F) / 4.5f;

	if (progress < 0.5f)
	{
		return -(std::pow(2.0f, 20.0f * progress - 10.0f) * std::sinf((20.0f * progress - 11.125f) * c)) / 2.0f;
	}

	return (std::pow(2.0f, -20.0f * progress + 10.0f) * std::sinf((20.0f * progress - 11.125f) * c)) / 2.0f + 1.0f;
}
