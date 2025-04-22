#include "EnemyBee.h"
#include "../Bullet/BulletManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"
#include "../MyEffekseer/EffekseerParameter.h"

#define BEE_BULLET_ID 1
#define BEE_SHOT_NUM 3
#define BEE_MOVE_Z 0.25f

EnemyBee::EnemyBee()
{
	m_ShotCount = 0;
	m_ShotTimer = 0;
}

EnemyBee::~EnemyBee()
{
}

void EnemyBee::Init()
{
	BulletManager::GetInstance()->SetupBullet(BEE_BULLET_ID);
	m_DeadEffectID = EFFEKSEER_BEE_DEAD;
}

void EnemyBee::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/Bee/Bee.x");
}

void EnemyBee::Start()
{
	m_Move.z = BEE_MOVE_Z;
	m_Collision->SetActive(true);
	m_Collision->SetTargetPos(&m_Pos);
	m_Collision->SetRadius(m_Param->radius);
	m_Collision->SetTag(COLLISION_TAG_ENEMY);
	m_ShotTimer = 30;
}

void EnemyBee::Step()
{
	EnemyBase::Step();

	if (!m_Active) return;

	if (m_ShotTimer <= 0)
	{
		// BEE_SHOT_NUMの数だけ発射する
		if (m_ShotCount < BEE_SHOT_NUM)
		{
			if (m_Interval <= 0)
			{
				// プレイヤーに向けて発射
				VECTOR playerPos = PlayerManager::GetInstance()->GetPlayer()->GetPos();
				VECTOR bulletVec = MyMath::VecCreate(m_Pos, playerPos);
				BulletManager::GetInstance()->FireBullet(BEE_BULLET_ID, m_Pos, bulletVec);

				// インターバルをリセット
				m_Interval = m_Param->interval;

				// 発射数をカウント
				m_ShotCount++;
			}
			else
			{
				m_Interval--;
			}
		}
	}
	else
	{
		m_ShotTimer--;
	}

}

// 呼ばれたオブジェクトの複製を作る関数
EnemyBase* EnemyBee::Clone()
{
	// クローン用のオブジェクトを生成
	EnemyBee* clone = new EnemyBee;

	// 自身の中身をクローンにコピー
	*clone = *this;

	// 画像はDuplicateする必要がある
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	// くらい判定
	clone->m_Collision = CollisionManager::GetInstance()->CreateSphere();

	// 出来上がったクローンを返却
	return clone;
}
