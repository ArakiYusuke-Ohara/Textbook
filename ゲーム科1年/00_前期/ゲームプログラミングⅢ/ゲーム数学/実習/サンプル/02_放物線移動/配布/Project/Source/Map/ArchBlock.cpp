#include "ArchBlock.h"
#include "../Camera/Camera.h"

#define ARCH_BLOCK_RANGE (300.0f)	// 放物線の横幅

ArchBlockData g_ArchBlockData = { 0 };

void InitArchBlock()
{
	g_ArchBlockData.active = false;
	g_ArchBlockData.handle = 0;
	g_ArchBlockData.dir = 0;
	g_ArchBlockData.posX = 0.0f;
	g_ArchBlockData.posY = 0.0f;
	g_ArchBlockData.startX = 0.0f;
	g_ArchBlockData.startY = 0.0f;
	g_ArchBlockData.topX = 0.0f;
	g_ArchBlockData.topY = 0.0f;
}

void LoadArchBlock()
{
	g_ArchBlockData.handle = LoadGraph("Data/Map/ArchBlock.png");
}

void StartArchBlock()
{
	// 初期位置
	g_ArchBlockData.startX = 500.0f;
	g_ArchBlockData.startY = 700.0f;
	g_ArchBlockData.posX = g_ArchBlockData.startX;
	g_ArchBlockData.posY = g_ArchBlockData.startY;

	// 頂点座標
	g_ArchBlockData.topX = g_ArchBlockData.startX + ARCH_BLOCK_RANGE * 0.5f;
	g_ArchBlockData.topY = 400.0f;
	// 最初は右向き
	g_ArchBlockData.dir = 1;
}

void StepArchBlock()
{
}

void UpdateArchBlock()
{
	// 右へ移動
	g_ArchBlockData.posX += ARCH_BLOCK_SPEED * g_ArchBlockData.dir;

	// わかりやすい名前の変数に格納
	float x = g_ArchBlockData.startX;
	float y = g_ArchBlockData.startY;
	float h = g_ArchBlockData.topX;
	float k = g_ArchBlockData.topY;

	// ① 放物線の方程式に初期位置と頂点座標を代入してaを求める


	// ② 現在のX座標と頂点座標とaを代入してY座標を求める


	// 一定範囲左右で往復させる
	float rightEnd = g_ArchBlockData.startX + ARCH_BLOCK_RANGE;
	// 右端に到達したら反対方向へ
	if (g_ArchBlockData.posX > rightEnd)
	{
		g_ArchBlockData.posX = rightEnd;
		g_ArchBlockData.dir = -g_ArchBlockData.dir;
	}
	// 左端に到達したら反対方向へ
	else if (g_ArchBlockData.posX < g_ArchBlockData.startX)
	{
		g_ArchBlockData.posX = g_ArchBlockData.startX;
		g_ArchBlockData.dir = -g_ArchBlockData.dir;
	}
}

void DrawArchBlock()
{
	CameraData camera = GetCamera();

	DrawGraph((int)(g_ArchBlockData.posX - camera.posX), (int)(g_ArchBlockData.posY - camera.posY), g_ArchBlockData.handle, TRUE);
}

void FinArchBlock()
{
	DeleteGraph(g_ArchBlockData.handle);
}

ArchBlockData GetArchBlockData()
{
	return g_ArchBlockData;
}
