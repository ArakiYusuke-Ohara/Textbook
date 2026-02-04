#pragma once
#include "DxLib.h"

// ヘッダーにインクルードを書きたくないので前方定義
class CollisionSphere;
class BulletBase;
class EnemyBase;

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
	CollisionSphere* GetCollision() const { return m_Collision; }

	void SetActive(bool active) { m_Active = active; }

	void HitEnemyBullet(BulletBase* bullet);
	void Dead();

private:
	VECTOR CalcBulletVec();
	void SearchLockEnemy();

private:
	bool m_Active;
	int m_Handle;	// モデル画像ハンドル
	int m_NormalCursorHandle;
	int m_LockCursorHandle;
	int m_NormalBulletId;	// 通常弾のID
	int m_NormalBulletInterval;
	int m_Hp;
	int m_InvisibleTimer;
	VECTOR m_Pos;	// 座標
	VECTOR m_Rot;	// 回転
	VECTOR m_Scale;	// スケール
	VECTOR m_Move;	// 移動量
	VECTOR m_Accel;	// 加速度
	CollisionSphere* m_Collision;	// 当たり判定
	EnemyBase* m_LockEnemy;
};

