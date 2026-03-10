#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffekseerManager.h"
#include "EffekseerEffect.h"
#include "EffekseerParam.h"


EffekseerManager* EffekseerManager::m_Instance = nullptr;

EffekseerManager::EffekseerManager()
{
	m_EffectHandles = nullptr;
	m_Effects = nullptr;
}

EffekseerManager::~EffekseerManager()
{
	Fin();
}

void EffekseerManager::Setup()
{
	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);
}

bool EffekseerManager::Init()
{
	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(EFFEKSEER_MAX_PARTICLE) == -1)
	{
		return false;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	return true;
}

void EffekseerManager::Load()
{
	// 各エフェクトデータをロード
	m_EffectHandles = new int[EFFEKSEER_EFFECT_TYPE_MAX];
	m_EffectHandles[EFFEKSEER_HIT] = LoadEffekseerEffect("Data/Effect/EffectA.efkefc");
	m_EffectHandles[EFFEKSEER_FIRE] = LoadEffekseerEffect("Data/Effect/EffectB.efkefc");
	m_EffectHandles[EFFEKSEER_RING] = LoadEffekseerEffect("Data/Effect/EffectC.efkefc");
}

void EffekseerManager::Start()
{
	// 管理用の配列を生成
	m_Effects = new EffekseerEffect[EFFEKSEER_EFFECT_MAX];
}

EffekseerEffect* EffekseerManager::PlayEffect(int type, VECTOR pos)
{
	EffekseerEffect* effect = m_Effects;
	for (int i = 0; i < EFFEKSEER_EFFECT_MAX; i++, effect++)
	{
		if (!effect->IsActive())
		{
			// 未使用のエフェクトから使っていく
			effect->SetActive(true);

			// エフェクト再生
			effect->Play(m_EffectHandles[type]);

			// 位置設定
			effect->SetPos(pos);

			// 再生するエフェクトを返却
			return effect;
		}
	}

	return nullptr;
}

void EffekseerManager::Step()
{
	// 各エフェクトを更新
	EffekseerEffect* effect = m_Effects;
	for (int i = 0; i < EFFEKSEER_EFFECT_MAX; i++, effect++)
	{
		effect->Step();
	}
}

void EffekseerManager::Update()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	// 各エフェクトを更新
	EffekseerEffect* effect = m_Effects;
	for (int i = 0; i < EFFEKSEER_EFFECT_MAX; i++, effect++)
	{
		effect->Update();
	}

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void EffekseerManager::Draw()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}

void EffekseerManager::Fin()
{
	// ハンドル配列を削除
	if (m_EffectHandles)
	{
		// ロードしたものを削除
		for (int i = 0; i < EFFEKSEER_EFFECT_TYPE_MAX; i++)
		{
			DeleteEffekseerEffect(m_EffectHandles[i]);
		}

		// ハンドル配列も削除
		delete[] m_EffectHandles;
		m_EffectHandles = nullptr;
	}

	// 生成されたエフェクトを全て削除
	if (m_Effects)
	{
		delete[] m_Effects;
		m_Effects = nullptr;
	}

	// Effekseerを終了する。
	Effkseer_End();
}
