#include "Model.h"
#include "DxLib.h"

Model::Model() : 
m_Handle(-1)
{
}

Model::~Model()
{
	Fin();
}

void Model::Load(const char* path)
{
	m_Handle = MV1LoadModel(path);
}

void Model::Draw()
{
	MV1DrawModel(m_Handle);
}

void Model::Fin()
{
	MV1DeleteModel(m_Handle);
}
