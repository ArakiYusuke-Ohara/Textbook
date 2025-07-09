#pragma once

#include "../Singleton/Singleton.h"
#include <vector>

class Easing;

enum EasingType
{
	EASE_IN_SLIDE,
	EASE_OUT_SLIDE,
	EASE_OUT_ELASTIC,
	EASE_IN_OUT_ELASTIC,
	EASING_TYPE_MAX,
};

class EasingManager : public Singleton<EasingManager>
{
public:
	EasingManager();
	~EasingManager();

public:
	void Update();

	Easing* CreateEasing();

private:
	std::vector<Easing*> m_EasingObjects;
};
