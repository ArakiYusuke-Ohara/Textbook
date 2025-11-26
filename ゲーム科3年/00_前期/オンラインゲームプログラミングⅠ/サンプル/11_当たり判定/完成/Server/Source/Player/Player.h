#pragma once
#include "../Object/GameObject.h"

class ComponentBase;

class Player : public GameObject
{
public:
	Player();
	~Player() = default;

	void Init();

private:
	int m_ID;
};
