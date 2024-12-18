#pragma once

#include "DxLib.h"

class Block
{
public:
	Block();
	~Block();

public:
	void Init();			// 初期化
	void Load();			// ロード
	void Start();			// 開始
	void Step();			// ステップ
	void Update();			// 更新
	void Draw();			// 描画
	void Fin();				// 終了

public:
	void SetPos(VECTOR pos) { m_Pos = pos; }

private:
	int m_Handle;	// 画像ハンドル
	VECTOR m_Pos;	// 座標

};