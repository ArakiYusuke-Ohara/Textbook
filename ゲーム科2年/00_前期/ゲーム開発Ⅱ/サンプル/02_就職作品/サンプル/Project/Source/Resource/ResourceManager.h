#pragma once
#include <vector>

class Resource;
class Model;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static void CreateInstance() { if (!m_Instance) m_Instance = new ResourceManager; }
	static ResourceManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	Model* LoadModel(const char* path);

	void Fin();

private:
	static ResourceManager* m_Instance;
	std::vector<Resource*> m_Resources;
};
