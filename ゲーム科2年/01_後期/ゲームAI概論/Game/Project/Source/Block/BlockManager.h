#pragma once

#include "DxLib.h"
#include <vector>
#include <list>

class Block;

struct BlockParameter
{
	VECTOR pos;
};

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
	void Draw();	// 描画
	void Fin();		// 終了

public:
	Block* CreateBlock();
	std::vector<Block*> GetBlocks() { return m_Blocks; }

private:
	// BlockManagerインスタンス
	static BlockManager* m_Instance;

	// vectorのオブジェクトプールで管理してみる
	std::vector<Block*> m_Blocks;

	// クローン元のブロック
	Block* m_OriginalBlock;
};
