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

		VECTOR GetGravity() const { return m_Gravity; }

private:
		VECTOR CalcMove();



private:
	Transform m_Transform;
	VECTOR m_Gravity;
	int m_ModelHandle;
};
