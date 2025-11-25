#include "CameraManager.h"
#include "Camera.h"

void CameraManager::Step()
{
}

void CameraManager::Update()
{
}

Camera* CameraManager::CreateCamera()
{
	if (!m_Camera)
	{
		m_Camera = new Camera();
	}

	return m_Camera;
}
