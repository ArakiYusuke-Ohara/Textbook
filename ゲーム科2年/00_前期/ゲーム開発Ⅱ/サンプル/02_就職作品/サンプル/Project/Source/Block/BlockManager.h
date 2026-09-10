#pragma once
#include "DxLib.h"
#include <vector>

class Object;

class BlockManager
{
public:
	BlockManager() = default;
	~BlockManager();

	static void CreateInstance() { if (!m_Instance) m_Instance = new BlockManager; }
	static BlockManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	Object* SpawnBlock(VECTOR pos, VECTOR rot, VECTOR scale);

	void Fin();

private:
	static BlockManager* m_Instance;
	std::vector<Object*> m_Blocks;

};
