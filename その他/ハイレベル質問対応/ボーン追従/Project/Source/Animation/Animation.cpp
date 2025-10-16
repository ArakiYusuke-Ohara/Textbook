#include "Animation.h"
#include "DxLib.h"

Animation::Animation(int handle)
{
	m_AttachIndex = 0;
	m_TotalTime = 0.0f;
	m_NowTime = 0.0f;
	m_PlaySpeed = 0.0f;
	m_IsLoop = false;
	m_PlayingID = -1;
	m_Handle = handle;
}

void Animation::Play(int id, float playSpeed, bool isLoop)
{
	// 再生中のアニメーションで呼ばれた場合は何もしない
	if (id == m_PlayingID) return;

	// 再生していたアニメーションはデタッチする
	MV1DetachAnim(m_Handle, m_AttachIndex);

	// アニメーションをアタッチする
	m_AttachIndex = MV1AttachAnim(m_Handle, id);

	// アニメーションのトータル時間を取得
	m_TotalTime = MV1GetAttachAnimTotalTime(m_Handle, m_AttachIndex);

	// 現在の再生時間を0にする
	m_NowTime = 0.0f;

	// 再生速度設定
	m_PlaySpeed = playSpeed;

	// ループ設定
	m_IsLoop = isLoop;

	// 再生中のアニメーション設定
	m_PlayingID = id;
}

void Animation::Update()
{
	// アニメーションの再生時間を設定
	MV1SetAttachAnimTime(m_Handle, m_AttachIndex, m_NowTime);

	// 再生時間を進める
	m_NowTime += m_PlaySpeed;

	// 末尾まで再生したか
	if (m_NowTime > m_TotalTime)
	{
		// ループ設定なら冒頭へ戻す
		if (m_IsLoop)
		{
			m_NowTime = 0.0f;
		}
		// ループでなければ末尾で止める
		else
		{
			m_NowTime = m_TotalTime;
		}
	}

}
