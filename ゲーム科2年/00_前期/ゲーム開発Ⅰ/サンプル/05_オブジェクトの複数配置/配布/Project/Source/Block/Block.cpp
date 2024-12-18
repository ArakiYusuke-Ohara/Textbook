#include "Block.h"

// コンストラクタ
Block::Block()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
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

}

void Block::Start()
{
}

void Block::Step()
{
}

void Block::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
}

void Block::Draw()
{
	MV1DrawModel(m_Handle);
}

void Block::Fin()
{
	MV1DeleteModel(m_Handle);
}

