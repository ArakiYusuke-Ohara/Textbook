#pragma once

class Sky;

enum SkyType
{
	BLUE_SKY,
	SKY_TYPE_NONE = -1
};

// プレイヤーオブジェクト管理クラス
class SkyManager
{
public:
	SkyManager();	// コンストラクタ
	~SkyManager();	// デストラクタ

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new SkyManager; }
	static SkyManager* GetInstance() { return m_Instance; }
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
	// 生成されたSkyManager自身を格納する変数
	// SkyManagerはゲーム上に１つのみなのでstaticにしている
	static SkyManager* m_Instance;
	// 生成されたプレイヤーの参照
	Sky* m_Sky;
};