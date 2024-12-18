#include "DxLib.h"
#include "GameSetting/GameSetting.h"
#include "Player/Player.h"
#include "Input/Input.h"
#include "Enemy/BlueEnemy.h"
#include "Enemy/RedEnemy.h"
#include "Collision/Collision.h"

// 初期化関数
// 始まる前に1回しか呼ばれない
void GameInit()
{
	// 入力初期化
	InitInput();

	// プレイヤー初期化
	InitPlayer();

	// 赤エネミー初期化
	InitRedEnemy();

	// 青エネミー初期化
	InitBlueEnemy();
}

// 更新関数
// ゲームが動いている間ずっと呼ばれる
void GameUpdate()
{
	// 入力更新
	UpdateInput();

	// プレイヤー更新
	UpdatePlayer();

	// 赤エネミー更新
	UpdateRedEnemy();

	// 青エネミー更新
	UpdateBlueEnemy();

	// 当たり判定は全ての更新が終わった後に呼ぶ
	CheckCollision();
}

// 描画関数
// 画面に描画する
void GameDraw()
{
	// プレイヤー描画
	DrawPlayer();

	// 入力描画
	DrawInput();

	// 赤エネミー描画
	DrawRedEnemy();

	// 青エネミー描画
	DrawBlueEnemy();
}

// 終了関数
// ゲーム終了時に1回だけ呼ばれる
void GameFin()
{
	// 入力終了
	FinInput();

	// プレイヤー終了
	FinPlayer();

	// 赤エネミー終了
	FinRedEnemy();

	// 青エネミー終了
	FinBlueEnemy();
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ウィンドウサイズ設定
	SetWindowSize((int)(SCREEN_WIDTH * WINDOW_SIZE_RATE), (int)(SCREEN_HEIGHT * WINDOW_SIZE_RATE));

	// 透過色の設定
	SetTransColor(TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B);

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
