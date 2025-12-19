#include "GameApp.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../Network/ClientAPI.h"

GameApp::GameApp()
: m_ClientAPI(nullptr)
{
}

GameApp::~GameApp()
{
	EndNetwork();
	Input::Fin();
	SceneManager::DeleteInstance();
}

void GameApp::Init()
{
	Input::Init();

	SceneManager::CreateInstance();
	SceneManager::GetInstance()->Init();
}

void GameApp::Exec()
{
	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		Sleep(1);

		// 画面をクリア
		ClearDrawScreen();

		// 入力更新
		Input::Step();

		// シーン更新
		SceneManager::GetInstance()->Step();

		// ネットワーク更新
		if (m_ClientAPI)
		{
			m_ClientAPI->Step();
			m_ClientAPI->Draw();
		}

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 画面フリップ
		ScreenFlip();
	}
}

void GameApp::StartNetwork()
{
	if(!m_ClientAPI)
	{
		m_ClientAPI = MakeUnique<ClientAPI>();
		m_ClientAPI->Connect();
	}
}

void GameApp::EndNetwork()
{
	if (m_ClientAPI)
	{
		m_ClientAPI.reset();
	}
}

bool GameApp::IsConnected() const
{
	if (m_ClientAPI && m_ClientAPI->IsConnected()) return true;

	return false;
}
