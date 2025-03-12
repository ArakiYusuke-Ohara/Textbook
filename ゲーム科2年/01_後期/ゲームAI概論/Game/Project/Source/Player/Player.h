#pragma once
#include "DxLib.h"

// ヘッダーにインクルードを書きたくないので前方定義
class CollisionAABB;
class BulletBase;
class EnemyBase;
class AIStrategyBase;

// プレイヤークラス
class Player 
{
public:
	Player();	// コンストラクタ
	~Player();	// デストラクタ

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

public:
	bool IsActive() const { return m_Active; }
	bool IsInvisible() const { return m_InvisibleTimer > 0; }
	int GetHP() const { return m_Hp; }
	VECTOR GetPos() const { return m_Pos; }
	CollisionAABB* GetCollision() const { return m_Collision; }

	void SetActive(bool active) { m_Active = active; }
	void SetPlayerNumber(int number) { m_PlayerNumber = number; }
	void SetAIStrategy(AIStrategyBase* strategy) { m_AIStrategy = strategy; }

	void Dead();

	void Move();
	void AIMove();
	void UpdateAnimation();

private:
	bool m_Active;
	int m_Handle;	
	int m_PlayerNumber;
	int m_Hp;
	int m_InvisibleTimer;
	int m_BulletInterval;
	int m_Direction;
	int m_AnimationIndex;
	int m_AnimationTimer;
	VECTOR m_Pos;	
	VECTOR m_OldPos;
	VECTOR m_Move;	
	CollisionAABB* m_Collision;
	AIStrategyBase* m_AIStrategy;
};

