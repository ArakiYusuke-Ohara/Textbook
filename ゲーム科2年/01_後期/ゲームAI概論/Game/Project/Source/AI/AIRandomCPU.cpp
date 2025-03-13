#include "AIRandomCPU.h"
#include "AIParameter.h"
#include "../MyRandom/MyRandom.h"

#define STRATEGY_TIME 180

AIRandomCPU::AIRandomCPU()
{
}

// ‚±‚ÌŠÖ”‚ÉCPU‚Ì‚Æ‚és“®‚ğŒˆ’è‚·‚éˆ—‚ğ‘‚­
int AIRandomCPU::ThinkStrategy()
{
	// ƒ‰ƒ“ƒ_ƒ€‚Å’Ç‚¢‚©‚¯‚é‚©—£‚ê‚é‚©
	if (MyRandom::GetRandom() % 2 == 0)
	{
		return CPU_STRATEGY_CHASE;
	}

	return CPU_STRATEGY_AWAY;
}

void AIRandomCPU::Draw()
{
}
