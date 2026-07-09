#pragma once
#define ENEMY_DRAGON_FLY_MAX		(10)	// 最大出現数
#define ENEMY_DRAGON_FLY_RADIUS		(16.0f)	// 半径
#define ENEMY_DRAGON_FLY_WIDTH		(32.0f)	// 横幅
#define ENEMY_DRAGON_FLY_HEIGHT		(32.0f)	// 縦幅

struct EnemyDragonFlyData
{
	int handle;
	int timer;
	float posX;
	float posY;
	float moveX;
	float moveY;
	bool active;
	bool isMoveChange;
};

// 関数のプロトタイプ宣言
void InitDragonFly();
void LoadDragonFly();
void StartDragonFly();
void StepDragonFly();
void UpdateDragonFly();
void DrawDragonFly();
void FinDragonFly();

// DragonFlyを出現させる


// DragonFly取得
EnemyDragonFlyData* GetDragonFly();

// 当たり判定関連
void DragonFlyHitPlayer(int index);

// 当たり判定関連
void DragonFlyHitPlayerBullet(int index);
