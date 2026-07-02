#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Enemy/BlueEnemy.h"

PlayerData g_PlayerData = { 0 };

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
	// 前回の座標を保存する
	g_PlayerData.prevPosX = g_PlayerData.posX;
	g_PlayerData.prevPosY = g_PlayerData.posY;

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
	// 当たりながらスライドする方法をやるにはここは削除
	//g_PlayerData.posX += g_PlayerData.moveX;
	//g_PlayerData.posY += g_PlayerData.moveY;
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

/// <summary>
/// プレイヤーが青い敵に当たった
/// </summary>
void PlayerHitBlueEnemy()
{
	// 移動前の座標に戻せばめりこまない（簡単）
	{
		g_PlayerData.posX = g_PlayerData.prevPosX;
		g_PlayerData.posY = g_PlayerData.prevPosY;
	}

}

/// <summary>
/// 移動と当たり判定を軸ごとにする
/// </summary>
void PlayerMoveAndCollision()
{	
	// 青い敵のデータ取得
	BlueEnemyData* blueEnemy = GetBlueEnemy();

	// X軸だけ移動する
	g_PlayerData.posX += g_PlayerData.moveX;
	// 当たり判定
	if (CheckSquareSquare(g_PlayerData.posX, g_PlayerData.posY, PLAYER_WIDTH, PLAYER_HEIGHT,
		blueEnemy->posX + 0.01f, blueEnemy->posY, BLUE_ENEMY_WIDTH, BLUE_ENEMY_HEIGHT))
	{
		// 右に移動していれば左に押し出す
		if (g_PlayerData.moveX > 0.0f)
		{
			g_PlayerData.posX -= (g_PlayerData.posX + PLAYER_WIDTH) - blueEnemy->posX;	// 左に押し出す
		}
		// 左に移動していれば右に押し出す
		else if (g_PlayerData.moveX < 0.0f)
		{
			g_PlayerData.posX += (blueEnemy->posX + BLUE_ENEMY_WIDTH) - g_PlayerData.posX;	// 左に押し出す
		}

		g_PlayerData.moveX = 0.0f;
	}

	// Y軸だけ移動する
	g_PlayerData.posY += g_PlayerData.moveY;
	// 当たり判定
	if (CheckSquareSquare(g_PlayerData.posX, g_PlayerData.posY, PLAYER_WIDTH, PLAYER_HEIGHT,
		blueEnemy->posX, blueEnemy->posY, BLUE_ENEMY_WIDTH, BLUE_ENEMY_HEIGHT))
	{
		// 下に移動していれば上に押し出す
		if (g_PlayerData.moveY > 0.0f)
		{// 下に移動しているということは上からあたった
			g_PlayerData.posY -= (g_PlayerData.posY + PLAYER_HEIGHT) - blueEnemy->posY;	// 上に押し出す
		}
		// 上に移動していれば下に押し出す
		else if (g_PlayerData.moveY < 0.0f)
		{// 上に移動しているということは下からあたった
			g_PlayerData.posY += (blueEnemy->posY + BLUE_ENEMY_HEIGHT) - g_PlayerData.posY;	// 下に押し出す
		}

		g_PlayerData.moveY = 0.0f;
	}
}
