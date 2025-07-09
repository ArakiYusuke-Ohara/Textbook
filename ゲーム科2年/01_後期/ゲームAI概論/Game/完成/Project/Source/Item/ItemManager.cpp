#include "ItemManager.h"
#include "Item.h"
#include "../Block/BlockParameter.h"
#include "../MyRandom/MyRandom.h"
#include "../Stage/StageManager.h"
#include "../MyMath/MyMath.h"

#define SPAWN_INTERVAL 600
#define SPAWN_NUM 2

ItemManager::ItemManager()
{
	m_Originals = {};
	m_Items = {};
	m_SpawnTimer = 0;
}

ItemManager::~ItemManager()
{
	Fin();
}

void ItemManager::Init()
{
	// オリジナルを生成
	for (int i = 0; i < ITEM_ID_MAX; i++)
	{
		Item* item = new Item;
		item->Init();
		item->SetParam(&ITEM_MASTER_PARAM[i]);
		m_Originals.push_back(item);
	}

	m_SpawnTimer = SPAWN_INTERVAL;
}

void ItemManager::Load()
{
	// オリジナルをロード
	for (Item* item : m_Originals)
	{
		item->Load();
	}
}

void ItemManager::Step()
{
	// アイテムスポーン処理
	SpawnItem();

	for (Item* item : m_Items)
	{
		item->Step();
	}
}

void ItemManager::Update()
{
	for (Item* item : m_Items)
	{
		item->Update();
	}
}

void ItemManager::Draw()
{
	for (Item* item : m_Items)
	{
		item->Draw();
	}
}

void ItemManager::Fin()
{
	// オリジナルを削除
	for (Item* item : m_Originals)
	{
		delete item;
	}
	m_Originals.clear();
	m_Originals.shrink_to_fit();

	// 生成したアイテムを削除
	for (Item* item : m_Items)
	{
		delete item;
	}
	m_Items.clear();
	m_Items.shrink_to_fit();

}

Item* ItemManager::CreateItem(int id)
{
	// 未使用のアイテムがあったら使いまわす
	for (Item* item : m_Items)
	{
		if (!item->IsActive())
		{
			item->SetParam(&ITEM_MASTER_PARAM[id]);
			item->Spawn();
			return item;
		}
	}

	// 未使用がなかったら新しく作る
	Item* item = m_Originals[id]->Clone();
	item->SetParam(&ITEM_MASTER_PARAM[id]);
	item->Spawn();
	m_Items.push_back(item);

	return item;
}

Item* ItemManager::CreateItem(int id, VECTOR pos)
{
	Item* item = CreateItem(id);
	item->SetPos(pos);

	return item;
}

void ItemManager::SpawnItem()
{
	// 一定時間ごとにスポーン
	if (m_SpawnTimer <= 0)
	{
		for (int i = 0; i < SPAWN_NUM; i++)
		{
			// どのアイテムかはランダム
			int id = MyRandom::GetRandom() % ITEM_ID_MAX;

			// ブロックのある位置には出現しないように
			int indexX = MyRandom::GetDistribution(1, BLOCK_MAP_COL - 2);
			int indexY = MyRandom::GetDistribution(1, BLOCK_MAP_ROW - 2);

			VECTOR pos = { (float)(ITEM_WIDTH * indexX), (float)(ITEM_HEIGHT * indexY), 0.0f };

			// ステージ座標からワールド座標に変換
			pos = StageManager::GetInstance()->ConvertStagePosToWorldPos(pos);

			// アイテム生成
			CreateItem(id, pos);
		}

		// タイマーリセット
		m_SpawnTimer = SPAWN_INTERVAL;
	}
	else
	{
		// タイマーカウント
		m_SpawnTimer--;
	}
}
