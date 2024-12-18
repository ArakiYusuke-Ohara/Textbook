#include "DxLib.h"
#include "Player/Player.h"
#include "Camera/Camera.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// プレイヤーを生成
	Player* player = new Player();
	player->Init();		// 初期化
	player->Load();		// ロード
	player->Start();	// 開始

	// カメラを生成
	Camera* camera = new Camera();
	camera->Init();		// 初期化
	camera->Load();		// ロード
	camera->Start();	// 開始

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		// プレイヤーステップ
		player->Step();
		// カメラステップ
		camera->Step();

		// プレイヤー更新
		player->Update();
		// カメラアップデート
		camera->Update();


		// プレイヤー描画
		player->Draw();
		// カメラ描画
		camera->Draw();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 画面フリップ
		ScreenFlip();
	}

	// プレイヤー削除
	delete player;

	// カメラ削除
	delete camera;

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
