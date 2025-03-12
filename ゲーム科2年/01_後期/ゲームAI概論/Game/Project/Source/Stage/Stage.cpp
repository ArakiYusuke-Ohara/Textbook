#include "DxLib.h"
#include "Stage.h"
#include "StageParameter.h"

Stage::Stage()
{
	m_Handle = 0;
}

Stage::~Stage()
{
}

void Stage::Load()
{
	m_Handle = LoadGraph("Data/Play/Stage/BG.png");
}

void Stage::Draw()
{
	DrawGraph(STAGE_POS_X, STAGE_POS_Y, m_Handle, TRUE);
}

void Stage::Fin()
{
	DeleteGraph(m_Handle);
}
