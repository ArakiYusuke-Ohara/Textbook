#include "BlockManager.h"
#include "BlockParameter.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Model.h"
#include "../Object/Object.h"
#include "../Component/ModelRenderer.h"

BlockManager* BlockManager::m_Instance = nullptr;

BlockManager::~BlockManager()
{
	Fin();
}

void BlockManager::Load()
{
	for (const BlockParameter& data : BLOCK_MASTER_PARAM)
	{
		Model* model = ResourceManager::GetInstance()->LoadModel(data.modelID);
	}
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
	Model* model = ResourceManager::GetInstance()->GetModel(BLOCK_MASTER_PARAM[id].modelID);
	renderer->SetModel(model);

	return block;
}

