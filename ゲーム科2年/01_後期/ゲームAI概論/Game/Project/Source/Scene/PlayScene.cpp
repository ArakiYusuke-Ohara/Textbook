#include "DxLib.h"
#include "PlayScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../Collision/CollisionManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Stage/StageManager.h"
#include "../Block/BlockManager.h"
#include "../Collision/CollisionManager.h"
#include "../AI/AIManager.h"
#include "../AI/AIParameter.h"

PlayScene::PlayScene() : SceneBase()
{

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
	playerManager->Init();
	// 操作プレイヤーを1Pとして生成
	playerManager->CreatePlayer(0);
	// CPUを2Pとして生成
	Player* cpuPlayer = playerManager->CreatePlayer(1);
	// AIマネージャーを生成
	AIManager::CreateInstance();
	AIManager* aiManager = AIManager::GetInstance();
	// CPU用のAIを生成
	AIStrategyBase* ai = aiManager->CreateAI(AI_STRATEGY_TYPE_A);
	// CPUのAIにセット
	cpuPlayer->SetAIStrategy(ai);

	// ステージマネージャーを生成
	StageManager::CreateInstance();
	StageManager::GetInstance()->CreateStage();

	// ブロックマネージャーを生成
	BlockManager::CreateInstance();
	BlockManager* boxManager = BlockManager::GetInstance();
	// ブロックマネージャー初期化
	boxManager->Init();
}

void PlayScene::Load()
{
	// ステージをロード
	StageManager::GetInstance()->Load();

	// プレイヤーをロード
	PlayerManager::GetInstance()->Load();

	// ブロックをロード
	BlockManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	// プレイヤー開始
	PlayerManager::GetInstance()->Start();

	// ブロック開始
	BlockManager::GetInstance()->Start();
}

void PlayScene::Step()
{
	// プレイヤーステップ
	PlayerManager::GetInstance()->Step();
	// 当たり判定
	CollisionManager::GetInstance()->CheckCollision();
}

void PlayScene::Update()
{
	// プレイヤー更新
	PlayerManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	// ステージを描画
	StageManager::GetInstance()->Draw();
	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();
	// ボックス描画
	BlockManager::GetInstance()->Draw();
	// 当たり判定描画
	CollisionManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	// ステージマネージャー削除
	StageManager::DeleteInstance();

	// プレイヤーマネージャー削除
	PlayerManager::DeleteInstance();

	// ボックスマネージャー削除
	BlockManager::DeleteInstance();

	// コリジョンマネージャー削除
	CollisionManager::DeleteInstance();
}
