#include "DxLib.h"
#include "BlueEnemy.h"

// 変数
BlueEnemyData g_BlueEnemyData = { 0 };

void InitBlueEnemy()
{
	g_BlueEnemyData.hitFlg = false;
	g_BlueEnemyData.handle = LoadGraph("Data/Enemy/BlueEnemy.png");
	g_BlueEnemyData.posX = 400.0f;
	g_BlueEnemyData.posY = 600.0f;
	g_BlueEnemyData.moveX = 0.0f;
	g_BlueEnemyData.moveY = 0.0f;
}

void UpdateBlueEnemy()
{
	// ヒットフラグは毎回折る（当たり判定後に当たっていたら立てる）
	g_BlueEnemyData.hitFlg = false;
}

void DrawBlueEnemy()
{
	DrawGraph((int)g_BlueEnemyData.posX, (int)g_BlueEnemyData.posY, g_BlueEnemyData.handle, TRUE);

	// 当たっていたら文字を描画する
	if (g_BlueEnemyData.hitFlg)
	{
		DrawString(0, 20, "BlueEnemy:マウスが当たった", GetColor(255, 255, 255));
	}
}

void FinBlueEnemy()
{
}

BlueEnemyData* GetBuleEnemyData()
{
	return &g_BlueEnemyData;
}
