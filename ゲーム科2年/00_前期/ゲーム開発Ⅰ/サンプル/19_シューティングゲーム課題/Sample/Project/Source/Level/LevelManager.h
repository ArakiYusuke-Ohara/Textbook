#pragma once

#include "LevelParameter.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new LevelManager; }
	static LevelManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void SetSelectLevel(LevelType level) { m_SelectLevel = level; }

	LevelType GetSelectLevel() const { return m_SelectLevel; }
	const LevelParameter* GetLevelParameter(LevelType level);
	const LevelParameter* GetSelectLevelParameter();

private:
	static LevelManager* m_Instance;
	LevelType m_SelectLevel;
};
