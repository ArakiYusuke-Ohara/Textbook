#include "ItemManager.h"
#include "Item.h"
#include "../Block/BlockParameter.h"
#include "../MyRandom/MyRandom.h"

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
	for (Item* item : m_Items)
	{
		item->Step();
	}

	// アイテムスポーン処理
	SpawnItem();
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
			item->SetActive(true);
			item->SetParam(&ITEM_MASTER_PARAM[id]);
			return item;
		}
	}

	// 未使用がなかったら新しく作る
	Item* item = m_Originals[id]->Clone();
	item->SetActive(true);
	item->SetParam(&ITEM_MASTER_PARAM[id]);
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
		// どのアイテムかはランダム
		int id = MyRandom::GetRandom() % ITEM_ID_MAX;

		// ブロックのある位置には出現しないように
		int indexX = MyRandom::GetDistribution(1, BLOCK_MAP_COL - 2);
		int indexY = MyRandom::GetDistribution(1, BLOCK_MAP_ROW - 2);
		VECTOR pos = { (float)(ITEM_WIDTH * indexX), (float)(ITEM_HEIGHT * indexY), 0.0f };

		// アイテム生成
		CreateItem(id, pos);

		// タイマーリセット
		m_SpawnTimer = ITEM_SPAWN_INTERVAL;
	}
	else
	{
		// タイマーカウント
		m_SpawnTimer--;
	}
}
