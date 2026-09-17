#pragma once
#include "ResourceParameter.h"
#include <array>

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

	Model* LoadModel(ModelID id);
	Model* GetModel(ModelID id) const { return m_Models[id]; }

	void Fin();

private:
	static ResourceManager* m_Instance;
	std::array<Model*, MODEL_ID_MAX> m_Models;
};
