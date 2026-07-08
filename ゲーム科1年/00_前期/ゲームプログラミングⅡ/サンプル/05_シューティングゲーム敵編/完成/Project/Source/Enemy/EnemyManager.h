#pragma once
// “G‚Ìí—Ş
enum EnemyType
{
	ENEMY_TYPE_FLIES,
	ENEMY_TYPE_DRAGON_FLY,
	ENEMY_TYPE_KAPU,
};

// “G‘S‘Ì‚Ìˆ—
void InitEnemy();
void LoadEnemy();
void StartEnemy();
void StepEnemy();
void UpdateEnemy();
void DrawEnemy();
void FinEnemy();
