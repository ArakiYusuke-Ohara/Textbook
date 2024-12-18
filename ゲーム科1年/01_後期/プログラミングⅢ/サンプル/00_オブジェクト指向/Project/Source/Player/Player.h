#pragma once

class Player
{
	// 機能はメンバ関数としてまとめる
	void Run();		// 走る
	void Jump();	// ジャンプする
	void Draw();	// 描画する
	void Dead();	// 死亡する

	// 機能に必要なデータはメンバ変数としてまとめる
	float m_PosX;
	float m_PosY;
	float m_MoveX;
	float m_MoveY;
	int m_Handle;
	int m_HP;
};

