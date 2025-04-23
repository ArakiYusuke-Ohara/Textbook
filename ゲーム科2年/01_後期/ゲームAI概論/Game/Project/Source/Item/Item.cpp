#include "Item.h"
#include "../Stage/StageManager.h"

Item::Item()
{
	m_Active = false;
	m_Handle = 0;
	m_Pos = {};
	m_Param = nullptr;
}

Item::~Item()
{
	Fin();
}

void Item::Init()
{
}

void Item::Load()
{
	if (m_Param)
	{
		m_Handle = LoadGraph(m_Param->path);
	}
}

void Item::Step()
{
}

void Item::Update()
{
}

void Item::Draw()
{
	// ƒ[ƒ‹ƒhÀ•W‚É•ÏŠ·
	VECTOR pos = StageManager::GetInstance()->ConvertStagePosToWorldPos(m_Pos);
	DrawBox((int)pos.x, (int)pos.y, (int)(pos.x + ITEM_WIDTH), (int)(pos.y + ITEM_HEIGHT), GetColor(255, 255, 255), TRUE);
}

void Item::Fin()
{
	DeleteGraph(m_Handle);
}

Item* Item::Clone()
{
	Item* clone = new Item;
	*clone = *this;

	return clone;
}
