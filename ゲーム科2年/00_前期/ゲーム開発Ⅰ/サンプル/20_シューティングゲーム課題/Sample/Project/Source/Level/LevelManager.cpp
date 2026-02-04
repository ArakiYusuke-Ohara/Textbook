#include "LevelManager.h"

LevelManager* LevelManager::m_Instance = nullptr;

// データ群はエクセルとかにまとめたい
const LevelParameter LEVEL_PARAMETER[] =
{
	{0, 1, 0, 0},
	{0, 0, 0, 0},
};

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

const LevelParameter* LevelManager::GetLevelParameter(LevelType level)
{
	return &LEVEL_PARAMETER[level];
}

const LevelParameter* LevelManager::GetSelectLevelParameter()
{
	if (m_SelectLevel == LEVEL_TYPE_NONE) return nullptr;

	return &LEVEL_PARAMETER[m_SelectLevel];
}
