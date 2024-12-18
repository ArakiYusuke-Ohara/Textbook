#pragma once
#include "Food.h"

#define FARM_NAME_MAX 32

class Fruit : public Food
{
public:
	void SetFarmName(const char* name);
	char* GetFarmName() { return m_FarmName; }
	void CalcPrice() override;

private:
	char m_FarmName[FARM_NAME_MAX];
};

