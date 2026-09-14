#pragma once
#include <vector>

class Component;
class Renderer;

class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	static void CreateInstance() { if (!m_Instance) m_Instance = new ComponentManager; }
	static ComponentManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	void Render();
	void Fin();

	template<typename T>
	void Register(T* component);

private:
	static ComponentManager* m_Instance;
	std::vector<Renderer*> m_Renderers;
};

template<>
inline void ComponentManager::Register<Renderer>(Renderer* component)
{
	m_Renderers.push_back(component);
}
