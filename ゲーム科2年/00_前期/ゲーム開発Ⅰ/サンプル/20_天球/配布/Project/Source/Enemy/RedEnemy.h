#pragma once
#include "EnemyBase.h"

class RedEnemy : public EnemyBase
{
public:
	RedEnemy();
	~RedEnemy();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	// Update, Draw, FinはEnemyBaseの処理で十分なので不要

	// 複製、量産するためのクローン関数
	EnemyBase* Clone() override;
};


