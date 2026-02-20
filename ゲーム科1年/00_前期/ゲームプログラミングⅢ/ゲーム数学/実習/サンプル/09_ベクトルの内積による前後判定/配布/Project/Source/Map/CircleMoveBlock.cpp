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
	block->pos.x = block->startPos.x + RADIUS * cosf(block->cos);

	// ‡C ‰~ˆÚ“®Žž‚ÌYˆÚ“®’l‚Í ”¼Œa * sinƒÆ
	block->pos.y = block->startPos.y + RADIUS * sinf(block->sin);

	// ˆÚ“®—Ê‚ðŒvŽZ‚µ‚Ä‚¨‚­
	block->move.x = block->pos.x - block->prevPos.x;
	block->move.y = block->pos.y - block->prevPos.y;
}

void ResolveCircleMoveBlockX(Body* body, const BlockData* block)
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

void ResolveCircleMoveBlockY(Body* body, const BlockData* block)
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
