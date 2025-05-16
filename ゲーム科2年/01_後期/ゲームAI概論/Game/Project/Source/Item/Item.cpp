#include "Item.h"
#include "../Stage/StageManager.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Effect/SpriteAnimationManager.h"
#include "../Effect/SpriteAnimation.h"

#define ITEM_LIFE 480
#define BLINK_TIME 180

Item::Item()
{
	m_Active = false;
	m_Life = 0;
	m_Pos = {};
	m_Param = nullptr;
	m_CollisionAABB = nullptr;
	m_SpriteAnim = nullptr;
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
}

void Item::Step()
{
	if (!m_Active) return;

	// 寿命処理
	if (m_Life <= 0)
	{
		Destroy();
	}
	else
	{
		m_Life--;
	}

	// 位置追従
	m_SpriteAnim->SetPos(m_Pos);
}

void Item::Update()
{
	if (!m_Active) return;
}

void Item::Draw()
{
	if (!m_Active) return;

	// 寿命が切れそうなら点滅
	if (m_Life <= BLINK_TIME && m_Life % 4 == 0)
	{
		m_SpriteAnim->SetHide(!m_SpriteAnim->IsHide());
	}

#if 0
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

	// 寿命が切れそうなら点滅
	if (m_Life <= BLINK_TIME)
	{
		if (m_Life % 4 == 0)
		{
			DrawBox((int)m_Pos.x, (int)m_Pos.y, (int)(m_Pos.x + ITEM_WIDTH), (int)(m_Pos.y + ITEM_HEIGHT), color, TRUE);
		}
	}
	// 通常描画
	else
	{
		DrawBox((int)m_Pos.x, (int)m_Pos.y, (int)(m_Pos.x + ITEM_WIDTH), (int)(m_Pos.y + ITEM_HEIGHT), color, TRUE);
	}
#endif
}

void Item::Fin()
{

}

void Item::Spawn()
{
	m_Active = true;
	m_Life = ITEM_LIFE;
	m_SpriteAnim = SpriteAnimationManager::GetInstance()->Play(m_Param->animID, m_Pos, 5, true);
}

void Item::HitPlayer()
{
	Destroy();
}

Item* Item::Clone()
{
	Item* clone = new Item;
	*clone = *this;

	// 当たり判定設定は必要
	CollisionAABB* aabb = CollisionManager::GetInstance()->CreateAABB();
	aabb->SetSize(VGet(ITEM_WIDTH, ITEM_HEIGHT, 0.0f));
	aabb->SetTargetPos(&clone->m_Pos);
	clone->m_CollisionAABB = aabb;

	return clone;
}

void Item::Destroy()
{
	m_Active = false;
	m_SpriteAnim->SetActive(false);
}
