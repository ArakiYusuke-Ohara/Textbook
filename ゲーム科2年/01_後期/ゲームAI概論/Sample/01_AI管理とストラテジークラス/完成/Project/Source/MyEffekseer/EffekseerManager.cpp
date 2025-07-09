#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffekseerManager.h"
#include "EffekseerEffectBase.h"
#include "EffekseerParameter.h"
#include "EffekseerEffect2D.h"
#include "EffekseerEffect3D.h"
#include "../Player/PlayerManager.h"

EffekseerManager* EffekseerManager::m_Instance = nullptr;

EffekseerManager::EffekseerManager()
{
	m_EffectHandls = nullptr;
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

	Effekseer_Set2DSetting(1600, 900);

	return true;
}

void EffekseerManager::Load()
{
	// 各エフェクトデータをロード
	m_EffectHandls = new int[EFFEKSEER_EFFECT_TYPE_MAX];
	m_EffectHandls[EFFEKSEER_PLAYER_DAMAGE] = LoadEffekseerEffect("Data/Effect/PlayerDamage.efkefc");
	m_EffectHandls[EFFEKSEER_PLAYER_NORMAL_SHOT_HIT] = LoadEffekseerEffect("Data/Effect/PlayerNormalShotHit.efkefc");
	m_EffectHandls[EFFEKSEER_PLAYER_LOCK_ON] = LoadEffekseerEffect("Data/Effect/PlayerLockOn.efkefc");
	m_EffectHandls[EFFEKSEER_BEE_SHOT_HIT] = LoadEffekseerEffect("Data/Effect/BeeShotHit.efkefc");
	m_EffectHandls[EFFEKSEER_BEE_DEAD] = LoadEffekseerEffect("Data/Effect/BeeDead.efkefc");
	m_EffectHandls[EFFEKSEER_BARRIER] = LoadEffekseerEffect("Data/Effect/Barrier.efkefc");
	m_EffectHandls[EFFEKSEER_GUARD] = LoadEffekseerEffect("Data/Effect/Guard.efkefc");
}

void EffekseerManager::Start()
{

}

void EffekseerManager::Step()
{
	// 各エフェクトを更新
	for (EffekseerEffectBase* effect : m_Effects)
	{
		effect->Step();
	}
}

void EffekseerManager::Update()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	// 各エフェクトを更新
	for (EffekseerEffectBase* effect : m_Effects)
	{
		effect->Update();
	}

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
	UpdateEffekseer2D();
}

void EffekseerManager::Draw()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
	DrawEffekseer2D();
}

void EffekseerManager::Fin()
{
	// ハンドル配列を削除
	if (m_EffectHandls)
	{
		// ロードしたものを削除
		for (int i = 0; i < EFFEKSEER_EFFECT_TYPE_MAX; i++)
		{
			DeleteEffekseerEffect(m_EffectHandls[i]);
		}

		// ハンドル配列も削除
		delete[] m_EffectHandls;
		m_EffectHandls = nullptr;
	}

	// 生成されたエフェクトを全て削除
	for (EffekseerEffectBase* effect : m_Effects)
	{
		delete effect;
	}

	m_Effects.clear();

	// Effekseerを終了する。
	Effkseer_End();
}

EffekseerEffectBase* EffekseerManager::PlayEffect2D(int type, VECTOR pos, VECTOR scale)
{
	for (EffekseerEffectBase* effect : m_Effects)
	{
		if (!effect->IsActive() && effect->Is2D())
		{
			// 未使用のエフェクトから使っていく
			effect->Play(m_EffectHandls[type]);

			// 位置と拡縮設定
			effect->SetPos(pos);
			effect->SetScale(scale);

			// 再生するエフェクトを返却
			return effect;
		}
	}

	EffekseerEffect2D* effect = new EffekseerEffect2D;
	// エフェクト再生
	effect->Play(m_EffectHandls[type]);
	// 位置と拡縮設定
	effect->SetPos(pos);
	effect->SetScale(scale);
	// 管理配列に追加
	m_Effects.push_back(effect);

	return effect;
}

EffekseerEffectBase* EffekseerManager::PlayEffect3D(int type, VECTOR pos, VECTOR scale)
{
	for (EffekseerEffectBase* effect : m_Effects)
	{
		if (!effect->IsActive() && !effect->Is2D())
		{
			// 未使用のエフェクトから使っていく
			effect->Play(m_EffectHandls[type]);

			// 位置と拡縮設定
			effect->SetPos(pos);
			effect->SetScale(scale);

			// 再生するエフェクトを返却
			return effect;
		}
	}

	EffekseerEffect3D* effect = new EffekseerEffect3D;
	// エフェクト再生
	effect->Play(m_EffectHandls[type]);
	// 位置と拡縮設定
	effect->SetPos(pos);
	effect->SetScale(scale);
	// 管理配列に追加
	m_Effects.push_back(effect);

	return effect;
}
