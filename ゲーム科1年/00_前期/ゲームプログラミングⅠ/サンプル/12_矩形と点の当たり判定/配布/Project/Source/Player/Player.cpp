#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"

PlayerData g_PlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.handle = LoadGraph("Resource/Player/Player.png");

	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	g_PlayerData.moveY = PLAYER_MOVE_SPEED;
}

void UpdatePlayer()
{
	// 上入力
	if (IsInputKey(KEY_UP))
	{
		g_PlayerData.posY -= g_PlayerData.moveY;
	}
	// 下入力
	if (IsInputKey(KEY_DOWN))
	{
		g_PlayerData.posY += g_PlayerData.moveY;
	}
	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.posX -= g_PlayerData.moveX;
	}
	// 右入力
	if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.posX += g_PlayerData.moveX;
	}

	// ヒットフラグは毎回折る（当たり判定後に当たっていたら立てる）
	g_PlayerData.hitFlg = false;
}

void DrawPlayer()
{
	DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);

	// 当たっていたら文字を描画する
	if (g_PlayerData.hitFlg)
	{
		DrawString(0, 0, "Player:マウスが当たった", GetColor(255, 255, 255));
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
