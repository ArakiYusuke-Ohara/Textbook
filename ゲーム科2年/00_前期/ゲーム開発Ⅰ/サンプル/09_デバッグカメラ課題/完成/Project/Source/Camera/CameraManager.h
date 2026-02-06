#pragma once

class Camera;
class DebugCamera;

// プレイヤーオブジェクト管理クラス
class CameraManager
{
public:
	CameraManager();	// コンストラクタ
	~CameraManager();	// デストラクタ

public:
	// カメラマネージャーを生成する
	// マネージャークラスはゲーム上に１つのみとするので
	// ２回目以降はnewが通らないようになっている
	// （シングルトン）
	static void CreateInstance() { if (!m_Instance) m_Instance = new CameraManager; }
	// マネージャーの関数が呼びたいときに使用する、マネージャー取得関数
	static CameraManager* GetInstance() { return m_Instance; }
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

public:
	// カメラを生成する
	void CreateCamera();
	// デバッグカメラを生成する
	void CreateDebugCamera();

	// 管理中のカメラを取得する
	Camera* GetCamera() { return m_Camera; }

	// デバッグカメラモードに切り替える
	void ChangeDebugCameraMode();
	// デバッグカメラモードを解除する
	void ReleaseDebugCameraMode();
	// デバッグカメラモードかどうか
	bool IsDebugCameraMode() { return m_IsDebugCamera; }

private:
	// 生成されたCameraManager自身を格納する変数
	// マネージャークラスはゲーム上に１つのみなのでstaticにしている
	static CameraManager* m_Instance;
	// 生成されたカメラの参照
	Camera* m_Camera;
	// 生成されたデバッグカメラの参照
	DebugCamera* m_DebugCamera;

	// デバッグカメラ起動中かどうか
	bool m_IsDebugCamera;
};
