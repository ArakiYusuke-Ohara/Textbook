#pragma once

// プレイヤー設定関連
#define PLAYER_DEFAULT_POS_X (200.0f)
#define PLAYER_DEFAULT_POS_Y (400.0f)
#define PLAYER_MOVE_SPEED (10.0f)

// プレイヤーサイズ
#define PLAYER_WIDTH	(64.0f)
#define PLAYER_HEIGHT	(64.0f)
#define PLAYER_RADIUS	(32.0f)

// プレイヤーデータ
struct PlayerData
{
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
	bool hitFlag;
};

// 関数のプロトタイプ宣言
void InitPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// 取得関数
PlayerData* GetPlayer();

// 当たり判定
void PlayerHitWaterEnemy();
