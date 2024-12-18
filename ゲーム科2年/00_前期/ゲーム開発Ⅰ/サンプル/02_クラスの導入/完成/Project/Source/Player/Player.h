#pragma once
#include "DxLib.h"

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

private:
	int m_Handle;	// 画像ハンドル
	VECTOR m_Pos;	// 座標
	VECTOR m_Rot;	// 回転
	VECTOR m_Scale;	// スケール
};

