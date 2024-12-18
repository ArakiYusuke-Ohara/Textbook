#include "DxLib.h"

// 画面設定
#define SCREEN_WIDTH (1920)		// 画面の横幅
#define SCREEN_HEIGHT (1080)	// 画面の高さ
#define SCREEN_COLOR_DEPTH (32)	// 画面のカラービット数

// 背景画像用のグローバル変数
int g_SkyHandle = 0;

// 初期化関数
// 始まる前に1回しか呼ばれない
void GameInit()
{
	// 空の画像をロードする
	g_SkyHandle = LoadGraph("Resource/BG/Sky.png");
}

// 更新関数
// ゲームが動いている間ずっと呼ばれる
void GameUpdate()
{
}

// 描画関数
// 画面に描画する
void GameDraw()
{
	// 空の画像を描画する
	DrawGraph(0, 0, g_SkyHandle, TRUE);
}

// 終了関数
// ゲーム終了時に1回だけ呼ばれる
void GameFin()
{
	// 空の画像を削除
	DeleteGraph(g_SkyHandle);
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
