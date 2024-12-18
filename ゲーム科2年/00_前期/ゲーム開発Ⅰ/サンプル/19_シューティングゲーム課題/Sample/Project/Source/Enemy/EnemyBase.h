#pragma once

#include "DxLib.h"
#include "EnemyParameter.h"

class CollisionSphere;
class BulletBase;
class ObjectMoverBase;

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

	// 登録されたパラメータを元に準備
	void Setup();

	// 死亡
	virtual void Dead();

public:
	bool IsActive() const { return m_Active; }
	bool IsDead() const { return m_Hp <= 0; }
	int GetHP() const { return m_Hp; }
	VECTOR GetPos() const { return m_Pos; }
	float GetEncountDist() const{ return m_EncountDist; }
	const EnemyParameter* GetParam() const { return m_Param; }
	const EnemyLocate* GetLocate() const { return m_Locate; }
	CollisionSphere* GetCollision() const { return m_Collision; }

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetActive(bool active) { m_Active = active; }
	void SetEncountDist(float dist) { m_EncountDist = dist; }
	void SetParameter(const EnemyParameter* param) { m_Param = param; }
	void SetLocate(const EnemyLocate* locate) { m_Locate = locate; }
	void SetMover(ObjectMoverBase* mover);

	virtual void HitBullet(BulletBase* bullet);

protected:
	bool m_Active;
	int m_Handle;
	int m_Hp;
	int m_Interval;
	int m_DeadEffectID;
	float m_EncountDist;
	VECTOR m_Pos;
	VECTOR m_DrawPos;
	VECTOR m_Rot;
	VECTOR m_Move;
	const EnemyParameter* m_Param;
	const EnemyLocate* m_Locate;
	ObjectMoverBase* m_Mover;
	CollisionSphere* m_Collision;
};


