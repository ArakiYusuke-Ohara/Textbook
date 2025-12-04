#pragma once
#include "../Object/GameObject.h"

class ComponentBase;

// サーバー用プレイヤークラス
class Player : public GameObject
{
public:
	Player();
	~Player() = default;

	void Init();

private:
	int m_ID;
};
