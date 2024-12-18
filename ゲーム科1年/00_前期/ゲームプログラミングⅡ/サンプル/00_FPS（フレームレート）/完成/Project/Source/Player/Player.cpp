#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"

PlayerData g_PlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.handle = LoadGraph("Resource/Player/Player.png");

	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
}

void StepPlayer()
{
	// ヒットフラグは毎回折る（当たり判定後に当たっていたら立てる）
	g_PlayerData.hitFlag = false;

	// 移動量は毎回リセットする
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;

	// 上入力
	if (IsInputKey(KEY_UP))
	{
		g_PlayerData.moveY = -PLAYER_MOVE_SPEED;
	}
	// 下入力
	if (IsInputKey(KEY_DOWN))
	{
		g_PlayerData.moveY = PLAYER_MOVE_SPEED;
	}
	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
	}
	// 右入力
	if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	}
}

void UpdatePlayer()
{
	// 移動処理
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;
}

void DrawPlayer()
{
	DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);

	// 当たっていたら文字を描画する
	if (g_PlayerData.hitFlag)
	{
		DrawString(0, 0, "Player:水色エネミーに当たった", GetColor(255, 255, 255));
	}
}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

void PlayerHitWaterEnemy()
{
	g_PlayerData.hitFlag = true;
}
