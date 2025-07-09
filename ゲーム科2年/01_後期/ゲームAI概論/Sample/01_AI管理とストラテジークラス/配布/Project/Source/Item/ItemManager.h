#pragma once
#include "DxLib.h"
#include "../Singleton/Singleton.h"
#include "ItemParameter.h"
#include <vector>

class Item;

class ItemManager : public Singleton<ItemManager>
{
public:
	ItemManager();
	~ItemManager();

public:
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Fin();

	Item* CreateItem(int id);
	Item* CreateItem(int id, VECTOR pos);

public:
	std::vector<Item*> GetItems() const { return m_Items; }

private:
	void SpawnItem();

private:
	std::vector<Item*> m_Originals;
	std::vector<Item*> m_Items;

	int m_SpawnTimer;
};
