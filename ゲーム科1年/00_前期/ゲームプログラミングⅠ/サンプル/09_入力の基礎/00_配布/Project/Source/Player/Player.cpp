#include "DxLib.h"
#include "Player.h"

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
}

void DrawPlayer()
{
	DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);
}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}
