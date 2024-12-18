#include "DxLib.h"

// 画面設定
#define SCREEN_WIDTH (1920)		// 画面の横幅
#define SCREEN_HEIGHT (1080)	// 画面の高さ
#define SCREEN_COLOR_DEPTH (32)	// 画面のカラービット数

// 雲の設定
#define CLOUD_NUM (3)		// 雲の数
#define CLOUD_WIDTH (370)	// 雲の幅
#define CLOUD_HEIGHT (210)	// 雲の高さ

// 背景画像用のグローバル変数
int g_SkyHandle = 0;
int g_SunHandle = 0;

// 雲に関する変数をまとめた構造体
struct CloudData
{
	int handle;		// 画像ハンドル
	float posX;		// X座標
	float posY;		// Y座標
	float moveX;	// X移動量
	float moveY;	// Y移動量
};

// 雲の数だけデータを用意する
CloudData g_CloudData[CLOUD_NUM] = { 0 };

// 初期化関数
// 始まる前に1回しか呼ばれない
void GameInit()
{
	// 空の画像をロードする
	g_SkyHandle = LoadGraph("Resource/BG/Sky.png");

	// 太陽の画像をロードする
	g_SunHandle = LoadGraph("Resource/BG/Sun.png");

	// 全ての雲の初期化
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		// 雲の画像をロードする
		g_CloudData[i].handle = LoadGraph("Resource/BG/Cloud.png");

		// 雲の初期位置を設定する
		g_CloudData[i].posX = 1920.0f + i * 400.0f;
		g_CloudData[i].posY = 50.0f + i * 200.0f;

		// 雲の移動量を設定する
		g_CloudData[i].moveX = i % 2 == 0 ? -2.0f : 2.0f;
		g_CloudData[i].moveY = i % 2 == 0 ? 0.5f : -0.5f;
	}
}

// 更新関数
// ゲームが動いている間ずっと呼ばれる
void GameUpdate()
{
	// 全ての雲を移動させる
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		// 雲を移動させる
		g_CloudData[i].posX += g_CloudData[i].moveX;
		g_CloudData[i].posY += g_CloudData[i].moveY;

		// 雲が通り過ぎたかをチェック
		if (g_CloudData[i].posX <= -CLOUD_WIDTH)	// 左端
		{
			// 雲を画面の右端に移動させる
			g_CloudData[i].posX = SCREEN_WIDTH;
		}
		else if (g_CloudData[i].posX >= SCREEN_WIDTH)	// 右端
		{
			// 雲を画面の左端に移動させる
			g_CloudData[i].posX = -CLOUD_WIDTH;
		}
		else if (g_CloudData[i].posY >= SCREEN_HEIGHT)	// 下端
		{
			// 雲を画面の上端に移動させる
			g_CloudData[i].posY = -CLOUD_HEIGHT;
		}
		else if (g_CloudData[i].posY <= -CLOUD_HEIGHT)	// 上端
		{
			// 雲を画面の下端に移動させる
			g_CloudData[i].posY = SCREEN_HEIGHT;
		}

	}
}

// 描画関数
// 画面に描画する
void GameDraw()
{
	// 空の画像を描画する
	DrawGraph(0, 0, g_SkyHandle, TRUE);

	// 太陽を描画
	DrawGraph(-600, 0, g_SunHandle, TRUE);

	// 全ての雲を描画する
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		// 雲を描画する
		DrawGraph((int)g_CloudData[i].posX, (int)g_CloudData[i].posY, (int)g_CloudData[i].handle, TRUE);
	}
}

// 終了関数
// ゲーム終了時に1回だけ呼ばれる
void GameFin()
{
	// もう使わない画像をメモリから削除

	// 空の画像を削除
	DeleteGraph(g_SkyHandle);

	// 太陽の画像を削除
	DeleteGraph(g_SunHandle);

	// 全ての雲の画像を削除
	for (int i = 0; i < CLOUD_NUM; i++)
	{
		// 雲の画像を削除
		DeleteGraph(g_CloudData[i].handle);
	}
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// 画面解像度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// 初期化処理
	GameInit();

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		// 更新処理
		GameUpdate();

		// 描画処理
		GameDraw();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 画面フリップ
		ScreenFlip();
	}

	// 終了処理
	GameFin();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
