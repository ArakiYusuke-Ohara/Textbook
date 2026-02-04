#include "DxLib.h"
#include "PlayScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../Collision/CollisionManager.h"
#include "../Player/PlayerManager.h"
#include "../Camera/CameraManager.h"
#include "../Block/BlockManager.h"
#include "../Goal/GoalManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Floor/Floor.h"


PlayScene::PlayScene() : SceneBase()
{
	m_Floor = nullptr;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	// コリジョンマネージャー生成
	CollisionManager::CreateInstance();

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

	// 床生成（現状、床だけ管理クラスがない。。。）
	m_Floor = new Floor;
	// 初期化
	m_Floor->Init();

	// ブロックマネージャーを生成
	BlockManager::CreateInstance();
	BlockManager* boxManager = BlockManager::GetInstance();
	// ブロックマネージャー初期化
	boxManager->Init();

	// ゴールマネージャー生成
	GoalManager::CreateInstance();
	GoalManager* goalManager = GoalManager::GetInstance();
	// ゴール生成
	goalManager->CreateGoal();
	// 初期化
	goalManager->Init();

	// エネミーマネージャー生成
	EnemyManager::CreateInstance();
	EnemyManager* enemyManager = EnemyManager::GetInstance();
	// 初期化
	enemyManager->Init();

}

void PlayScene::Load()
{
	// プレイヤーをロード
	PlayerManager::GetInstance()->Load();

	// カメラロード
	CameraManager::GetInstance()->Load();

	// ブロックをロード
	BlockManager::GetInstance()->Load();

	// ゴールをロード
	GoalManager::GetInstance()->Load();

	// エネミーをロード
	EnemyManager::GetInstance()->Load();

	//床をロード
	m_Floor->Load();
}

void PlayScene::Start()
{
	// プレイヤー開始
	PlayerManager::GetInstance()->Start();

	// カメラ開始
	CameraManager::GetInstance()->Start();

	// ブロック開始
	BlockManager::GetInstance()->Start();

	// ゴール開始
	GoalManager::GetInstance()->Start();

	// エネミー配置
	EnemyManager* enemyManger = EnemyManager::GetInstance();
	// 赤エネミー生成
	EnemyBase* enemy = enemyManger->CreateEnemy(RED_ENEMY);
	enemy->SetPos(VGet(3.0f, 1.0f, 0.0f));
	// 青エネミー生成
	enemy = enemyManger->CreateEnemy(BLUE_ENEMY);
	enemy->SetPos(VGet(-3.0f, 1.0f, 0.0f));

	// エネミー開始
	enemyManger->Start();

	// 床開始
	m_Floor->Start();
}

void PlayScene::Step()
{
	CameraManager* cameraManager = CameraManager::GetInstance();

	// デバッグカメラモード切り替え
	if (Input::IsTriggerKey(Input::KEY_1))
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
	}
	// デバッグカメラがOFFの時のみそれぞれのオブジェクトを動かす
	else
	{
		// プレイヤーステップ
		PlayerManager::GetInstance()->Step();
		// エネミーステップ
		EnemyManager::GetInstance()->Step();
		// カメラステップ
		CameraManager::GetInstance()->Step();
		// 床ステップ
		m_Floor->Step();
		// ボックスステップ
		BlockManager::GetInstance()->Step();
		// ゴールステップ
		GoalManager::GetInstance()->Step();
		// 当たり判定
		CollisionManager::GetInstance()->CheckCollision();
	}

}

void PlayScene::Update()
{
	// プレイヤー更新
	PlayerManager::GetInstance()->Update();
	// エネミー更新
	EnemyManager::GetInstance()->Update();
	// カメラ更新
	CameraManager::GetInstance()->Update();
	// 床更新
	m_Floor->Update();
	// ボックス更新
	BlockManager::GetInstance()->Update();
	// ゴール更新
	GoalManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();
	// エネミー描画
	EnemyManager::GetInstance()->Draw();
	// カメラ描画
	CameraManager::GetInstance()->Draw();
	// 床描画
	m_Floor->Draw();
	// ボックス描画
	BlockManager::GetInstance()->Draw();
	// ゴール描画
	GoalManager::GetInstance()->Draw();

	// 当たり判定描画
	CollisionManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	// プレイヤーマネージャー削除
	PlayerManager::DeleteInstance();

	// カメラマネージャー削除
	CameraManager::DeleteInstance();

	// ボックスマネージャー削除
	BlockManager::DeleteInstance();

	// ゴールマネージャー削除
	GoalManager::DeleteInstance();

	// コリジョンマネージャー削除
	CollisionManager::DeleteInstance();

	// エネミーマネージャー削除
	EnemyManager::DeleteInstance();

	// 床削除
	delete m_Floor;
}
