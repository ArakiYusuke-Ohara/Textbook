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

void Block::Load(int handle)
{
	// Boxは複数使用するのでMV1LoadModelは使わない。
	// MV1DuplicateModelはモデルを複製する関数で、
	// Loadと違いファイルオープン～解析を省略することができる。
	m_Handle = MV1DuplicateModel(handle);
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

