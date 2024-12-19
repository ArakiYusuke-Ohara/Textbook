#include "DxLib.h"
#include "PlayScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../Collision/CollisionManager.h"
#include "../Player/PlayerManager.h"
#include "../Camera/CameraManager.h"
#include "../Goal/GoalManager.h"
#include "../Collision/CollisionManager.h"
#include "../Floor/Floor.h"
#include "../Stage/StageManager.h"


PlayScene::PlayScene() : SceneBase()
{
}

PlayScene::~PlayScene()
{
	Fin();
}

void PlayScene::Init()
{
	// コリジョンマネージャー生成
	CollisionManager::CreateInstance();

	// ステージ生成
	StageManager::CreateInstance();
	StageManager::GetInstance()->Init();

	// プレイヤーマネージャーを生成
	PlayerManager::CreateInstance();
	PlayerManager* playerManager = PlayerManager::GetInstance();
	// プレイヤーを生成
	playerManager->CreatePlayer();
	// プレイヤーの初期化～開始
	playerManager->Init();

	// カメラマネージャーを生成
	CameraManager::CreateInstance();
	// カメラマネージャーを取得
	CameraManager* cameraManager = CameraManager::GetInstance();
	// カメラを生成
	cameraManager->CreateCamera(CAMERA);
	cameraManager->CreateCamera(DEBUG_CAMERA);
	// カメラの初期化
	cameraManager->Init();

	// ゴールマネージャー生成
	GoalManager::CreateInstance();
	GoalManager* goalManager = GoalManager::GetInstance();
	// ゴール生成
	goalManager->CreateGoal();
	// 初期化
	goalManager->Init();
}

void PlayScene::Load()
{
	// ステージをロード
	StageManager::GetInstance()->Load();

	// プレイヤーをロード
	PlayerManager::GetInstance()->Load();

	// カメラロード
	CameraManager::GetInstance()->Load();

	// ゴールをロード
	GoalManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	// プレイヤー開始
	PlayerManager::GetInstance()->Start();

	// カメラ開始
	CameraManager::GetInstance()->Start();

	// ゴール開始
	GoalManager::GetInstance()->Start();
}

void PlayScene::Step()
{
	CameraManager* cameraManager = CameraManager::GetInstance();

	// デバッグカメラモード切り替え
	if (Input::IsTriggerKey(KEY_1))
	{
		CameraManager* cameraManager = CameraManager::GetInstance();
		// デバッグカメラON/OFF切り替え
		bool isDebugCamera = cameraManager->IsDebugCameraMode();
		if (isDebugCamera)
		{
			// デバッグカメラ解除
			cameraManager->ReleaseDebugCameraMode();
		}
		else
		{
			// デバッグカメラON
			cameraManager->ChangeDebugCameraMode();
		}
	}

	if (cameraManager->IsDebugCameraMode())
	{
		// デバッグカメラがONのときはカメラだけStep/Updateする
		cameraManager->Step();
		cameraManager->Update();
	}
	// デバッグカメラがOFFの時のみそれぞれのオブジェクトを動かす
	else
	{
		// プレイヤーステップ
		PlayerManager::GetInstance()->Step();
		// ゴールステップ
		GoalManager::GetInstance()->Step();
		// 当たり判定
		CollisionManager::GetInstance()->CheckCollision();
		// カメラステップ
		CameraManager::GetInstance()->Step();
	}

}

void PlayScene::Update()
{
	CameraManager* cameraManager = CameraManager::GetInstance();
	if (cameraManager->IsDebugCameraMode())
	{
		// カメラ更新
		CameraManager::GetInstance()->Update();
	}
	else
	{
		// プレイヤー更新
		PlayerManager::GetInstance()->Update();
		// カメラ更新
		CameraManager::GetInstance()->Update();
		// ゴール更新
		GoalManager::GetInstance()->Update();
	}
}

void PlayScene::Draw()
{
	// ステージ描画
	StageManager::GetInstance()->Draw();
	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();
	// カメラ描画
	CameraManager::GetInstance()->Draw();
	// ゴール描画
	GoalManager::GetInstance()->Draw();

	// 当たり判定描画
	CollisionManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	// ステージ削除
	StageManager::DeleteInstance();

	// プレイヤーマネージャー削除
	PlayerManager::DeleteInstance();

	// カメラマネージャー削除
	CameraManager::DeleteInstance();

	// ゴールマネージャー削除
	GoalManager::DeleteInstance();

	// コリジョンマネージャー削除
	CollisionManager::DeleteInstance();
}
