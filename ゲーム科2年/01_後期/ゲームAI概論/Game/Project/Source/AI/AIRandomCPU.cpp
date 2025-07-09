#include "AIRandomCPU.h"
#include "AIParameter.h"
#include "../MyRandom/MyRandom.h"

#define STRATEGY_TIME 180

AIRandomCPU::AIRandomCPU()
{
}

// この関数にCPUのとる行動を決定する処理を書く
int AIRandomCPU::ThinkStrategy()
{
	// ランダムで追いかけるか離れるか
	if (MyRandom::GetRandom() % 2 == 0)
	{
		return CPU_STRATEGY_CHASE_TARGET;
	}

	return CPU_STRATEGY_AWAY;
}

void AIRandomCPU::Draw()
{
}
