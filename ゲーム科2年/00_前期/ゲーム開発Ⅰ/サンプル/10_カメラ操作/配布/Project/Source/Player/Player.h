#pragma once
#include "DxLib.h"

// ヘッダーにインクルードを書きたくないので前方定義
class CollisionAABB;
class CollisionSphere;
struct HitResultAABB;


// プレイヤークラス
class Player 
{
public:
	Player();	// コンストラクタ
	~Player();	// デストラクタ

	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

	VECTOR GetPos() { return m_Pos; }
	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphereCollision() { return m_SphereCollision; }

private:
	// 当たり判定
	void CheckCollision();			// メイン処理
	void MoveWithCollision();		// 移動と押し出し
	HitResultAABB CheckHitBlocks();	// ブロックとの当たり判定
	void CheckGoal();				// ゴールとの当たり判定

	int m_Handle;	// 画像ハンドル
	VECTOR m_Pos;	// 座標
	VECTOR m_Rot;	// 回転
	VECTOR m_Scale;	// スケール
	VECTOR m_Move;	// 移動量
	CollisionAABB* m_AABB;	// AABBの当たり判定
	CollisionSphere* m_SphereCollision;
	bool m_IsGoal;
};

