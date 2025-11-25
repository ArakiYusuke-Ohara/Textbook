#include "Camera.h"
#include "../MyMath/MyMath.h"
#include "../Player/Player.h"

#define CAMERA_NEAR_CLIP 0.01f
#define CAMERA_FAR_CLIP 1000.0f

Camera::Camera()
{
	m_Pos = {};
	m_Target = {};
	m_UpVec = {};
}

void Camera::Init()
{
	// カメラのニアクリップとファークリップを設定
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	m_Pos = VGet(0.0f, 7.0f, -10.0f);
	m_Target = VGet(0.0f, 3.0f, 0.0f);
	m_UpVec = VGet(0.0f, 1.0f, 0.0f);
}

void Camera::Step()
{
	if (m_FollowPlayer)
	{
		VECTOR playerGravity = m_FollowPlayer->GetGravity();
		m_UpVec = MyMath::VecScale(playerGravity, -1.0f);
	}
}

void Camera::Update()
{
	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

VECTOR Camera::GetForward()
{
	VECTOR forward = MyMath::VecCreate(m_Pos, m_Target);
	return MyMath::VecNormalize(forward);
}


