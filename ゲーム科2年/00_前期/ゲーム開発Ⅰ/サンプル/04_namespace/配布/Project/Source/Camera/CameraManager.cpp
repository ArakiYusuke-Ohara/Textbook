#include "CameraManager.h"

// 静的変数の初期化
CameraManager* CameraManager::m_Instance = nullptr;

// コンストラクタ
CameraManager::CameraManager()
{
	// 生成されていなければnullptr
	m_Camera = nullptr;
}

// デストラクタ
CameraManager::~CameraManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void CameraManager::CreateCamera()
{
	// プレイヤーが生成されていなければ生成する
	if (!m_Camera)
	{
		m_Camera = new Camera;
	}
}

void CameraManager::Init()
{
	if (m_Camera)
	{
		m_Camera->Init();
	}
}

void CameraManager::Load()
{
	if (m_Camera)
	{
		m_Camera->Load();
	}
}

void CameraManager::Start()
{
	if (m_Camera)
	{
		m_Camera->Start();
	}
}

void CameraManager::Step()
{
	if (m_Camera)
	{
		m_Camera->Step();
	}
}

void CameraManager::Update()
{
	if (m_Camera)
	{
		m_Camera->Update();
	}
}

void CameraManager::Draw()
{
	if (m_Camera)
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
}
