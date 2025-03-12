#pragma once

class AIStrategyBase
{
public:
	AIStrategyBase() {}
	~AIStrategyBase() {}

public:
	virtual void Step();
	virtual void Draw();
	virtual void Fin();
};
