#pragma once
#include "EnemyBase.h"

class EnemyBoss : public EnemyBase
{
public:
	EnemyBoss();
	virtual ~EnemyBoss();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Dead() override;

	// •¡»A—ÊY‚·‚é‚½‚ß‚ÌƒNƒ[ƒ“ŠÖ”
	EnemyBase* Clone() override;

private:
	void RedShot();
	void GreenShot();
	void BlueShot();
	void YellowShot();
	void MainShot();
};