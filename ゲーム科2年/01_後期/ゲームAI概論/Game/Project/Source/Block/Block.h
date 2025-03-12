#pragma once

#include "DxLib.h"

class CollisionAABB;

class Block
{
public:
	Block();
	~Block();

public:
	void Load();			// ロード
	void Start();			// 開始
	void Draw();			// 描画
	void Fin();				// 終了

public:
	Block* Clone();			// クローン

	bool IsActive() { return m_Active; }
	CollisionAABB* GetAABB() { return m_AABB; }

	void SetActive(bool active) { m_Active = active; }
	void SetPos(VECTOR pos) { m_Pos = pos; }

private:
	bool m_Active;
	int m_Handle;	// 画像ハンドル
	VECTOR m_Pos;	// 座標
	CollisionAABB* m_AABB;	// 当たり判定
};