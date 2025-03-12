#include "DxLib.h"
#include "StageManager.h"
#include "Stage.h"

StageManager::StageManager()
{
	m_Stage = nullptr;
}

StageManager::~StageManager()
{
	Fin();
}

void StageManager::CreateStage()
{
	if (!m_Stage)
	{
		m_Stage = new Stage;
	}
}

void StageManager::Load()
{
	m_Stage->Load();
}

void StageManager::Draw()
{
	m_Stage->Draw();
}

void StageManager::Fin()
{
	m_Stage->Fin();
	m_Stage = nullptr;
}
