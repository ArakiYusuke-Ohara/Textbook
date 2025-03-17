#include "DxLib.h"
#include "PlayScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../Collision/CollisionManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Player/AIPlayer.h"
#include "../Stage/StageManager.h"
#include "../Block/BlockManager.h"
#include "../AI/AIManager.h"
#include "../AI/AIPlayCPU.h"
#include "../AI/AIRandomCPU.h"
#include "../Bullet/BulletManager.h"

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

	// バレットマネージャー生成
	BulletManager::CreateInstance();

	// プレイヤーマネージャーを生成
	PlayerManager::CreateInstance();
	PlayerManager* playerManager = PlayerManager::GetInstance();
	playerManager->Init();
	// 操作プレイヤーを1Pとして生成
	playerManager->CreatePlayer(0);

	// CPUを2Pとして生成
	AIPlayer* cpuPlayer = playerManager->CreateAIPlayer(1);
	// AIマネージャーを生成
	AIManager::CreateInstance();
	AIManager* aiManager = AIManager::GetInstance();
	// CPU用のAIを生成と設定
	AIPlayCPU* ai = aiManager->CreateAI<AIPlayCPU>();
	ai->SetAwayDistance(200.0f);
	ai->SetOwner(cpuPlayer);
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

	// バレットをロード
	BulletManager::GetInstance()->Load();

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
	// バレットステップ
	BulletManager::GetInstance()->Step();
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
	// バレット描画
	BulletManager::GetInstance()->Draw();
	// ボックス描画
	BlockManager::GetInstance()->Draw();
	// 当たり判定描画
	CollisionManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	// ステージマネージャー削除
	StageManager::DeleteInstance();

	// バレットマネージャー削除
	BulletManager::DeleteInstance();

	// プレイヤーマネージャー削除
	PlayerManager::DeleteInstance();

	// ボックスマネージャー削除
	BlockManager::DeleteInstance();

	// コリジョンマネージャー削除
	CollisionManager::DeleteInstance();

	// AIマネージャーを削除
	AIManager::DeleteInstance();
}
