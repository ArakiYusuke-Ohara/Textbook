#include "MoveBlock.h"
#include "MapParameter.h"
#include "../Collision/CollisionParameter.h"
#include <math.h>

#define MOVE_SPEED (0.02f)
#define MOVE_RANGE (100.0f)

void StepMoveBlock(BlockData* block)
{
	// ‡@ Sin”g—p‚ÌŠp“x‚ð‰ÁŽZ‚·‚é
	block->sin += MOVE_SPEED;

	// ‡A Šp“x‚Í0`2ƒÎ‚Ì”ÍˆÍ‚ÉŽû‚ß‚é
	if (block->sin > DX_TWO_PI_F)
	{
		block->sin -= DX_TWO_PI_F;
	}
}

void UpdateMoveBlock(BlockData* block)
{
	// ‡B sinfŠÖ”‚ÉŠp“x‚ð“n‚·‚ªA‚»‚Ì‚Ü‚Ü‚¾‚Æ’l‚ª¬‚³‚·‚¬‚é‚Ì‚Å
	//    MOVE_RANGE‚ÅŠ|‚¯ŽZ‚µ‚ÄˆÚ“®•‚Æ‚·‚é
	float sin = sinf(block->sin) * MOVE_RANGE;

	// ‡C Å‰‚É”z’u‚³‚ê‚½ˆÊ’u‚©‚çsin‚¾‚¯—£‚ê‚½•ª‚ªYÀ•W‚Æ‚È‚é
	block->body.pos.y = block->startPos.y + sin;

	// ˆÚ“®—Ê‚ðŒvŽZ‚µ‚Ä‚¨‚­
	block->body.move.x = block->body.pos.x - block->body.prevPos.x;
	block->body.move.y = block->body.pos.y - block->body.prevPos.y;
}
