#include "BulletManager.h"
#include "StraightBullet.h"
#include "../Collision/CollisionParameter.h"
#include "../MyEffekseer/EffekseerParameter.h"

// データ群はエクセルにしたい
const BulletParameter BULLET_MASTER_DATA[]
{
	{"Data/Bullet/PlayerNormalBullet.x", BULLET_CATEGORY_STRAIGHT, 120, 1, COLLISION_TAG_PLAYER_BULLET, EFFEKSEER_PLAYER_NORMAL_SHOT_HIT, 0.9f, 0.1f},
	{"Data/Bullet/BeeBullet.x", BULLET_CATEGORY_STRAIGHT, 180, 1, COLLISION_TAG_ENEMY_BULLET, EFFEKSEER_PLAYER_NORMAL_SHOT_HIT, 0.3f, 0.2f},
	{"Data/Bullet/DiaBullet.x", BULLET_CATEGORY_STRAIGHT, 180, 1, COLLISION_TAG_ENEMY_BULLET, EFFEKSEER_PLAYER_NORMAL_SHOT_HIT, 0.6f, 0.2f},
};

BulletManager* BulletManager::m_Instance = nullptr;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::Init()
{
}

void BulletManager::Load()
{
	// クローン元のバレットをロード
	for (BulletBase* bullet : m_OriginalBullets)
	{
		bullet->Load();
	}
}

void BulletManager::Step()
{
	for (BulletBase* bullet : m_Bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Step();
		}
	}
}

void BulletManager::Update()
{
	for (BulletBase* bullet : m_Bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Update();
		}
	}
}

void BulletManager::Draw()
{
	for (BulletBase* bullet : m_Bullets)
	{
		if (bullet->IsActive())
		{
			bullet->Draw();
		}
	}

	// m_Bulletsの個数
	DrawFormatString(0, 100, GetColor(0, 0, 0), "m_Bulletsのサイズ：%d", m_Bullets.size());
}

void BulletManager::Fin()
{
	for (BulletBase* bullet : m_OriginalBullets)
	{
		delete bullet;
	}
	for (BulletBase* bullet : m_Bullets)
	{
		delete bullet;
	}

	m_OriginalBullets.clear();
	m_Bullets.clear();
}

void BulletManager::SetupBullet(int id)
{
	BulletBase* bullet = nullptr;
	BulletParameter param = BULLET_MASTER_DATA[id];

	switch (param.category)
	{
		case BULLET_CATEGORY_STRAIGHT: bullet = new StraightBullet; break;
	}

	bullet->Init(id);

	m_OriginalBullets.push_back(bullet);
}

void BulletManager::FireBullet(int id, VECTOR pos, VECTOR vec)
{
	// 未使用で同じIDのバレットを探す
	for (BulletBase* bullet : m_Bullets)
	{
		if (id == bullet->GetID() && !bullet->IsActive())
		{
			// バレットを再利用する
			bullet->Fire(pos, vec);
			return;
		}
	}

	// 再利用できなければ新規追加
	BulletBase* bullet = CreateBullet(id);
	bullet->Fire(pos, vec);
	
	// vectorに追加
	m_Bullets.push_back(bullet);
}

const BulletParameter* BulletManager::GetBulletParameter(int id)
{
	return &BULLET_MASTER_DATA[id];
}

BulletBase* BulletManager::CreateBullet(int id)
{
	for (BulletBase* bullet : m_OriginalBullets)
	{
		if (id == bullet->GetID())
		{
			return bullet->Clone();
		}
	}

	// 引数のバレットがセットアップされていない
	return nullptr;
}
