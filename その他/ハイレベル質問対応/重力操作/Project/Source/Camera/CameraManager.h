#pragma once
#include "../Singleton/Singleton.h"

class Camera;

class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager() = default;
	~CameraManager() = default;

	void Step();
	void Update();

	Camera* GetCamera() const { return m_Camera; }
	Camera* CreateCamera();

private:
	Camera* m_Camera;
};
