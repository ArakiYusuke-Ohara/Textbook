#include "EasingManager.h"
#include "Easing.h"

EasingManager::EasingManager()
{
}

EasingManager::~EasingManager()
{
}

void EasingManager::Update()
{
	for (Easing* easing : m_EasingObjects)
	{
		if (easing->IsActive())
		{
			easing->Update();
		}
	}
}

Easing* EasingManager::CreateEasing()
{
	Easing* easing = nullptr;
	for (Easing* e : m_EasingObjects)
	{
		if (!e->IsActive())
		{
			easing = e;
			break;
		}
	}

	if (!easing)
	{
		easing = new Easing;
		m_EasingObjects.push_back(easing);
	}

	return easing;
}
