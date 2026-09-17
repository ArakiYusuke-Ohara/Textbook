#pragma once
#include "DxLib.h"
#include "BlockParameter.h"
#include <vector>
#include <array>

class Object;
class Model;

class BlockManager
{
public:
	BlockManager() = default;
	~BlockManager();

	static void CreateInstance() { if (!m_Instance) m_Instance = new BlockManager; }
	static BlockManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	void Load();
	void Update();
	void Fin();

	Object* SpawnBlock(BlockID id, VECTOR pos, VECTOR rot, VECTOR scale);

private:
	static BlockManager* m_Instance;
	std::array<Model*, BLOCK_ID_MAX> m_BlockData;
	std::vector<Object*> m_Blocks;

};
