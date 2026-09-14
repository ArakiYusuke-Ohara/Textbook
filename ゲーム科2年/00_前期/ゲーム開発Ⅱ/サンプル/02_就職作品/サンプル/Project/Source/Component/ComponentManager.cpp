#include "ComponentManager.h"
#include "Renderer.h"

ComponentManager* ComponentManager::m_Instance = nullptr;


ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::Render()
{
	// •`‰æ
	for (Renderer* renderer : m_Renderers)
	{
		renderer->Render();
	}
}

void ComponentManager::Fin()
{
	for (Renderer* renderer : m_Renderers)
	{
		delete renderer;
	}
	m_Renderers.clear();
}
