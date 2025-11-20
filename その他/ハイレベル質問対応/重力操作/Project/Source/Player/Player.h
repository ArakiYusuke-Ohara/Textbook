#pragma once
#include "../GameObject/Transform.h"
#include "../Quatrenion/Quatrenion.h"

class Player
{
public:
		Player();
		~Player();

		void Init();
		void Load();
		void Step();
		void Update();
		void Draw();
		void Fin();

private:
	Transform m_Transform;
	int m_ModelHandle;
};
