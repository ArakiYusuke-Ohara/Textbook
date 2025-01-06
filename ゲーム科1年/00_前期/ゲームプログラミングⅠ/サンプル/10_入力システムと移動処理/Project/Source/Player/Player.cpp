#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"

PlayerData g_PlayerData;

void InitPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Player/Player.png");

	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
}

void StepPlayer()
{
	// 移動量をリセット
	// リセットしないと動き続けてしまう
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;

	// 上入力
	if (IsInputKey(KEY_UP))
	{
		// 上移動
		g_PlayerData.moveY = -PLAYER_MOVE_SPEED;
	}
	// 下入力
	if (IsInputKey(KEY_DOWN))
	{
		// 下移動
		g_PlayerData.moveY = PLAYER_MOVE_SPEED;
	}
	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		// 左移動
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
	}
	// 右入力
	if (IsInputKey(KEY_RIGHT))
	{
		// 右移動
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
}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}
