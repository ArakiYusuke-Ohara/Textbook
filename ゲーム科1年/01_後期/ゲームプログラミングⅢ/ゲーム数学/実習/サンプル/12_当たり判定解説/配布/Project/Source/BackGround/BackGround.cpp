#include "DxLib.h"
#include "BackGround.h"
#include "../Math/MyMath.h"

#define BACK_GROUND_WIDTH	(1600)
#define BACK_GROUND_HEIGHT	(900)

// 背景用のデータ
struct BackGroundData
{
	int handle;
	VECTOR pos;
	VECTOR move;
};
BackGroundData g_BackGroundData[BACK_GROUND_LAYER_MAX] = { 0 };

void InitBackGround()
{
	for (int i = 0; i < BACK_GROUND_LAYER_MAX; i++)
	{
		g_BackGroundData[i].handle = 0;
		g_BackGroundData[i].pos = {};
		g_BackGroundData[i].move = {};
	}
}

void LoadBackGround(const char* path, BackGroundLayer layer)
{
	g_BackGroundData[layer].handle = LoadGraph(path);
}

void StepBackGround()
{
}

void UpdateBackGround()
{
	// 移動
	for (int i = 0; i < BACK_GROUND_LAYER_MAX; i++)
	{
		g_BackGroundData[i].pos = VecAdd(g_BackGroundData[i].pos, g_BackGroundData[i].move);

		// スクロールのループ
		if (g_BackGroundData[i].pos.x > BACK_GROUND_WIDTH)
		{
			g_BackGroundData[i].pos.x -= BACK_GROUND_WIDTH;
		}
		if (g_BackGroundData[i].pos.x < -BACK_GROUND_WIDTH)
		{
			g_BackGroundData[i].pos.x += BACK_GROUND_WIDTH;
		}
		if (g_BackGroundData[i].pos.y > BACK_GROUND_HEIGHT)
		{
			g_BackGroundData[i].pos.y -= BACK_GROUND_HEIGHT;
		}
		if (g_BackGroundData[i].pos.y < -BACK_GROUND_HEIGHT)
		{
			g_BackGroundData[i].pos.y += BACK_GROUND_HEIGHT;
		}
	}
}

void DrawBackGround()
{
	for (int i = 0; i < BACK_GROUND_LAYER_MAX; i++)
	{
		DrawGraph((int)g_BackGroundData[i].pos.x, (int)g_BackGroundData[i].pos.y, (int)g_BackGroundData[i].handle, TRUE);

		// 左にスクロールしていたら右側にもう一枚描画
		if (g_BackGroundData[i].move.x < 0.0f)
		{
			DrawGraph((int)g_BackGroundData[i].pos.x + BACK_GROUND_WIDTH, (int)g_BackGroundData[i].pos.y, (int)g_BackGroundData[i].handle, TRUE);
		}
		// 右にスクロールしていたら左側にもう一枚描画
		if (g_BackGroundData[i].move.x > 0.0f)
		{
			DrawGraph((int)g_BackGroundData[i].pos.x - BACK_GROUND_WIDTH, (int)g_BackGroundData[i].pos.y, (int)g_BackGroundData[i].handle, TRUE);
		}
		// 上にスクロールしていたら下側にもう一枚描画
		if (g_BackGroundData[i].move.y > 0.0f)
		{
			DrawGraph((int)g_BackGroundData[i].pos.x, (int)g_BackGroundData[i].pos.y - BACK_GROUND_HEIGHT, (int)g_BackGroundData[i].handle, TRUE);
		}
		// 下にスクロールしていたら上側にもう一枚描画
		if (g_BackGroundData[i].move.y < 0.0f)
		{
			DrawGraph((int)g_BackGroundData[i].pos.x, (int)g_BackGroundData[i].pos.y + BACK_GROUND_HEIGHT, (int)g_BackGroundData[i].handle, TRUE);
		}
	}
}

void FinBackGround()
{
	for (int i = 0; i < BACK_GROUND_LAYER_MAX; i++)
	{
		DeleteGraph(g_BackGroundData[i].handle);
	}
}

void SetBackGroundMove(float moveX, float moveY, BackGroundLayer layer)
{
	g_BackGroundData[layer].move.x = moveX;
	g_BackGroundData[layer].move.y = moveY;
}
