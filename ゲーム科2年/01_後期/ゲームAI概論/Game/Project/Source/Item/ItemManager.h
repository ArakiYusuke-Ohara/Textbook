#pragma once
#include "../Singleton/Singleton.h"
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

private:
	std::vector<Item*> m_Originals;
	std::vector<Item*> m_Items;
};
