#include "Camera.h"

#define CAMERA_NEAR_CLIP 0.01f
#define CAMERA_FAR_CLIP 1000.0f

Camera::Camera()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Target = VGet(0.0f, 0.0f, 0.0f);
	m_UpVec = VGet(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
	Fin();
}

void Camera::Init()
{
}

void Camera::Load()
{
}

void Camera::Start()
{
	// ニア、ファークリップの設定
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	// 位置設定
	m_Pos = VGet(0.0f, 6.0f, -10.0f);
	// ターゲット設定
	m_Target = VGet(0.0f, 0.0f, 0.0f);
	// アップベクトル設定
	m_UpVec = VGet(0.0f, 1.0f, 0.0f);
}

void Camera::Step()
{
}

void Camera::Update()
{
	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void Camera::Draw()
{
}

void Camera::Fin()
{

}
