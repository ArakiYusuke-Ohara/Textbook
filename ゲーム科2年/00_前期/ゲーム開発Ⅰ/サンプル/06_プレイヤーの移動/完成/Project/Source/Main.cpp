#include "DxLib.h"
#include "Player/PlayerManager.h"
#include "Camera/CameraManager.h"
#include "Block/BlockManager.h"
#include "Input/Input.h"
#include "FPS/FPS.h"
#include "Floor/Floor.h"

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

	// 床生成
	Floor* floor = new Floor;
	// 初期化～開始
	floor->Init();
	floor->Load();
	floor->Start();

	// ボックスマネージャーを生成
	BlockManager::CreateInstance();
	BlockManager* boxManager = BlockManager::GetInstance();
	// 初期化～開始
	boxManager->Init();
	boxManager->Load();
	boxManager->Start();

	// 入力初期化
	Input::Init();

	// FPS初期化
	FPSSystem::Init();

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 1ミリ秒待機すると処理が安定する
		Sleep(1);

		// 画面をクリア
		ClearDrawScreen();

		// 入力更新
		Input::Update();

		// プレイヤーステップ
		playerManager->Step();
		// カメラステップ
		cameraManager->Step();
		// 床ステップ
		floor->Step();
		// ボックスステップ
		boxManager->Step();

		// プレイヤー更新
		playerManager->Update();
		// カメラアップデート
		cameraManager->Update();
		// 床更新
		floor->Update();
		// ボックス更新
		boxManager->Update();


		// プレイヤー描画
		playerManager->Draw();
		// カメラ描画
		cameraManager->Draw();
		// 床描画
		floor->Draw();
		// ボックス描画
		boxManager->Draw();


		// 入力描画
		Input::Draw();

		// FPS更新
		FPSSystem::Update();
		// FPS描画
		FPSSystem::Draw();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 1フレームが速すぎた場合の待機
		FPSSystem::WaitFPS();

		// 画面フリップ
		ScreenFlip();
	}

	// プレイヤーマネージャー削除
	PlayerManager::DeleteInstance();

	// カメラマネージャー削除
	CameraManager::DeleteInstance();

	// ボックスマネージャー削除
	BlockManager::DeleteInstance();

	// 床削除
	delete floor;

	// 入力終了
	Input::Fin();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
