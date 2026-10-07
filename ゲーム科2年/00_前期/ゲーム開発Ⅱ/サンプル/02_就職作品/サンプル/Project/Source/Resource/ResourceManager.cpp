#include "ResourceManager.h"
#include "Model.h"

ResourceManager* ResourceManager::m_Instance = nullptr;


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	Fin();
}

Model* ResourceManager::LoadModel(const char* path)
{
	Model* model = new Model;
	model->Load(path);
	m_Models.push_back(model);

	return model;
}

void ResourceManager::Fin()
{
	for (Resource* resource : m_Models)
	{
		delete resource;
	}

	m_Models.clear();
}
