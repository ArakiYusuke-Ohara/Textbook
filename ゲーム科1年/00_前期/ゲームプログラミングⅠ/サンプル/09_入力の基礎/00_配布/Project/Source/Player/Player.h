#pragma once

// プレイヤー設定関連
#define PLAYER_DEFAULT_POS_X (200.0f)
#define PLAYER_DEFAULT_POS_Y (400.0f)
#define PLAYER_MOVE_SPEED (10.0f)

// 関数のプロトタイプ宣言
void InitPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// プレイヤーデータ
struct PlayerData
{
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
};
