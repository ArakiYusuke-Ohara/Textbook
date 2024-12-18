#pragma once

#include "Character.h"

class Tekuteku : public Character
{
public:
	Tekuteku();
	~Tekuteku();

public:
	void SetWalkSpeed(int speed) { m_WalkSpeed = speed; }
	void Walk();
	void Draw() override;

private:
	int m_WalkSpeed;
};
