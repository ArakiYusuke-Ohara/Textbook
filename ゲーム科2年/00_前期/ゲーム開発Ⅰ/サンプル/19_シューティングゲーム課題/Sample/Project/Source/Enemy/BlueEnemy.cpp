#include "BlueEnemy.h"
#include "../MyMath/MyMath.h"

#define JUMP_POW 0.1f
#define GRAVITY	 0.01f
#define JUMP_INTERVAL 60

BlueEnemy::BlueEnemy()
{
	m_JumpInterval = 0;
}

BlueEnemy::~BlueEnemy()
{
}

void BlueEnemy::Init()
{
}

void BlueEnemy::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/BlueEnemy/BlueEnemy.x");
}

void BlueEnemy::Start()
{
}

void BlueEnemy::Step()
{
	// 重力処理
	m_Move.y -= GRAVITY;

	// 一定時間ごとにジャンプ
	if(m_JumpInterval <= 0)
	{
		m_Move.y = JUMP_POW;
		m_JumpInterval = JUMP_INTERVAL;
	}
	else
	{
		m_JumpInterval--;
	}

	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	// 地面より下に行かないように
	// （練習用：本来は当たり判定でやるべき）
	if (m_Pos.y < 1.0f)
	{
		m_Pos.y = 1.0f;
		m_Move.y = 0.0f;
	}

}

// 呼ばれたオブジェクトの複製を作る関数
EnemyBase* BlueEnemy::Clone()
{
	// クローン用のオブジェクトを生成
	BlueEnemy* clone = new BlueEnemy;

	// 自身の中身をクローンにコピー
	*clone = *this;

	// 画像はDuplicateする必要がある
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	// 出来上がったクローンを返却
	return clone;
}
