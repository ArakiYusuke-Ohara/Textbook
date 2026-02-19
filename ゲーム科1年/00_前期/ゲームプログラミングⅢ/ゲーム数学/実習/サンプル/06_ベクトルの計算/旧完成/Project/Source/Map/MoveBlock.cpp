#include "MoveBlock.h"
#include "../Camera/Camera.h"
#include <math.h>

#define MOVE_BLOCK_ARCH_RANGE (300.0f)	// 放物線の横幅
#define MOVE_BLOCK_SIN_SPEED (0.03f)	// Sin波移動の速度
#define MOVE_BLOCK_CIRCLE_RADIUS (100.0f)	// 円移動の半径
#define MOVE_BLOCK_CIRCLE_SPEED (0.03f)		// 円移動の速度

MoveBlockData g_MoveBlockData = { 0 };

void UpdateArchBlock();	// 放物線移動更新
void UpdateSinBlock();	// Sin波移動更新
void UpdateCircleBlock();	// 円移動更新


void InitMoveBlock()
{
	g_MoveBlockData.active = false;
	g_MoveBlockData.handle = 0;
	g_MoveBlockData.dir = 0;
	g_MoveBlockData.pos.x = 0.0f;
	g_MoveBlockData.pos.y = 0.0f;
	g_MoveBlockData.startPos.x = 0.0f;
	g_MoveBlockData.startPos.y = 0.0f;
	g_MoveBlockData.archTopPos.x = 0.0f;
	g_MoveBlockData.archTopPos.y = 0.0f;
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
	g_MoveBlockData.mode = MOVE_BLOCK_MODE_CIRCLE;
	// 初期位置
	g_MoveBlockData.startPos.x = 500.0f;
	g_MoveBlockData.startPos.y = 500.0f;
	g_MoveBlockData.pos.x = g_MoveBlockData.startPos.x;
	g_MoveBlockData.pos.y = g_MoveBlockData.startPos.y;
	// Sin波で移動する範囲
	g_MoveBlockData.sinRange = 100.0f;
}

void StepMoveBlock()
{
}

void UpdateMoveBlock()
{
	// 移動前の座標を記録
	g_MoveBlockData.oldPos.x = g_MoveBlockData.pos.x;
	g_MoveBlockData.oldPos.y = g_MoveBlockData.pos.y;

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

		// 円移動
	case MOVE_BLOCK_MODE_CIRCLE:
		UpdateCircleBlock();
		break;
	}
}

void DrawMoveBlock()
{
	CameraData camera = GetCamera();

	DrawGraph((int)(g_MoveBlockData.pos.x - camera.pos.x), (int)(g_MoveBlockData.pos.y - camera.pos.y), g_MoveBlockData.handle, TRUE);
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
	g_MoveBlockData.pos.x += ARCH_BLOCK_SPEED * g_MoveBlockData.dir;

	// わかりやすい名前の変数に格納
	float x = g_MoveBlockData.startPos.x;
	float y = g_MoveBlockData.startPos.y;
	float h = g_MoveBlockData.archTopPos.x;
	float k = g_MoveBlockData.archTopPos.y;

	// ① 放物線の方程式に初期位置と頂点座標を代入してaを求める
	float a = (y - k) / ((x - h) * (x - h));

	// ② 現在のX座標と頂点座標とaを代入してY座標を求める
	g_MoveBlockData.pos.y = a * ((g_MoveBlockData.pos.x - h) * (g_MoveBlockData.pos.x - h)) + k;

	// 一定範囲左右で往復させる
	float rightEnd = g_MoveBlockData.startPos.x + MOVE_BLOCK_ARCH_RANGE;
	// 右端に到達したら反対方向へ
	if (g_MoveBlockData.pos.x > rightEnd)
	{
		g_MoveBlockData.pos.x = rightEnd;
		g_MoveBlockData.dir = -g_MoveBlockData.dir;
	}
	// 左端に到達したら反対方向へ
	else if (g_MoveBlockData.pos.x < g_MoveBlockData.startPos.x)
	{
		g_MoveBlockData.pos.x = g_MoveBlockData.startPos.x;
		g_MoveBlockData.dir = -g_MoveBlockData.dir;
	}
}

void UpdateSinBlock()
{
	// ① ブロックのY座標は開始位置からSin波だけ移動した場所
	float sin = sinf(g_MoveBlockData.sinAngle) * g_MoveBlockData.sinRange;
	g_MoveBlockData.pos.y = g_MoveBlockData.startPos.y + sin;

	// ② Sin波に渡す角度を加算する
	g_MoveBlockData.sinAngle += MOVE_BLOCK_SIN_SPEED;

	// ③ 角度は0～2πの範囲に収める
	if (g_MoveBlockData.sinAngle > DX_TWO_PI_F)
	{
		g_MoveBlockData.sinAngle -= DX_TWO_PI_F;
	}
}

void UpdateCircleBlock()
{
	// ① 円移動時のX移動値は 半径 * cosθ
	g_MoveBlockData.pos.x = g_MoveBlockData.startPos.x + MOVE_BLOCK_CIRCLE_RADIUS * cosf(g_MoveBlockData.circleAngle);

	// ② 円移動時のY移動値は 半径 * sinθ
	g_MoveBlockData.pos.y = g_MoveBlockData.startPos.y + MOVE_BLOCK_CIRCLE_RADIUS * sinf(g_MoveBlockData.circleAngle);

	// ③ 三角関数に渡す角度を加算
	g_MoveBlockData.circleAngle += MOVE_BLOCK_CIRCLE_SPEED;

	// ③ 角度は0～2πの範囲に収める
	if (g_MoveBlockData.circleAngle > DX_TWO_PI_F)
	{
		g_MoveBlockData.circleAngle -= DX_TWO_PI_F;
	}
}
