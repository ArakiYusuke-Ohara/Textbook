#include "Block.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"

#define END_POS_Z -10.0f

// コンストラクタ
Block::Block()
{
	m_Active = false;
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_AABB = nullptr;
}

// デストラクタ
Block::~Block()
{
	Fin();
}

void Block::Load()
{
	m_Handle = LoadGraph("Data/Play/Stage/Block.png");
}

void Block::Start()
{
	m_Active = true;

	// 当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(40.0f, 40.0f, 0.0f));
}

void Block::Draw()
{
	DrawGraph((int)m_Pos.x, (int)m_Pos.y, m_Handle, TRUE);
}

void Block::Fin()
{
	DeleteGraph(m_Handle);
}

Block* Block::Clone()
{
	Block* clone = new Block;
	*clone = *this;

	clone->m_Handle = m_Handle;
	return clone;
}

