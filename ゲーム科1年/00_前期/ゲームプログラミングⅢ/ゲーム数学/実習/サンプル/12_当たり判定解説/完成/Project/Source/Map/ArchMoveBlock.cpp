#include "ArchMoveBlock.h"
#include "MapParameter.h"
#include "../Collision/CollisionParameter.h"

#define ARCH_WIDTH	(200.0f)
#define ARCH_HEIGHT	(100.0f)
#define ARCH_SPEED	(0.5f)

void StartArchMoveBlock(BlockData* block)
{
	block->body.move.x = ARCH_SPEED;
}

void StepArchMoveBlock(BlockData* block)
{
	// ’[‚Ü‚Ås‚Á‚½‚çŒü‚«‚ð”½“]
	if (block->body.pos.x > (block->startPos.x + ARCH_WIDTH) || block->body.pos.x < block->startPos.x)
	{
		block->body.move.x = -block->body.move.x;
	}
}

void UpdateArchMoveBlock(BlockData* block)
{
	// ‰E‚ÖˆÚ“®
	block->body.pos.x += block->body.move.x;

	// ‚í‚©‚è‚â‚·‚¢–¼‘O‚Ì•Ï”‚ÉŠi”[
	float x = block->startPos.x;
	float y = block->startPos.y;
	float h = block->startPos.x + (ARCH_WIDTH * 0.5f);
	float k = block->startPos.y - ARCH_HEIGHT;

	// ‡@ •ú•¨ü‚Ì•û’öŽ®‚É‰ŠúˆÊ’u‚Æ’¸“_À•W‚ð‘ã“ü‚µ‚Äa‚ð‹‚ß‚é
	float a = (y - k) / ((x - h) * (x - h));

	// ‡A Œ»Ý‚ÌXÀ•W‚Æ’¸“_À•W‚Æa‚ð‘ã“ü‚µ‚ÄYÀ•W‚ð‹‚ß‚é
	block->body.pos.y = a * ((block->body.pos.x - h) * (block->body.pos.x - h)) + k;

	// ˆÚ“®—Ê‚ðŒvŽZ‚µ‚Ä‚¨‚­
	block->body.move.x = block->body.pos.x - block->body.prevPos.x;
	block->body.move.y = block->body.pos.y - block->body.prevPos.y;
}
