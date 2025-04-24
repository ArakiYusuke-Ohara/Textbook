#include "Item.h"
#include "../Stage/StageManager.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"

#define ITEM_LIFE 480
#define BLINK_TIME 180

Item::Item()
{
	m_Active = false;
	m_Life = 0;
	m_Handle = 0;
	m_Pos = {};
	m_Param = nullptr;
	m_CollisionAABB = nullptr;
}

Item::~Item()
{
	Fin();
}

void Item::Init()
{
	m_Life = ITEM_LIFE;
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
	if (!m_Active) return;

	// õ–½ˆ—
	if (m_Life <= 0)
	{
		m_Active = false;
	}
	else
	{
		m_Life--;
	}
}

void Item::Update()
{
	if (!m_Active) return;
}

void Item::Draw()
{
	if (!m_Active) return;

#ifdef _DEBUG
	int color = 0;
	switch (m_Param->id)
	{
	case ITEM_ID_PLAYER_SPEED_UP:
		color = GetColor(0, 0, 255);
		break;
	case ITEM_ID_BULLET_RAPID_UP:
		color = GetColor(0, 255, 0);
		break;
	case ITEM_ID_BULLET_SPEED_UP:
		color = GetColor(255, 0, 0);
		break;
	}

	// õ–½‚ªØ‚ê‚»‚¤‚È‚ç“_–Å
	if (m_Life <= BLINK_TIME)
	{
		if (m_Life % 4 == 0)
		{
			DrawBox((int)m_Pos.x, (int)m_Pos.y, (int)(m_Pos.x + ITEM_WIDTH), (int)(m_Pos.y + ITEM_HEIGHT), color, TRUE);
		}
	}
	// ’Êí•`‰æ
	else
	{
		DrawBox((int)m_Pos.x, (int)m_Pos.y, (int)(m_Pos.x + ITEM_WIDTH), (int)(m_Pos.y + ITEM_HEIGHT), color, TRUE);
	}
#endif
}

void Item::Fin()
{
	DeleteGraph(m_Handle);
}

void Item::Spawn()
{
	m_Active = true;
	m_Life = ITEM_LIFE;
}

void Item::HitPlayer()
{
	m_Active = false;
}

Item* Item::Clone()
{
	Item* clone = new Item;
	*clone = *this;

	// “–‚½‚è”»’èİ’è‚Í•K—v
	CollisionAABB* aabb = CollisionManager::GetInstance()->CreateAABB();
	aabb->SetSize(VGet(ITEM_WIDTH, ITEM_HEIGHT, 0.0f));
	aabb->SetTargetPos(&clone->m_Pos);
	clone->m_CollisionAABB = aabb;

	return clone;
}
