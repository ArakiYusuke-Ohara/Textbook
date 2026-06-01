#pragma once

#include "DxLib.h"

class CollisionSphere;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	// 各エネミー専用で処理を作る必要がない場合は基底クラスで共通処理にする
	virtual void Update();
	virtual void Draw();	
	virtual void Fin();

	// 複製、量産するためのクローン関数
	virtual EnemyBase* Clone() = 0;

	void Activate();
	void Damage(int damage = 1);

public:
	void SetPos(VECTOR pos) { m_Pos = pos; }

	bool IsActive() const { return m_Active; }
	CollisionSphere* GetCollision() const { return m_Collision; }

protected:
	bool m_Active;
	int m_Handle;
	int m_HP;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Move;
	CollisionSphere* m_Collision;
};


