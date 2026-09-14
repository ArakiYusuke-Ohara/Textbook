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

Model* ResourceManager::LoadModel(ModelID id)
{
	Model* model = new Model;
	model->Load(MODEL_PATH_LIST[id]);
	m_Models[id] = model;

	return model;
}

void ResourceManager::Fin()
{
	for (Resource* resource : m_Models)
	{
		delete resource;
	}
}
