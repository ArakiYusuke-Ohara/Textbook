#pragma once

#include "DxLib.h"

// Effekseerエフェクト１つ分のクラス
class EffekseerEffectBase
{
public:
	EffekseerEffectBase();	// コンストラクタ
	virtual ~EffekseerEffectBase();	// デストラクタ

public:
	virtual void Step() = 0;	// ステップ
	virtual void Update() = 0;	// 更新
	virtual void Play(int handle) = 0;	// 再生
	virtual void Stop() = 0;	// 停止

	// 必要なアクセサ
	bool IsActive() const { return m_Active; }
	bool Is2D() const { return m_Is2D; }

	void SetActive(bool active) { m_Active = active; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetScale(VECTOR scale) { m_Scale = scale; }

protected:
	bool m_Active;	// アクティブフラグ
	bool m_Is2D;
	int m_Handle;	// プレイハンドル（注意：リソースハンドルではない）
	VECTOR m_Pos;	// 座標
	VECTOR m_Scale;	// 座標
};


