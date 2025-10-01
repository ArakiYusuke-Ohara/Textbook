#pragma once
#include "../Map/MapParameter.h"
#include "../Animation/Animation.h"
#include "../Collision/Collision.h"

// プレイヤーサイズ
#define PLAYER_WIDTH	(72.0f)
#define PLAYER_HEIGHT	(72.0f)
#define PLAYER_RADIUS	(36.0f)

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

// プレイヤーの状態
enum PlayerState
{
	PLAYER_RUN = (1 << 0),
	PLAYER_AIR = (1 << 1),
	PLAYER_FALL = (1 << 2),
};

// プレイヤーデータ
struct PlayerData
{
	bool active;								// 生存フラグ
	bool isTurn;								// 左を向いているか
	int  state;									// プレイヤーの状態
	float posX;									// X座標
	float posY;									// Y座標
	float moveX;								// X移動量
	float moveY;								// Y移動量
	AnimationData animation[PLAYER_ANIM_MAX];	// アニメーション
	PlayerAnimationType playAnim;				// 再生中のアニメーション
	BoxCollision boxCollision;					// 矩形当たり判定
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
PlayerData GetPlayer();

// 移動関数
void PlayerMoveX();
void PlayerMoveY();

// 当たり判定
// 通常ブロックとの当たり判定
void PlayerHitNormalBlockX(MapChipData mapChipData, bool checkRight = true, bool checkLeft = true);
void PlayerHitNormalBlockY(MapChipData mapChipData);												
// 坂道ブロックとの当たり判定
void PlayerHitSlopeBlockX(MapChipData mapChipData);
void PlayerHitSlopeBlockY(MapChipData mapChipData);
// 自動ドアとの当たり判定
void PlayerHitAutoDoorX(AutoDoorData autoDoor);
void PlayerHitAutoDoorY(AutoDoorData autoDoor);
// 放物線ブロックとの当たり判定
void PlayerHitArchBlockX(ArchBlockData archBlock);
void PlayerHitArchBlockY(ArchBlockData archBlock);
