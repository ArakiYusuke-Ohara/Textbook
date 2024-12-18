#include "DxLib.h"
#include "Cloud.h"
#include "../GameSetting/GameSetting.h"

// ‰_ƒf[ƒ^
CloudData g_CloudData[CLOUD_NUM];

void InitCloud()
{
	// ‘S‚Ä‚Ì‰_‚Ì‰Šú‰»
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		// ‰_‚Ì‰æ‘œ‚ğƒ[ƒh‚·‚é
		g_CloudData[i].handle = LoadGraph("Resource/BG/Cloud.png");

		// ‰_‚Ì‰ŠúˆÊ’u‚ğİ’è‚·‚é
		g_CloudData[i].posX = 1920.0f + i * 400.0f;
		g_CloudData[i].posY = 50.0f + i * 50.0f;

		// ‰_‚ÌˆÚ“®—Ê‚ğİ’è‚·‚é
		g_CloudData[i].moveX = -2.0f;
		g_CloudData[i].moveY = 0.0f;
	}
}

void UpdateCloud()
{
	// ‘S‚Ä‚Ì‰_‚ğˆÚ“®‚³‚¹‚é
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		// ‰_‚ğˆÚ“®‚³‚¹‚é
		g_CloudData[i].posX += g_CloudData[i].moveX;
		g_CloudData[i].posY += g_CloudData[i].moveY;

		// ‰_‚ª’Ê‚è‰ß‚¬‚½‚©‚ğƒ`ƒFƒbƒN
		if (g_CloudData[i].posX <= -CLOUD_WIDTH)
		{
			// ‰_‚ğ‰æ–Ê‚Ì‰E’[‚ÉˆÚ“®‚³‚¹‚é
			g_CloudData[i].posX = SCREEN_WIDTH;
		}
	}
}

void DrawCloud()
{
	// ‘S‚Ä‚Ì‰_‚ğ•`‰æ‚·‚é
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		// ‰_‚ğ•`‰æ‚·‚é
		DrawGraph((int)g_CloudData[i].posX, (int)g_CloudData[i].posY, (int)g_CloudData[i].handle, TRUE);
	}
}

void FinCloud()
{
	// ‘S‚Ä‚Ì‰_‚Ì‰æ‘œ‚ğíœ
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		// ‰_‚Ì‰æ‘œ‚ğíœ
		DeleteGraph(g_CloudData[i].handle);
	}
}
