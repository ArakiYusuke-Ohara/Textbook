#include "Block.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionAABB.h"

void Block::Start()
{
	m_AABB = new CollisionAABB;
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));
}

StageObject* Block::Clone()
{
	Block* clone = new Block;

	*clone = *this;
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	return clone;
}

