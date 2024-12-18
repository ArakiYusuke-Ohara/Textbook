#include "MoveBlock.h"
#include "../Camera/Camera.h"
#include <math.h>

#define BLOCK_ARCH_MOVE_RANGE (300.0f)	// 放物線の横幅
#define BLOCK_SIN_MOVE_SPEED (0.03f)		// Sin波移動の速度

MoveBlockData g_MoveBlockData = { 0 };

void UpdateArchBlock();	// 放物線移動更新
void UpdateSinBlock();	// Sin波移動更新


void InitMoveBlock()
{
	g_MoveBlockData.active = false;
	g_MoveBlockData.handle = 0;
	g_MoveBlockData.dir = 0;
	g_MoveBlockData.posX = 0.0f;
	g_MoveBlockData.posY = 0.0f;
	g_MoveBlockData.startX = 0.0f;
	g_MoveBlockData.startY = 0.0f;
	g_MoveBlockData.topX = 0.0f;
	g_MoveBlockData.topY = 0.0f;
	g_MoveBlockData.sinAngle = 0.0f;
	g_MoveBlockData.sinRange = 0.0f;
	g_MoveBlockData.mode = MOVE_BLOCK_MODE_NONE;
}

void LoadMoveBlock()
{
	g_MoveBlockData.handle = LoadGraph("Data/Map/ArchBlock.png");
}

void StartMoveBlock()
{
	// モード設定
	g_MoveBlockData.mode = MOVE_BLOCK_MODE_SIN;
	// 初期位置
	g_MoveBlockData.startX = 500.0f;
	g_MoveBlockData.startY = 500.0f;
	g_MoveBlockData.posX = g_MoveBlockData.startX;
	g_MoveBlockData.posY = g_MoveBlockData.startY;
	// Sin波で移動する範囲
	g_MoveBlockData.sinRange = 100.0f;
}

void StepMoveBlock()
{
}

void UpdateMoveBlock()
{
	switch (g_MoveBlockData.mode)
	{
	// 放物線移動
	case MOVE_BLOCK_MODE_ARCH:
		UpdateArchBlock();
		break;

	// Sin波移動
	case MOVE_BLOCK_MODE_SIN:
		UpdateSinBlock();
		break;
	}
}

void DrawMoveBlock()
{
	CameraData camera = GetCamera();

	DrawGraph((int)(g_MoveBlockData.posX - camera.posX), (int)(g_MoveBlockData.posY - camera.posY), g_MoveBlockData.handle, TRUE);
}

void FinMoveBlock()
{
	DeleteGraph(g_MoveBlockData.handle);
}

MoveBlockData GetMoveBlockData()
{
	return g_MoveBlockData;
}

void UpdateArchBlock()
{
	// 右へ移動
	g_MoveBlockData.posX += ARCH_BLOCK_SPEED * g_MoveBlockData.dir;

	// わかりやすい名前の変数に格納
	float x = g_MoveBlockData.startX;
	float y = g_MoveBlockData.startY;
	float h = g_MoveBlockData.topX;
	float k = g_MoveBlockData.topY;

	// ① 放物線の方程式に初期位置と頂点座標を代入してaを求める
	float a = (y - k) / ((x - h) * (x - h));

	// ② 現在のX座標と頂点座標とaを代入してY座標を求める
	g_MoveBlockData.posY = a * ((g_MoveBlockData.posX - h) * (g_MoveBlockData.posX - h)) + k;

	// 一定範囲左右で往復させる
	float rightEnd = g_MoveBlockData.startX + BLOCK_ARCH_MOVE_RANGE;
	// 右端に到達したら反対方向へ
	if (g_MoveBlockData.posX > rightEnd)
	{
		g_MoveBlockData.posX = rightEnd;
		g_MoveBlockData.dir = -g_MoveBlockData.dir;
	}
	// 左端に到達したら反対方向へ
	else if (g_MoveBlockData.posX < g_MoveBlockData.startX)
	{
		g_MoveBlockData.posX = g_MoveBlockData.startX;
		g_MoveBlockData.dir = -g_MoveBlockData.dir;
	}
}

void UpdateSinBlock()
{
	// ① ブロックのY座標は開始位置からSin波だけ移動した場所
	float sin = sinf(g_MoveBlockData.sinAngle) * g_MoveBlockData.sinRange;
	g_MoveBlockData.posY = g_MoveBlockData.startY + sin;

	// ② Sin波に渡す角度を加算する
	g_MoveBlockData.sinAngle += BLOCK_SIN_MOVE_SPEED;

	// ③ 角度は0～2πの範囲に収める
	if (g_MoveBlockData.sinAngle > DX_TWO_PI_F)
	{
		g_MoveBlockData.sinAngle -= DX_TWO_PI_F;
	}
}
