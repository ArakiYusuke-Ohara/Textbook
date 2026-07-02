#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"

PlayerData g_PlayerData;

void InitPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Player/Player.png");

	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	g_PlayerData.moveY = PLAYER_MOVE_SPEED;
}

void UpdatePlayer()
{
	// è„ì¸óÕ
	if (IsInputKey(KEY_UP))
	{
		g_PlayerData.posY -= g_PlayerData.moveY;
	}
	// â∫ì¸óÕ
	if (IsInputKey(KEY_DOWN))
	{
		g_PlayerData.posY += g_PlayerData.moveY;
	}
	// ç∂ì¸óÕ
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.posX -= g_PlayerData.moveX;
	}
	// âEì¸óÕ
	if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.posX += g_PlayerData.moveX;
	}
}

void DrawPlayer()
{
	DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);
}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}
