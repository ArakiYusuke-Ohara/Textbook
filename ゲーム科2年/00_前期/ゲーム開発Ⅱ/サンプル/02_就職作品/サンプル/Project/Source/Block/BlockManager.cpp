#include "BlockManager.h"
#include "../Object/Object.h"
#include "../Component/ModelRenderer.h"

BlockManager* BlockManager::m_Instance = nullptr;

BlockManager::~BlockManager()
{
	Fin();
}

Object* BlockManager::SpawnBlock(VECTOR pos, VECTOR rot, VECTOR scale)
{
	Object* block = new Object;
	ModelRenderer* renderer = block->AddComponent<ModelRenderer>();
	// renderer->SetModel();

	return block;
}

void BlockManager::Fin()
{

}
