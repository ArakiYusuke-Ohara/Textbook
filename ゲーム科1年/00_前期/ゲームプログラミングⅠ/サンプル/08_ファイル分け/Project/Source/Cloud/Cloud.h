#pragma once

// 雲の設定
#define CLOUD_NUM (3)		// 雲の数
#define CLOUD_WIDTH (370)	// 雲の幅

// 関数のプロトタイプ宣言
void InitCloud();	// 初期化
void UpdateCloud();	// 更新
void DrawCloud();	// 描画
void FinCloud();	// 終了

// 雲に関する変数をまとめた構造体
struct CloudData
{
	int handle;		// 画像ハンドル
	float posX;		// X座標
	float posY;		// Y座標
	float moveX;	// X移動量
	float moveY;	// Y移動量
};



