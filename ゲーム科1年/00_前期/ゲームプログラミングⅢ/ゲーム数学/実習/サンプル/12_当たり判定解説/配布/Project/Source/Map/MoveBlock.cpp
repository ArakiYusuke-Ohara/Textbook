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
	block->pos.y = block->startPos.y + sin;

	// ˆÚ“®—Ê‚ðŒvŽZ‚µ‚Ä‚¨‚­
	block->move.x = block->pos.x - block->prevPos.x;
	block->move.y = block->pos.y - block->prevPos.y;
}

void ResolveMoveBlockX(Body* body, const BlockData* block)
{
	// ¶‚©‚ç‚ ‚½‚Á‚½‚©
	if ((body->prevPos.x + body->width) <= block->prevPos.x)
	{
		// ¶‚É‰Ÿ‚µo‚·
		body->pos.x -= (body->pos.x + body->width) - block->pos.x;
	}
	// ‰E‚©‚ç‚ ‚½‚Á‚½‚©
	else if (body->prevPos.x >= (block->prevPos.x + block->width))
	{
		// ‰E‚É‰Ÿ‚µo‚·
		body->pos.x += (block->pos.x + block->width) - body->pos.x;
	}

	// ˆÚ“®—Ê‚Í0‚É‚·‚é
	body->move.x = 0.0f;

}

void ResolveMoveBlockY(Body* body, const BlockData* block)
{
	// ã‚©‚ç‚ ‚½‚Á‚½‚©
	if ((body->prevPos.y + body->height) <= block->prevPos.y)
	{
		// ã‚É‰Ÿ‚µo‚·
		body->pos.y -= (body->pos.y + body->height) - block->pos.y;
		// ’…’n
		body->isAir = false;
		// ‘«Œ³ƒuƒƒbƒN‚Æ‚µ‚Ä“o˜^
		body->groundBlock = block;
		// ˆÚ“®—Ê‚Í0‚É‚·‚é
		body->move.y = 0.0f;
	}
	// ‰º‚©‚ç‚ ‚½‚Á‚½‚©
	else if (body->prevPos.y >= (block->prevPos.y + block->height))
	{
		// ‰º‚É‰Ÿ‚µo‚·
		body->pos.y += (block->pos.y + block->height) - body->pos.y;
		// ˆÚ“®—Ê‚ÍƒuƒƒbƒN‚É‡‚í‚¹‚é
		body->move.y = block->move.y;
	}
}
