#pragma once

// 関数のプロトタイプ宣言
void InitBlueEnemy();
void UpdateBlueEnemy();
void DrawBlueEnemy();
void FinBlueEnemy();

struct BlueEnemyData
{
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
};
