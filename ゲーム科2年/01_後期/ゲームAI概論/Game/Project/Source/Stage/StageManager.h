#pragma once

#include "../Singleton/Singleton.h"
#include <vector>

class Stage;

class StageManager : public Singleton<StageManager>
{
public:
	StageManager();
	~StageManager();

public:
	void Load();
	void Draw();
	void Fin();

	Stage* GetStage() const { return m_Stage; }

public:
	void CreateStage();

private:
	Stage* m_Stage;
};
