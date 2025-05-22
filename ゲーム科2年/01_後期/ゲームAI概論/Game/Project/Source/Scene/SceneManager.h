#pragma once
#include "SceneBase.h"
#include "SceneParameter.h"
#include <vector>


class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new SceneManager; }
	static SceneManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance)delete m_Instance; m_Instance = nullptr; }

public:
	void Init();
	void Update();
	void Fin();

	void ChangeScene(SceneType type, float fadeOutSpeed = 0.0f);
	void AddScene(SceneType type);


// 以下の関数は外部から呼ぶことはないのでprivate
private:
	void InitScene();
	void LoadScene();
	void StartScene();
	void LoopScene();
	void FinScene();
	void FadeWait();

	SceneBase* CreateScene(SceneType type);
	void ClearScene();

private:
	static SceneManager* m_Instance;

	// 現在動いているシーン
	std::vector<SceneBase*> m_Scenes;

	// 現在の状態
	SceneState m_State;

	// 次に遷移するシーン
	SceneType m_NextScene;

	// 状態ごとの関数を呼ぶ関数ポインタ配列
	void (SceneManager::* m_StateFunc[SCENE_STATE_MAX])(void);

	// フェードアウトの速度
	float m_FadeOutSpeed;
};
