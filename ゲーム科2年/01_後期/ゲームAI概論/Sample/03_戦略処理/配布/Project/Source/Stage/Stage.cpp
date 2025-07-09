#include "DxLib.h"
#include "Stage.h"
#include "StageParameter.h"
#include "../Block/BlockParameter.h"
#include "../Game/GameSetting.h"

#define STAGE_WIDTH (BLOCK_WIDTH * BLOCK_MAP_COL)
#define STAGE_HEIGHT (BLOCK_HEIGHT * BLOCK_MAP_ROW)
#define STAGE_POS_X (SCREEN_WIDTH * 0.5f - STAGE_WIDTH * 0.5f)
#define STAGE_POS_Y (SCREEN_HEIGHT * 0.5f - STAGE_HEIGHT * 0.5f)

Stage::Stage()
{
	m_Handle = 0;
}

Stage::~Stage()
{
}

void Stage::Load()
{
}

void Stage::Draw()
{
	DrawBox((int)STAGE_POS_X, (int)STAGE_POS_Y, (int)(STAGE_POS_X + STAGE_WIDTH), (int)(STAGE_POS_Y + STAGE_HEIGHT), GetColor(0, 125, 0), TRUE);
}

void Stage::Fin()
{
}

float Stage::GetPosX()
{
	return STAGE_POS_X;
}

float Stage::GetPosY()
{
	return STAGE_POS_Y;
}

