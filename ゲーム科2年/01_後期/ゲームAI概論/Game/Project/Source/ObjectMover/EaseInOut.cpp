#include "EaseInOut.h"
#include "../MyMath/MyMath.h"
#include <math.h>

EaseInOut::EaseInOut()
{
	m_Timer = 0;
	m_Radian = 0.0f;
	m_RadianSpeed = 0.0f;
	m_StartPos = VGet(0.0f, 0.0f, 0.0f);
	m_TargetVec = VGet(0.0f, 0.0f, 0.0f);
	m_State = EASE_IN;
	m_Param = {};
	m_StepFunc[EASE_IN] = &EaseInOut::UpdateEaseIn;
	m_StepFunc[WAIT] = &EaseInOut::UpdateWait;
	m_StepFunc[EASE_OUT] = &EaseInOut::UpdateEaseOut;
}

EaseInOut::~EaseInOut()
{
}

void EaseInOut::Play()
{
	ObjectMoverBase::Play();

	m_State = EASE_IN;
	StartEaseMove(*m_ObjectPos, m_Param->easeInTarget, m_Param->easeInTime);
}

void EaseInOut::Update()
{
	if (!m_Active) return;

	(this->*m_StepFunc[m_State])();
}

void EaseInOut::UpdateEaseIn()
{
	UpdateEaseMove();

	// イーズイン時間になったら待機状態へ
	if (m_Timer >= m_Param->easeInTime)
	{
		m_State = WAIT;
		*m_ObjectPos = m_Param->easeInTarget;
		m_Timer = 0;
	}
	else
	{
		// タイマーを進める
		m_Timer++;
	}
}

void EaseInOut::UpdateWait()
{
	// 時間になったらイーズアウト状態へ
	if (m_Timer >= m_Param->waitTime)
	{
		m_State = EASE_OUT;
		StartEaseMove(m_Param->easeInTarget, m_Param->easeOutTarget, m_Param->easeOutTime);
	}
	else
	{
		// タイマーを進める
		m_Timer++;
	}
}

void EaseInOut::UpdateEaseOut()
{
	UpdateEaseMove();

	// イーズアウト時間になったら終了
	if (m_Timer >= m_Param->easeOutTime)
	{
		m_Active = false;
	}
	else
	{
		// タイマーを進める
		m_Timer++;
	}

}

void EaseInOut::StartEaseMove(VECTOR start, VECTOR end, int time)
{
	// スタート座標
	m_StartPos = start;

	// イーズイン先までのベクトル
	m_TargetVec = MyMath::VecCreate(m_StartPos, end);

	// sin関数に渡すラジアン角の増加値
	m_RadianSpeed = DX_PI_F / 2.0f / (float)time;

	// ラジアン角リセット
	m_Radian = 0.0f;

	// タイマーリセット
	m_Timer = 0;
}

void EaseInOut::UpdateEaseMove()
{
	// sinf関数から0～1.0の値を取得
	float sin = sinf(m_Radian);

	// イーズイン先までのベクトルを上の値でスケール
	VECTOR targetMove = MyMath::VecScale(m_TargetVec, sin);

	// スタート位置に上のベクトルを足すことにより
	// 0をスタート、1.0をイーズイン先とした座標を求めることができる
	*m_ObjectPos = MyMath::VecAdd(m_StartPos, targetMove);

	// ラジアン角を加算
	m_Radian += m_RadianSpeed;
}
