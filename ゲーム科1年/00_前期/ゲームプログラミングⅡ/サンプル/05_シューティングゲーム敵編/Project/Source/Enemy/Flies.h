#pragma once
#include "EnemyParameter.h"

// 関数のプロトタイプ宣言
void InitFlies();
void LoadFlies();
void StepFlies();
void UpdateFlies();
void DrawFlies();
void FinFlies();

// Fliesを生成
EnemyBaseData* SpawnFlies(float posX, float posY);

// Flies取得
EnemyFliesData* GetFlies();

// 当たり判定関連
void FliesHitPlayer(int index);

// 当たり判定関連
void FliesHitPlayerBullet(int index);
