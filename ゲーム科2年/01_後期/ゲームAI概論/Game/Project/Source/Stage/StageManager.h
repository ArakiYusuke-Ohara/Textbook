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
	void CreateStage();

	void Load();
	void Draw();
	void Fin();

private:
	Stage* m_Stage;
};
