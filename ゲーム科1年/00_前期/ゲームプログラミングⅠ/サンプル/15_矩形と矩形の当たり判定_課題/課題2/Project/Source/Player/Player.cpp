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
		DrawString(0, 0, "Player:青エネミーに当たった", GetColor(255, 255, 255));
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

void PlayerHitBlueEnemy(float enemyPosX, float enemyPosY, float enemyWidth, float enemyHeight)
{
	// 押し戻した後の座標を一時的に格納する変数
	float resultX = g_PlayerData.posX;
	float resultY = g_PlayerData.posY;

	// Yの移動を戻して、先にXだけ移動した状態で判定する
	float checkPosX = g_PlayerData.posX;
	float checkPosY = g_PlayerData.posY - g_PlayerData.moveY;

	if (CheckSquareSquare(checkPosX, checkPosY, PLAYER_WIDTH, PLAYER_HEIGHT,
		enemyPosX + 0.01f, enemyPosY + 0.01f, enemyWidth - 0.02f, enemyHeight - 0.02f))
	{
		// 右に移動していれば左に押し出す
		if (g_PlayerData.moveX > 0.0f)
		{
			resultX -= (checkPosX + PLAYER_WIDTH) - enemyPosX;	// 左に押し出す
		}
		// 左に移動していれば右に押し出す
		else if (g_PlayerData.moveX < 0.0f)
		{
			resultX += (enemyPosX + enemyWidth) - checkPosX;	// 左に押し出す
		}
	}

	// Xの移動を戻して、Yだけ移動した状態で判定する
	checkPosX = g_PlayerData.posX - g_PlayerData.moveX;
	checkPosY = g_PlayerData.posY;

	if (CheckSquareSquare(checkPosX, checkPosY, PLAYER_WIDTH, PLAYER_HEIGHT,
		enemyPosX + 0.01f, enemyPosY + 0.01f, enemyWidth - 0.02f, enemyHeight - 0.02f))
	{
		// 下に移動していれば上に押し出す
		if (g_PlayerData.moveY > 0.0f)
		{// 下に移動しているということは上からあたった
			resultY -= (g_PlayerData.posY + PLAYER_HEIGHT) - enemyPosY;	// 上に押し出す
		}
		// 上に移動していれば下に押し出す
		else if (g_PlayerData.moveY < 0.0f)
		{// 上に移動しているということは下からあたった
			resultY += (enemyPosY + enemyHeight) - g_PlayerData.posY;	// 下に押し出す
		}
	}

	// 押し出した後の座標を設定
	g_PlayerData.posX = resultX;
	g_PlayerData.posY = resultY;
}
