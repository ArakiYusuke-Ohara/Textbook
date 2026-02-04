#pragma once

#include "EnemyBase.h"

class EffekseerEffectBase;
class Easing;

class EnemyDia : public EnemyBase
{
public:
	EnemyDia();
	~EnemyDia();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Dead() override;

	// •¡»A—ÊY‚·‚é‚½‚ß‚ÌƒNƒ[ƒ“ŠÖ”
	EnemyBase* Clone() override;

	void HitBullet(BulletBase* bullet) override;

public:
	bool m_IsBarrier;
	int m_BarrierHandle;
	int m_BarrierTimer;
	float m_BarrierScale;
	EffekseerEffectBase* m_BarrierEffect;
	Easing* m_BarrierEasing;
};