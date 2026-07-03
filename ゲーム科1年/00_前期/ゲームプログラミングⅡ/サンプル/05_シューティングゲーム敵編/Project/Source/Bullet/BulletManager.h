#pragma once
#include "BulletParameter.h"

// ’e‘S‘Ì‚Ìˆ—
void InitAllBullet();
void LoadAllBullet();
void StepAllBullet();
void UpdateAllBullet();
void DrawAllBullet();
void FinAllBullet();

// ’e”­Ë
void RequestFireBullet(float posX, float posY, float moveX, float moveY);
