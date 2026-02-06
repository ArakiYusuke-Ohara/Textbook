#pragma once

#include "DxLib.h"

class CollisionAABB;

class Block
{
public:
	Block();
	~Block();

	void Init();			// 初期化
	void Load(int handle);	// ロード
	void Start();			// 開始
	void Step();			// ステップ
	void Update();			// 更新
	void Draw();			// 描画
	void Fin();				// 終了

	CollisionAABB* GetAABB() { return m_AABB; }

	void SetPos(VECTOR pos) { m_Pos = pos; }

private:
	int m_Handle;	// 画像ハンドル
	VECTOR m_Pos;	// 座標
	CollisionAABB* m_AABB;	// 当たり判定
};