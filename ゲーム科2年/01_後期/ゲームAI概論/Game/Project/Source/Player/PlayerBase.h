#pragma once
#include "DxLib.h"

// ヘッダーにインクルードを書きたくないので前方定義
class CollisionAABB;
class CollisionSphere;
class BulletBase;
class EnemyBase;
class AIStrategyBase;
class Block;
class Item;
class UIImage;
class UIGauge;

class PlayerBase
{
protected:
	PlayerBase();
	virtual ~PlayerBase();

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	virtual void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

public:
	bool IsActive() const { return m_Active; }
	bool IsInvisible() const { return m_InvisibleTimer > 0; }
	bool IsBulletInterval() const { return m_BulletInterval > 0; }
	int GetHP() const { return m_HP; }
	VECTOR GetPos() const { return m_Pos; }
	CollisionAABB* GetCollisionAABB() const { return m_CollisionAABB; }
	CollisionSphere* GetCollisionSphere() const { return m_CollisionSphere; }

	void SetActive(bool active) { m_Active = active; }
	void SetPlayerNumber(int number) { m_PlayerNumber = number; }

	void FireBullet();
	void Dead();

	void UpdateAnimation();

	void HitBlock(Block* block);
	void HitBullet();
	void HitItem(Item* item);

protected:
	void SetDirectionForMove();

private:
	void LoadUI();
	void LocateUI();
	void Damage(int damage);

protected:
	bool m_Active;
	int m_Handle;
	int m_PlayerNumber;
	int m_HP;
	int m_InvisibleTimer;
	int m_Direction;
	int m_AnimationIndex;
	int m_AnimationTimer;
	int m_UseBulletID;
	int m_Stiffness;
	float m_BulletInterval;
	float m_BulletIntervalTime;
	float m_BulletChargeSpeed;
	float m_MoveSpeed;
	float m_BulletSpeed;
	VECTOR m_Pos;
	VECTOR m_OldPos;
	VECTOR m_Move;
	CollisionAABB* m_CollisionAABB;
	CollisionSphere* m_CollisionSphere;
	UIImage** m_UIHP;
	UIGauge* m_BulletChargeGauge;
};