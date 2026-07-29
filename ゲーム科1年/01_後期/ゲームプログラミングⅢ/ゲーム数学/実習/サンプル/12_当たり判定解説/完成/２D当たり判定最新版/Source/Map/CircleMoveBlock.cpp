#include "MoveBlock.h"
#include "MapParameter.h"
#include "../Collision/CollisionParameter.h"
#include <math.h>

#define MOVE_SPEED (0.02f)
#define RADIUS (100.0f)

void StepCircleMoveBlock(BlockData* block)
{
	// ‡@ ŽOŠpŠÖ”—p‚ÌŠp“x‚ð‰ÁŽZ‚·‚é
	block->sin += MOVE_SPEED;
	block->cos += MOVE_SPEED;

	// ‡A Šp“x‚Í0`2ƒÎ‚Ì”ÍˆÍ‚ÉŽû‚ß‚é
	if (block->sin > DX_TWO_PI_F)
	{
		block->sin -= DX_TWO_PI_F;
	}
	if (block->cos > DX_TWO_PI_F)
	{
		block->cos -= DX_TWO_PI_F;
	}
}

void UpdateCircleMoveBlock(BlockData* block)
{
	// ‡B ‰~ˆÚ“®Žž‚ÌXˆÚ“®’l‚Í ”¼Œa * cosƒÆ
	block->body.pos.x = block->startPos.x + RADIUS * cosf(block->cos);

	// ‡C ‰~ˆÚ“®Žž‚ÌYˆÚ“®’l‚Í ”¼Œa * sinƒÆ
	block->body.pos.y = block->startPos.y + RADIUS * sinf(block->sin);

	// ˆÚ“®—Ê‚ðŒvŽZ‚µ‚Ä‚¨‚­
	block->body.move.x = block->body.pos.x - block->body.prevPos.x;
	block->body.move.y = block->body.pos.y - block->body.prevPos.y;
}

