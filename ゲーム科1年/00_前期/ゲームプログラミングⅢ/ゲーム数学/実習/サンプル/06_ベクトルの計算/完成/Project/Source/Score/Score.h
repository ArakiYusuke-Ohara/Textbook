#pragma once
#include "DxLib.h"

// スコア初期化
void InitScore();
void UpdateScore();

// スコア表示UI生成
void CreateScoreUI(VECTOR pos);
void CreateHiScoreUI(VECTOR pos);

// スコア設定
void SetScore(int score);

// スコア取得
int GetScore();

// ハイスコア設定
void SetHiScore(int hiScore);

// ハイスコア取得
int GetHiScore();
