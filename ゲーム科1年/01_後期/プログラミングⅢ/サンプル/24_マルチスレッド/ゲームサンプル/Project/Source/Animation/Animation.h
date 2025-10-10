#pragma once

class Animation
{
public:
	Animation(int handle);
	~Animation() = default;

public:
	void Play(int id, float playSpeed = 1.0f, bool isLoop = false);
	void Update();

private:
	int m_Handle;	// 3Dモデルのハンドル
	int m_AttachIndex;	// アニメーションのアタッチインデックス
	float m_TotalTime;	// 再生中のアニメーションの総時間
	float m_NowTime;	// 再生中のアニメーションの再生時間
	float m_PlaySpeed; // 再生速度
	bool m_IsLoop;		// アニメーションをループさせるか
	int m_PlayingID;	// 再生中のアニメーションID
};