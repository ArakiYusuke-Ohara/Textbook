#pragma once
#include "Block.h"

#define BLOCK_MAX 4

class BlockManager
{
public:
	BlockManager();
	~BlockManager();

public:
	// マネージャーインスタンス管理
	static void CreateInstance() { if (!m_Instance) m_Instance = new BlockManager; }
	// マネージャーの関数が呼びたいときに使用する、マネージャー取得関数
	static BlockManager* GetInstance() { return m_Instance; }
	// 使わなくなったら削除する際の削除関数
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

private:
	// BlockManagerインスタンス
	static BlockManager* m_Instance;

	// ブロックを複数管理するため、配列で管理する


	// 大元のモデルハンドル

};
