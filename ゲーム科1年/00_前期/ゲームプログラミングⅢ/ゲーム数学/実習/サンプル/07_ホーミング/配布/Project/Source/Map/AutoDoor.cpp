#include "DxLib.h"
#include "AutoDoor.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include <math.h>

#define AUTO_DOOR_OPEN_DISTANCE (200.0f)
#define AUTO_DOOR_SPEED (8.0f)

AutoDoorData g_AutoDoorData = { 0 };

void InitAutoDoor()
{
	g_AutoDoorData.active = false;
	g_AutoDoorData.isOpen = false;
	g_AutoDoorData.handle = 0;
	g_AutoDoorData.pos.x = 0.0f;
	g_AutoDoorData.pos.y = 0.0f;
	g_AutoDoorData.startPos.x = 0.0f;
	g_AutoDoorData.startPos.y = 0.0f;
}

void LoadAutoDoor()
{
	g_AutoDoorData.handle = LoadGraph("Data/Map/AutoDoor.png");
}

void StartAutoDoor()
{
	// 初期位置設定
	g_AutoDoorData.pos.x = 950.0f;
	g_AutoDoorData.pos.y = 750.0f;
	g_AutoDoorData.startPos.x = g_AutoDoorData.pos.x;
	g_AutoDoorData.startPos.y = g_AutoDoorData.pos.y;
}

void StepAutoDoor()
{
	PlayerData player = GetPlayer();

	// ① 自動ドアとプレイヤーがX軸でどれだけ離れているか計算する
	float distanceX = g_AutoDoorData.pos.x - player.pos.x;

	// ② 自動ドアとプレイヤーがY軸でどれだけ離れているか計算する
	float distanceY = g_AutoDoorData.pos.y - player.pos.y;

	// ③ 公式より２点間の距離を計算する
	float distance = sqrtf(distanceX * distanceX + distanceY * distanceY);

	// ④ ２点間の距離がAUTO_DOOR_OPEN_DISTANCE以下であればisOpenフラグをtrueにする
	if (distance <= AUTO_DOOR_OPEN_DISTANCE)
	{
		g_AutoDoorData.isOpen = true;
	}
}

void UpdateAutoDoor()
{
	// isOpenがtrueなら上昇
	if (g_AutoDoorData.isOpen)
	{
		g_AutoDoorData.pos.y -= AUTO_DOOR_SPEED;
		if (g_AutoDoorData.pos.y < (g_AutoDoorData.startPos.y - AUTO_DOOR_HEIGHT))
		{
			g_AutoDoorData.pos.y = g_AutoDoorData.startPos.y - AUTO_DOOR_HEIGHT;
		}
	}
	// isOpenがfalseなら下降
	else
	{
		g_AutoDoorData.pos.y += AUTO_DOOR_SPEED;
		if (g_AutoDoorData.pos.y > (g_AutoDoorData.startPos.y))
		{
			g_AutoDoorData.pos.y = g_AutoDoorData.startPos.y;
		}
	}
}

void DrawAutoDoor()
{
	CameraData camera = GetCamera();
	DrawGraph((int)(g_AutoDoorData.pos.x - camera.pos.x), (int)(g_AutoDoorData.pos.y - camera.pos.y), g_AutoDoorData.handle, TRUE);
}

void FinAutoDoor()
{
	DeleteGraph(g_AutoDoorData.handle);
}

AutoDoorData GetAutoDoorData()
{
	return g_AutoDoorData;
}
