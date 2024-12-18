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

void Block::Init()
{

}

void Block::Load()
{
	m_Handle = MV1LoadModel("Data/Block/Block.x");
}

void Block::Start()
{
	m_Active = true;

	// 当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
	m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));
}

void Block::Step()
{
}

void Block::Update()
{
	// プレイヤーのZ座標分だけ手前に描画する
	VECTOR playerPos = PlayerManager::GetInstance()->GetPlayer()->GetPos();
	VECTOR pos = m_Pos;
	pos.z -= playerPos.z;
	MV1SetPosition(m_Handle, pos);

	// 一定距離、プレイヤーの背後に行ったら非アクティブ
	if (pos.z <= END_POS_Z)
	{
		m_Active = false;
	}
}

void Block::Draw()
{
	MV1DrawModel(m_Handle);
}

void Block::Fin()
{
	MV1DeleteModel(m_Handle);
}

Block* Block::Clone()
{
	Block* clone = new Block;
	*clone = *this;

	clone->m_Handle = MV1DuplicateModel(m_Handle);
	return clone;
}

