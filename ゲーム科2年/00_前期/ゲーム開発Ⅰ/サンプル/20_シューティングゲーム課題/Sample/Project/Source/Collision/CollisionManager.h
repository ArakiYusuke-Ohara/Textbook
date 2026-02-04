#pragma once

#include "CollisionParameter.h"
#include "CollisionBase.h"
#include <vector>

// Box.hをインクルードしなくて済むように前方定義
class CollisionBase;
class CollisionAABB;
class CollisionSphere;

#define COLLISION_MAX 16

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

public:
	// マネージャーインスタンス管理
	static void CreateInstance() { if (!m_Instance) m_Instance = new CollisionManager; }
	// マネージャーの関数が呼びたいときに使用する、マネージャー取得関数
	static CollisionManager* GetInstance() { return m_Instance; }
	// 使わなくなったら削除する際の削除関数
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void Draw();	// 描画
	void Fin();		// 終了

public:
	// 関数を呼ぶときに型指定するテンプレート
	CollisionAABB* CreateAABB();
	CollisionSphere* CreateSphere();

private:
	CollisionBase* CreateCollision(int id);

public:
	// 当たり判定のチェック
	void CheckCollision();

private:
	// CollisionManagerインスタンス
	static CollisionManager* m_Instance;
	// 当たり判定管理用配列
	std::vector<CollisionBase*> m_Collisions;
};
