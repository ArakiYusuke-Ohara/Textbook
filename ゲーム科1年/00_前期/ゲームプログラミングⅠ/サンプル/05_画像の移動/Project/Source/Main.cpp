#include "DxLib.h"

// 画面設定
#define SCREEN_WIDTH (1920)		// 画面の横幅
#define SCREEN_HEIGHT (1080)	// 画面の高さ
#define SCREEN_COLOR_DEPTH (32)	// 画面のカラービット数

// 背景画像用のグローバル変数
int g_SkyHandle = 0;

// 雲に関する変数
int g_CloudHandle = 0;		// 画像ハンドル
float g_CloudPosX = 0.0f;	// X座標
float g_CloudPosY = 0.0f;	// Y座標
float g_CloudMoveX = 0.0f;	// X移動量
float g_CloudMoveY = 0.0f;	// Y移動量


// 初期化関数
// 始まる前に1回しか呼ばれない
void GameInit()
{
	// 空の画像をロードする
	g_SkyHandle = LoadGraph("Data/BG/Sky.png");

	// 雲の画像をロードする
	g_CloudHandle = LoadGraph("Data/BG/Cloud.png");

	// 雲の初期位置を設定する
	g_CloudPosX = 1920.0f;
	g_CloudPosY = 50.0f;

	// 雲の移動量を設定する
	g_CloudMoveX = -2.0f;
	g_CloudMoveY = 0.0f;
}

// 更新関数
// ゲームが動いている間ずっと呼ばれる
void GameUpdate()
{
	// 雲を移動させる
	g_CloudPosX += g_CloudMoveX;
	g_CloudPosY += g_CloudMoveY;
}

// 描画関数
// 画面に描画する
void GameDraw()
{
	// 空の画像を描画する
	DrawGraph(0, 0, g_SkyHandle, TRUE);

	// 雲を描画する
	DrawGraph((int)g_CloudPosX, (int)g_CloudPosY, g_CloudHandle, TRUE);
}

// 終了関数
// ゲーム終了時に1回だけ呼ばれる
void GameFin()
{
	// もう使わない画像をメモリから削除

	// 空の画像を削除
	DeleteGraph(g_SkyHandle);

	// 雲の画像を削除
	DeleteGraph(g_CloudHandle);
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
