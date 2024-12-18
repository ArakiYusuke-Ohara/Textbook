#include "DxLib.h"
#include "Player/PlayerManager.h"
#include "Camera/CameraManager.h"

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

	// プレイヤーマネージャーを生成
	PlayerManager::CreateInstance();
	// プレイヤーマネージャーを取得
	PlayerManager* playerManager = PlayerManager::GetInstance();
	// プレイヤーを生成
	playerManager->CreatePlayer();
	// プレイヤーの初期化～開始
	playerManager->Init();
	playerManager->Load();
	playerManager->Start();

	// カメラマネージャーを生成
	CameraManager::CreateInstance();
	// カメラマネージャーを取得
	CameraManager* cameraManager = CameraManager::GetInstance();
	// カメラを生成
	cameraManager->CreateCamera();
	// カメラの初期化～開始
	cameraManager->Init();
	cameraManager->Load();
	cameraManager->Start();

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		// プレイヤーステップ
		playerManager->Step();
		// カメラステップ
		cameraManager->Step();

		// プレイヤー更新
		playerManager->Update();
		// カメラアップデート
		cameraManager->Update();


		// プレイヤー描画
		playerManager->Draw();
		// カメラ描画
		cameraManager->Draw();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 画面フリップ
		ScreenFlip();
	}

	// プレイヤーマネージャー削除
	PlayerManager::DeleteInstance();

	// カメラマネージャー削除
	CameraManager::DeleteInstance();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
