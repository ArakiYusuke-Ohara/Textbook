#pragma once

#include "DxLib.h"
#include "EffekseerEffectBase.h"

// Effekseerエフェクト１つ分のクラス
class EffekseerEffect2D : public EffekseerEffectBase
{
public:
	EffekseerEffect2D();	// コンストラクタ
	~EffekseerEffect2D();	// デストラクタ

public:
	void Step() override;	// ステップ
	void Update() override;	// 更新
	void Play(int handle) override;	// 再生
	void Stop() override;	// 停止
};


