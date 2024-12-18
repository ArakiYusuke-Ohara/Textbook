#include "ReflactBlock.h"
#include "../Math/MyMath.h"
#include "../Camera/Camera.h"

ReflactBlockData g_ReflactBlockData = { 0 };

void InitReflactBlock()
{
	g_ReflactBlockData.active = false;
	g_ReflactBlockData.handle = 0;
	g_ReflactBlockData.pos = VGet(0.0f, 0.0f, 0.0f);
	g_ReflactBlockData.normal = VGet(0.0f, 0.0f, 0.0f);
}

void LoadReflactBlock()
{
	g_ReflactBlockData.handle = LoadGraph("Data/Map/ReflactBlock.png");
}

void StartReflactBlock()
{
	g_ReflactBlockData.pos = VGet(50.0f, 750.0f, 0.0f);

	// 法線は右向きで固定
	// 回転を考慮する場合はまた別の計算が必要
	g_ReflactBlockData.normal = VGet(1.0f, 0.0f, 0.0f);

}

void StepReflactBlock()
{
}

void UpdateReflactBlock()
{
}

void DrawReflactBlock()
{
	CameraData camera = GetCameraData();
	VECTOR pos = VecCreate(camera.pos, g_ReflactBlockData.pos);
	DrawGraph((int)pos.x, (int)pos.y, g_ReflactBlockData.handle, TRUE);
}

void FinReflactBlock()
{
	DeleteGraph(g_ReflactBlockData.handle);
}

ReflactBlockData GetReflactBlock()
{
	return g_ReflactBlockData;
}
