#pragma once

#include "DxLib.h"
#include "BulletParameter.h"
#include <vector>

class BulletBase;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

public:
	// マネージャーインスタンス管理
	static void CreateInstance() { if (!m_Instance) m_Instance = new BulletManager; }
	// マネージャーの関数が呼びたいときに使用する、マネージャー取得関数
	static BulletManager* GetInstance() { return m_Instance; }
	// 使わなくなったら削除する際の削除関数
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void Load();
	void Step();
	void Draw();
	void Fin();

public:
	std::vector<BulletBase*> GetBullets() const { return m_Bullets; }

	void SetupBullet(int id);
	void FireBullet(int id, VECTOR pos, VECTOR vec);
	const BulletParameter* GetBulletParameter(int id);

private:
	BulletBase* CreateBullet(int id);

private:
	static BulletManager* m_Instance;

	// 使用するバレットのクローン元
	std::vector<BulletBase*> m_OriginalBullets;

	// vectorのオブジェクトプールで管理してみる
	std::vector<BulletBase*> m_Bullets;
};


