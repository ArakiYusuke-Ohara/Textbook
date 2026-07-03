#pragma once
#include "EnemyParameter.h"

// “G‘S‘Ì‚Ìˆ—
void InitEnemy();
void LoadEnemy();
void StepEnemy();
void UpdateEnemy();
void DrawEnemy();
void FinEnemy();

EnemyBaseData** GetEnemy();
int GetEnemyCount();
void SpawnEnemy(EnemyType type, float posX, float posY);
