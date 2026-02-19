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
	block->posY = block->startPosY + sin;

	// ˆÚ“®—Ê‚ðŒvŽZ‚µ‚Ä‚¨‚­
	block->moveX = block->posX - block->prevPosX;
	block->moveY = block->posY - block->prevPosY;
}

void ResolveMoveBlockX(Body* body, const BlockData* block)
{
	// ¶‚©‚ç‚ ‚½‚Á‚½‚©
	if ((body->prevPosX + body->width) <= block->prevPosX)
	{
		// ¶‚É‰Ÿ‚µo‚·
		body->posX -= (body->posX + body->width) - block->posX;
	}
	// ‰E‚©‚ç‚ ‚½‚Á‚½‚©
	else if (body->prevPosX >= (block->prevPosX + block->width))
	{
		// ‰E‚É‰Ÿ‚µo‚·
		body->posX += (block->posX + block->width) - body->posX;
	}

	// ˆÚ“®—Ê‚Í0‚É‚·‚é
	body->moveX = 0.0f;

}

void ResolveMoveBlockY(Body* body, const BlockData* block)
{
	// ã‚©‚ç‚ ‚½‚Á‚½‚©
	if ((body->prevPosY + body->height) <= block->prevPosY)
	{
		// ã‚É‰Ÿ‚µo‚·
		body->posY -= (body->posY + body->height) - block->posY;
		// ’…’n
		body->isAir = false;
		// ‘«Œ³ƒuƒƒbƒN‚Æ‚µ‚Ä“o˜^
		body->groundBlock = block;
		// ˆÚ“®—Ê‚Í0‚É‚·‚é
		body->moveY = 0.0f;
	}
	// ‰º‚©‚ç‚ ‚½‚Á‚½‚©
	else if (body->prevPosY >= (block->prevPosY + block->height))
	{
		// ‰º‚É‰Ÿ‚µo‚·
		body->posY += (block->posY + block->height) - body->posY;
		// ˆÚ“®—Ê‚ÍƒuƒƒbƒN‚É‡‚í‚¹‚é
		body->moveY = block->moveY;
	}
}
