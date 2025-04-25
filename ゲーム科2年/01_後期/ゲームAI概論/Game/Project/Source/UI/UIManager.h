#pragma once

#include "../Singleton/Singleton.h"
#include "UIBase.h"
#include "UIParameter.h"
#include <vector>

class UIBase;

class UIManager : public Singleton<UIManager>
{
public:
	UIManager();
	~UIManager();

public:
	void Init();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	UIBase* CreateUI(int id);

private:
	std::vector<UIBase*> m_UIs;
};
