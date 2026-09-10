#include "RedEnemy.h"

#define ROTATION_SPEED 0.1f

RedEnemy::RedEnemy()
{
}

RedEnemy::~RedEnemy()
{
}

void RedEnemy::Init()
{
}

void RedEnemy::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/RedEnemy/RedEnemy.x");
}

void RedEnemy::Start()
{
}

void RedEnemy::Step()
{
	// 赤エネミーはその場で回転
	m_Rot.y += ROTATION_SPEED;
}

// 呼ばれたオブジェクトの複製を作る関数
EnemyBase* RedEnemy::Clone()
{
	// クローン用のオブジェクトを生成
	RedEnemy* clone = new RedEnemy;

	// 自身の中身をクローンにコピー
	*clone = *this;

	// 画像はDuplicateする必要がある
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	// 出来上がったクローンを返却
	return clone;
}
