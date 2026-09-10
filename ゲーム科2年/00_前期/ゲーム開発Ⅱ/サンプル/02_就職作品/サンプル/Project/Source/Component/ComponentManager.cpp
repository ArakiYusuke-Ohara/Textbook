#include "ComponentManager.h"
#include "Renderer.h"

ComponentManager* ComponentManager::m_Instance = nullptr;


ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::Update()
{
	// ƒŒƒ“ƒ_ƒ‰[•`‰æ
	for (Renderer* renderer : m_Renderers)
	{
		renderer->Render();
	}
}
