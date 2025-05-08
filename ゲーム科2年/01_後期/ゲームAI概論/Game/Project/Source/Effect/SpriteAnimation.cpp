#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation()
{
	m_Active = false;
	m_Handle = 0;
	m_NowFrame = 0;
	m_Timer = 0;
	m_Interval = 0;
	m_Pos = {};
	m_Param = nullptr;
}

SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::Step()
{
	if (!m_Active) return;

	// 次のコマへ進めるか
	if (m_Timer <= 0)
	{
		// 次のコマへ
		m_NowFrame++;
		// タイマーリセット
		m_Timer = m_Interval;

		// 全コマ表示し終わったら非アクティブ
		if (m_NowFrame >= m_Param->frameNum)
		{
			m_Active = false;

			// これ以上処理する必要なし
			return;
		}
	}

	m_Timer--;
}

void SpriteAnimation::Draw()
{
	if (!m_Active)return;

	// コマの切り取り位置計算（横１行の画像の想定）
	int frameX = m_Param->frameWidth * m_NowFrame;

	// 画像から表示するコマの部分だけ描画
	DrawRectGraph((int)m_Pos.x, (int)m_Pos.y, frameX, 0, m_Param->frameWidth, m_Param->frameHeight, m_Handle, TRUE);

}

void SpriteAnimation::Setup(int handle, const SpriteAnimationParam* param, VECTOR pos, int interval)
{
	m_Active = true;
	m_Handle = handle;
	m_NowFrame = 0;
	m_Param = param;
	m_Pos = pos;
	m_Interval = interval;
}
