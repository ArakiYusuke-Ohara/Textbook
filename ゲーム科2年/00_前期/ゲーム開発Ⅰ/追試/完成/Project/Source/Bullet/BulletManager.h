#pragma once
#include "DxLib.h"
#include <vector>

class Bullet;

class BulletManager
{
public:
	BulletManager();
	~BulletManager() = default;

	// マネージャーインスタンス管理
	static void CreateInstance() { if (!m_Instance) m_Instance = new BulletManager; }
	// マネージャーの関数が呼びたいときに使用する、マネージャー取得関数
	static BulletManager* GetInstance() { return m_Instance; }
	// 使わなくなったら削除する際の削除関数
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画

	Bullet* FireBullet(VECTOR pos, VECTOR rot, float speed);

private:
	// BulletManagerインスタンス
	static BulletManager* m_Instance;
	// バレット配列
	std::vector<Bullet*> m_Bullets;
};
