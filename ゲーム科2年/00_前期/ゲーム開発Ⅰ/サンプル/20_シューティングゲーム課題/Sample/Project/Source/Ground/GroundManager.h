#pragma once

class Ground;

enum GroundType
{
	GRASS,
	GROUND_TYPE_NONE = -1
};

// プレイヤーオブジェクト管理クラス
class GroundManager
{
public:
	GroundManager();	// コンストラクタ
	~GroundManager();	// デストラクタ

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new GroundManager; }
	static GroundManager* GetInstance() { return m_Instance; }
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
	static GroundManager* m_Instance;
	Ground* m_Ground;
};