#include "DxLib.h"
#include "Player/PlayerManager.h"
#include "Block/BlockManager.h"
#include "Collision/CollisionManager.h"
#include "Scene/SceneManager.h"
#include "MyEffekseer/EffekseerManager.h"
#include "Input/Input.h"
#include "FPS/FPS.h"
#include "MyMath/MyMath.h"
#include "MyRandom/MyRandom.h"
#include "Easing/EasingManager.h"
#include "Game/GameSetting.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	// Effekseerセットアップ
	EffekseerManager::CreateInstence();
	EffekseerManager::GetInstance()->Setup();

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// シーンマネージャー生成
	SceneManager::CreateInstance();
	// シーン初期化
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Init();

	// 入力初期化
	Input::Init();

	// FPS初期化
	FPSSystem::Init();

	// イージングマネージャー生成
	EasingManager::CreateInstance();

	// 乱数システム初期化
	MyRandom::Init();

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 1ミリ秒待機すると処理が安定する
		Sleep(1);

		// 画面をクリア
		ClearDrawScreen();

		// 入力更新
		Input::Update();

		// イージング更新
		EasingManager::GetInstance()->Update();

		// シーンを更新
		sceneManager->Update();

		// 入力描画
		Input::Draw();

		// FPS更新
		FPSSystem::Update();

#ifdef _DEBUG
		// FPS描画
		FPSSystem::Draw();
#endif
		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 1フレームが速すぎた場合の待機
		FPSSystem::WaitFPS();

		// 画面フリップ
		ScreenFlip();
	}

	// シーンマネージャー削除
	SceneManager::DeleteInstance();

	// Effekseer削除
	EffekseerManager::DeleteInstance();

	// イージングマネージャー削除
	EasingManager::DeleteInstance();

	// 入力終了
	Input::Fin();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
