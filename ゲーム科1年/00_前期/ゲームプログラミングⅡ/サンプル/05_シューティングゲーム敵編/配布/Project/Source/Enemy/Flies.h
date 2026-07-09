#pragma once
#define ENEMY_FLIES_MAX			(20)	// 最大出現数
#define ENEMY_FLIES_RADIUS		(16.0f)	// 半径
#define ENEMY_FLIES_WIDTH		(32.0f)	// 横幅
#define ENEMY_FLIES_HEIGHT		(32.0f)	// 縦幅

struct EnemyFliesData
{
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
	bool active;
};

// 関数のプロトタイプ宣言
void InitFlies();
void LoadFlies();
void StartFlies();
void StepFlies();
void UpdateFlies();
void DrawFlies();
void FinFlies();

// Fliesを出現させる


// Flies取得
EnemyFliesData* GetFlies();

// 当たり判定関連
void FliesHitPlayer(int index);

// 当たり判定関連
void FliesHitPlayerBullet(int index);
