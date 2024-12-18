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
	g_AutoDoorData.posX = 0.0f;
	g_AutoDoorData.posY = 0.0f;
	g_AutoDoorData.startPosX = 0.0f;
	g_AutoDoorData.startPosY = 0.0f;
}

void LoadAutoDoor()
{
	g_AutoDoorData.handle = LoadGraph("Data/Map/AutoDoor.png");
}

void StartAutoDoor()
{
	// 初期位置設定
	g_AutoDoorData.posX = 950.0f;
	g_AutoDoorData.posY = 750.0f;
	g_AutoDoorData.startPosX = g_AutoDoorData.posX;
	g_AutoDoorData.startPosY = g_AutoDoorData.posY;
}

void StepAutoDoor()
{
	PlayerData player = GetPlayer();

	// ① 自動ドアとプレイヤーがX軸でどれだけ離れているか計算する


	// ② 自動ドアとプレイヤーがY軸でどれだけ離れているか計算する


	// ③ 公式より２点間の距離を計算する


	// ④ ２点間の距離がAUTO_DOOR_OPEN_DISTANCE以下であればisOpenフラグをtrueにする


}

void UpdateAutoDoor()
{
	// isOpenがtrueなら上昇
	if (g_AutoDoorData.isOpen)
	{
		g_AutoDoorData.posY -= AUTO_DOOR_SPEED;
		if (g_AutoDoorData.posY < (g_AutoDoorData.startPosY - AUTO_DOOR_HEIGHT))
		{
			g_AutoDoorData.posY = g_AutoDoorData.startPosY - AUTO_DOOR_HEIGHT;
		}
	}
	// isOpenがfalseなら下降
	else
	{
		g_AutoDoorData.posY += AUTO_DOOR_SPEED;
		if (g_AutoDoorData.posY > (g_AutoDoorData.startPosY))
		{
			g_AutoDoorData.posY = g_AutoDoorData.startPosY;
		}
	}
}

void DrawAutoDoor()
{
	CameraData camera = GetCamera();
	DrawGraph((int)(g_AutoDoorData.posX - camera.posX), (int)(g_AutoDoorData.posY - camera.posY), g_AutoDoorData.handle, TRUE);
}

void FinAutoDoor()
{
	DeleteGraph(g_AutoDoorData.handle);
}

AutoDoorData GetAutoDoorData()
{
	return g_AutoDoorData;
}
