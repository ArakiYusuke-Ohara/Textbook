#include "DxLib.h"
#include "GameSetting/GameSetting.h"
#include "Player/Player.h"

// 初期化関数
// 始まる前に1回しか呼ばれない
void GameInit()
{
	InitPlayer();
}

// 更新関数
// ゲームが動いている間ずっと呼ばれる
void GameUpdate()
{
	UpdatePlayer();
}

// 描画関数
// 画面に描画する
void GameDraw()
{
	DrawPlayer();
}

// 終了関数
// ゲーム終了時に1回だけ呼ばれる
void GameFin()
{
	FinPlayer();
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
