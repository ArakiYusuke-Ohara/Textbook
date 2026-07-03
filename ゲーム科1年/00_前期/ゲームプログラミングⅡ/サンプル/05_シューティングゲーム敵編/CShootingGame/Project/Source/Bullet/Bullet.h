#pragma once
#include "BulletParameter.h"

// 各ロジックごとの関数
void InitBullet();
void LoadBullet();
void StepBullet();
void UpdateBullet();
void DrawBullet();
void FinBullet();

// 発射関数（必ずBulletManagerでしか呼ばないこと）
void FireBullet(float posX, float posY, float moveX, float moveY);

// 弾取得
BulletData* GetBullet();

// 当たり判定関連
void BulletHitEnemy(int index);
void BulletHitPlayer(int index);
