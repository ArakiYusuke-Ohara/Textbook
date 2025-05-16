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
#include "../Item/ItemManager.h"
#include "../UI/UIManager.h"
#include "../UI/UIImage.h"
#include "../Effect/SpriteAnimationManager.h"

PlayScene::PlayScene() : SceneBase()
{
	m_UIBG = nullptr;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	// 背景画像生成
	m_UIBG = UIManager::GetInstance()->CreateUI<UIImage>();

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

	// アイテムマネージャー生成と初期化
	ItemManager::CreateInstance();
	ItemManager::GetInstance()->Init();

	// スプライトアニメーション管理生成
	SpriteAnimationManager::CreateInstance();
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

	// アイテムをロード
	ItemManager::GetInstance()->Load();

	// スプライトアニメーションをロード
	SpriteAnimationManager::GetInstance()->Load();

	// 背景をロード
	m_UIBG->Load("Data/Play/BG/BG.png");
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
	// まだ決着がついてない
	if (!IsGameSet())
	{
		// UIステップ
		UIManager::GetInstance()->Step();
		// プレイヤーステップ
		PlayerManager::GetInstance()->Step();
		// バレットステップ
		BulletManager::GetInstance()->Step();
		// アイテムステップ
		ItemManager::GetInstance()->Step();
		// 当たり判定
		CollisionManager::GetInstance()->CheckCollision();
		// 決着がついたか
		if (IsGameSet())
		{
			// 決着シーンを上に乗せる
			SceneManager::GetInstance()->AddScene(GAME_SET);
		}
	}

	// スプライトアニメーションは決着後も動いていい
	SpriteAnimationManager::GetInstance()->Step();
}

void PlayScene::Update()
{
	// UI更新
	UIManager::GetInstance()->Update();
	// プレイヤー更新
	PlayerManager::GetInstance()->Update();
	// アイテム更新
	ItemManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	// UIを描画
	UIManager::GetInstance()->Draw();
	// ステージを描画
	StageManager::GetInstance()->Draw();
	// ブロック描画
	BlockManager::GetInstance()->Draw();
	// アイテムを描画
	ItemManager::GetInstance()->Draw();
	// スプライトアニメーション描画
	SpriteAnimationManager::GetInstance()->Draw();
	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();
	// バレット描画
	BulletManager::GetInstance()->Draw();
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

	// アイテム削除
	ItemManager::DeleteInstance();

	// スプライトアニメーション削除
	SpriteAnimationManager::DeleteInstance();

	// UI削除
	UIManager::GetInstance()->ClearUI();
}

bool PlayScene::IsGameSet()
{
	int activeCount = 0;
	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (Player* player : players)
	{
		if (player->IsActive())
		{
			activeCount++;
		}

		// ２体以上生きていれば決着はついてない
		if (activeCount >= 2)
		{
			return false;
		}
	}

	return true;
}
