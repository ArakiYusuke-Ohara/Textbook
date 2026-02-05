#include "CameraManager.h"
#include "Camera.h"
#include "DebugCamera.h"
#include "../Input/Input.h"

// 静的変数の初期化
CameraManager* CameraManager::m_Instance = nullptr;

// コンストラクタ
CameraManager::CameraManager()
{
	// 生成されていなければnullptr
	m_Camera = nullptr;

	m_IsDebugCamera = false;
}

// デストラクタ
CameraManager::~CameraManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void CameraManager::CreateCamera()
{
	// カメラが生成されていなければ生成する
	if (!m_Camera)
	{
		m_Camera = new Camera;
	}
}

void CameraManager::CreateDebugCamera()
{
	// デバッグカメラが生成されていなければ生成する
	if (!m_DebugCamera)
	{
		m_DebugCamera = new DebugCamera;
	}
}

// デバッグカメラモードに切り替える
void CameraManager::ChangeDebugCameraMode()
{
	// デバッグカメラを生成しているときのみ処理する
	if (m_DebugCamera)
	{
		// デバッグカメラモードをONにする
		m_IsDebugCamera = true;

		// 今のカメラの位置にデバッグカメラを持っていく
		m_DebugCamera->SetPos(m_Camera->GetPos());
		m_DebugCamera->SetTarget(m_Camera->GetTarget());
	}
}

// デバッグカメラモードを解除する
void CameraManager::ReleaseDebugCameraMode()
{
	// デバッグカメラを生成しているときのみ処理する
	if (m_DebugCamera)
	{
		// デバッグカメラモードをOFFにする
		m_IsDebugCamera = false;
	}
}

void CameraManager::Init()
{
	if (m_Camera)
	{
		m_Camera->Init();
	}
	if (m_DebugCamera)
	{
		m_DebugCamera->Init();
	}
}

void CameraManager::Load()
{
	if (m_Camera)
	{
		m_Camera->Load();
	}
	if (m_DebugCamera)
	{
		m_DebugCamera->Load();
	}
}

void CameraManager::Start()
{
	if (m_Camera)
	{
		m_Camera->Start();
	}
	if (m_DebugCamera)
	{
		m_DebugCamera->Start();
	}
}

void CameraManager::Step()
{
	// デバッグカメラモード切り替え
	if (Input::IsTriggerKey(Input::KEY_1))
	{
		// デバッグカメラON/OFF切り替え
		if (m_IsDebugCamera)
		{
			// デバッグカメラ解除
			ReleaseDebugCameraMode();
		}
		else
		{
			// デバッグカメラON
			ChangeDebugCameraMode();
		}
	}

	if (m_DebugCamera && m_IsDebugCamera)
	{
		m_DebugCamera->Step();
	}
	else if (m_Camera)
	{
		m_Camera->Step();
	}

}

void CameraManager::Update()
{
	if (m_DebugCamera && m_IsDebugCamera)
	{
		m_DebugCamera->Update();
	}
	else if (m_Camera)
	{
		m_Camera->Update();
	}
}

void CameraManager::Draw()
{
	if (m_DebugCamera && m_IsDebugCamera)
	{
		m_DebugCamera->Draw();
	}
	else if (m_Camera)
	{
		m_Camera->Draw();
	}
}

void CameraManager::Fin()
{
	if (m_Camera)
	{
		m_Camera->Fin();
	}
	if (m_DebugCamera)
	{
		m_DebugCamera->Fin();
	}
}
