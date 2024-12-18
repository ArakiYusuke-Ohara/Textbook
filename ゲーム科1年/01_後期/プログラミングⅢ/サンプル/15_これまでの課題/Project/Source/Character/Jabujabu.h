#pragma once

#include "Character.h"

class Jabujabu : public Character
{
public:
	Jabujabu();
	~Jabujabu();

public:
	void SetSwimSpeed(int speed) { m_SwimSpeed = speed; }
	void Swim();
	void Draw() override;

private:
	int m_SwimSpeed;
};
