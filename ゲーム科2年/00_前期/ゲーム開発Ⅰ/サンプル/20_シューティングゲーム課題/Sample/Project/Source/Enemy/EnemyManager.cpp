#include "EnemyManager.h"
#include "EnemyBee.h"
#include "EnemyDia.h"
#include "BlueEnemy.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../ObjectMover/ObjectMoverManager.h"
#include "../ObjectMover/ObjectMoverParameter.h"
#include "../ObjectMover/EaseInOut.h"
#include "../MyEffekseer/EffekseerParameter.h"

EnemyManager* EnemyManager::m_Instance = nullptr;

// データ群はエクセルにしたい
const EnemyParameter ENEMY_MASTER_PARAM[] = {
	{10, 10, 0.2f, 1.0f},
	{10, 8, 0.2f, 3.0f},
};

const EnemyLocate ENEMY_LOCATE_DATA[] = {
	{ ENEMY_BEE, 20.0f, {6.0f, 30.0f, 70.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 0 },
	{ ENEMY_BEE, 20.0f, {-6.0f,30.0f, 100.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 1 },
	{ ENEMY_BEE, 20.0f, {6.0f, 10.0f, 120.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 1 },
	{ ENEMY_BEE, 20.0f, {-6.0f,10.0f, 160.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 1 },
	{ ENEMY_BEE, 20.0f, {6.0f, 30.0f, 160.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 1 },
	{ ENEMY_BEE, 20.0f, {-6.0f,30.0f, 250.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 1 },
	{ ENEMY_BEE, 20.0f, {6.0f, 10.0f, 260.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 1 },
	{ ENEMY_BEE, 20.0f, {-6.0f,10.0f, 270.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 1 },
	{ ENEMY_BEE, 20.0f, {6.0f, 30.0f, 280.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 1 },
	{ ENEMY_BEE, 20.0f, {-6.0f,30.0f, 290.0f}, {0.0f, DX_PI_F, 0.0f}, OBJECT_MOVER_EASE_IN_OUT, 1 },
};

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	Fin();
}

void EnemyManager::Init()
{
	// クローン元のエネミーを生成する
	m_OriginalEnemy[ENEMY_BEE] = new EnemyBee;
	m_OriginalEnemy[ENEMY_DIA] = new EnemyDia;

	// クローン元のエネミーをロードする
	for (EnemyBase* enemy : m_OriginalEnemy)
	{
		enemy->Init();
	}
}

void EnemyManager::Load()
{
	// クローン元のエネミーをロードする
	for (EnemyBase* enemy : m_OriginalEnemy)
	{
		enemy->Load();
	}
}

void EnemyManager::Start()
{
	int enemyNum = sizeof(ENEMY_LOCATE_DATA) / sizeof(EnemyLocate);
	for(int i = 0; i < enemyNum; i++)
	{
		const EnemyLocate* locate = &ENEMY_LOCATE_DATA[i];
		// エネミー生成
		EnemyBase* enemy = CreateEnemy(locate->type);
		// 配置情報
		enemy->SetLocate(locate);
		// 出現距離設定
		enemy->SetEncountDist(locate->encountDist);
		// 初期位置設定
		enemy->SetPos(locate->pos);
		// 初期回転値設定
		enemy->SetRot(locate->rot);
		// プレイヤーが近づくまで非アクティブ
		enemy->SetActive(false);
	}

	for (auto enemy : m_EnemyList)
	{
		enemy->Start();
	}
}

void EnemyManager::Step()
{
	// エネミー出現システムステップ
	StepEnemyEncounter();

	// 範囲for文で安全にリストを回せる
	for (auto enemy : m_EnemyList)
	{
		if (enemy->IsActive())
		{
			enemy->Step();
		}
	}
}

void EnemyManager::Update()
{
	// 範囲for文で安全にリストを回せる
	for (auto enemy : m_EnemyList)
	{
		if (enemy->IsActive())
		{
			enemy->Update();
		}
	}
}

void EnemyManager::Draw()
{
	// 範囲for文で安全にリストを回せる
	for (auto enemy : m_EnemyList)
	{
		if (enemy->IsActive())
		{
			enemy->Draw();
		}
	}
}

void EnemyManager::Fin()
{
	// 範囲for文で安全にリストを回せる
	for (auto enemy : m_EnemyList)
	{
		delete enemy;
	}

	// リストをクリア
	m_EnemyList.clear();

	// クローン元も削除する
	for (auto enemy : m_OriginalEnemy)
	{
		delete enemy;
	}
}

EnemyBase* EnemyManager::CreateEnemy(EnemyType type)
{
	// タイプに合わせたエネミーをクローンで生成
	EnemyBase* enemy = m_OriginalEnemy[type]->Clone();

	// パラメータ設定
	enemy->SetParameter(&ENEMY_MASTER_PARAM[type]);

	// 準備
	enemy->Setup();

	// 生成したエネミーを管理用リストに追加
	m_EnemyList.push_back(enemy);

	// 返却すれば生成した後にいろいろいじれる
	return enemy;
}

void EnemyManager::CheckHP()
{
	for (EnemyBase* enemy : m_EnemyList)
	{
		if (enemy->IsActive() && enemy->GetHP() <= 0)
		{
			enemy->Dead();
		}
	}

}

void EnemyManager::StepEnemyEncounter()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPos();

	for (EnemyBase* enemy : m_EnemyList)
	{
		// 死亡している敵は無視
		if (enemy->IsDead()) continue;
		// 既にアクティブになってる敵も無視
		if (enemy->IsActive()) continue;

		// プレイヤーとのZ距離が一定距離になったらアクティブ
		if ((enemy->GetPos().z - playerPos.z) <= enemy->GetEncountDist())
		{
			EncountEnemy(enemy);
		}
	}
}

void EnemyManager::EncountEnemy(EnemyBase* enemy)
{
	enemy->SetActive(true);

	const EnemyLocate* locate = enemy->GetLocate();
	switch (locate->moveType)
	{
	case OBJECT_MOVER_EASE_IN_OUT:
	{
		const EaseInOutParam* param = ObjectMoverManager::GetInstance()->GetEaseInOutParam(locate->moveParamId);
		EaseInOut* mover = ObjectMoverManager::GetInstance()->CreateObjectMover<EaseInOut>();
		mover->SetParam(param);
		enemy->SetMover(mover);
		break;
	}

	}
}
