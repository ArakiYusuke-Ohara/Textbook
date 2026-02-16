#pragma once

// アニメーションタイプ
enum PlayerAnimationType
{
	PLAYER_ANIM_IDLE,
	PLAYER_ANIM_RUN,
	PLAYER_ANIM_JUMP,
	PLAYER_ANIM_FALL,
	PLAYER_ANIM_LANDING,
	PLAYER_ANIM_MAX,
	PLAYER_ANIM_NONE = -1
};

// プレイヤーデータ
struct PlayerData
{
	bool active;								// 生存フラグ
	bool isAir;									// 空中にいるか
	int handle;									// 画像ハンドル	
	float posX;									// X座標
	float posY;									// Y座標
	float moveX;								// X移動量
	float moveY;								// Y移動量
};

// 関数のプロトタイプ宣言
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// 取得関数
PlayerData* GetPlayer();
