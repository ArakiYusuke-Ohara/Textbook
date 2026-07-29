#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Sound/SoundManager.h"
#include "../Map/MapChip.h"
#include "../Map/MapManager.h"

// プレイヤー設定関連
#define PLAYER_WIDTH (50.0f)
#define PLAYER_HEIGHT (50.0f)
#define PLAYER_RADIUS	(36.0f)
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)
#define PLAYER_MOVE_SPEED (4.0f)

// ジャンプ力
#define PLAYER_JUMP_POWER (-12.0f)
// 重力
#define PLAYER_GRAVITY (0.4f)

// 矩形判定のサイズ
#define PLAYER_BOX_COLLISION_WIDTH (50)
#define PLAYER_BOX_COLLISION_HEIGHT (50)

// キャラクターの周囲何マスまでチェックするか
#define PLAYER_CHECK_ROUND_NUM (2)

PlayerData g_PlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.active = false;
	g_PlayerData.handle = 0;
	g_PlayerData.body.isAir = false;
	g_PlayerData.body.pos = VGet(0.0f, 0.0f, 0.0f);
	g_PlayerData.body.move = VGet(0.0f, 0.0f, 0.0f);
	g_PlayerData.body.width = 0.0f;
	g_PlayerData.body.height = 0.0f;
}

void LoadPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Player/Player.png");
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;

	// 初期位置設定
	g_PlayerData.body.pos.x = PLAYER_DEFAULT_POS_X;
	g_PlayerData.body.pos.y = PLAYER_DEFAULT_POS_Y;

	// サイズ設定
	g_PlayerData.body.width = PLAYER_WIDTH;
	g_PlayerData.body.height = PLAYER_HEIGHT;

}

void StepPlayer()
{
	// 死んでいたら何もしない
	if (!g_PlayerData.active)
	{
		return;
	}

	// X移動量は毎回リセットする
	g_PlayerData.body.move.x = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.body.move.y += PLAYER_GRAVITY;

	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.body.move.x = -PLAYER_MOVE_SPEED;
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.body.move.x = PLAYER_MOVE_SPEED;
	}

	// Z入力
	if (IsTriggerKey(KEY_Z))
	{
		g_PlayerData.body.move.y = PLAYER_JUMP_POWER;
	}
}

void UpdatePlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 当たり判定付きで移動
	MoveWithMapCollision(&g_PlayerData.body);

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_PlayerData.body.move.y < 0.0f || g_PlayerData.body.move.y > PLAYER_GRAVITY)
	{
		g_PlayerData.body.isAir = true;
	}
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 小数誤差が起きるので描画位置は四捨五入する
	int x = (int)(g_PlayerData.body.pos.x + 0.5f);
	int y = (int)(g_PlayerData.body.pos.y + 0.5f);
	DrawGraph(x, y, g_PlayerData.handle, TRUE);
}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}
