#include "BlockManager.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Model.h"
#include "../Object/Object.h"
#include "../Component/ModelRenderer.h"

BlockManager* BlockManager::m_Instance = nullptr;

BlockManager::BlockManager()
{
	m_Blocks = {};
	m_BlockModels = {};
}

BlockManager::~BlockManager()
{
	Fin();
}

void BlockManager::Load()
{
	m_BlockModels[BLOCK_ID_GRASS] = ResourceManager::GetInstance()->LoadModel("Data/Block/Grass.x");
}

void BlockManager::Update()
{
	for (Object* block : m_Blocks)
	{
		block->Update();
	}
}

void BlockManager::Fin()
{
	for (Object* block : m_Blocks)
	{
		delete block;
	}
	m_Blocks.clear();

}

Object* BlockManager::SpawnBlock(BlockID id, VECTOR pos, VECTOR rot, VECTOR scale)
{
	// 生成
	Object* block = new Object;

	// モデルをセット
	ModelRenderer* renderer = block->AddComponent<ModelRenderer>();
	renderer->SetModel(m_BlockModels[id]);

	return block;
}

