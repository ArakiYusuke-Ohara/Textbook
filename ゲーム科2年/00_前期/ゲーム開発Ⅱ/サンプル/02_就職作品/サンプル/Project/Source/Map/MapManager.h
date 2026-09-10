#pragma once
#include <vector>

struct MappingData;

// プレイヤーオブジェクト管理クラス
class MapManager
{
public:
	MapManager();	// コンストラクタ
	~MapManager();	// デストラクタ

	static void CreateInstance() { if (!m_Instance) m_Instance = new MapManager; }
	static MapManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	void Load(const char* fileName);	// ロード
	void Start();	// 開始
	void Draw();	// 描画
	void Fin();		// 終了

private:
	static MapManager* m_Instance;
	std::vector<MappingData> m_MappingData;
	std::vector<
};
