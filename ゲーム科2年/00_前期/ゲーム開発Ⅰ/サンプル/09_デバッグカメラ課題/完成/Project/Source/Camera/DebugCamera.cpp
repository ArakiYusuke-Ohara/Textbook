#include "DebugCamera.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"

#define CAMERA_NEAR_CLIP 0.01f
#define CAMERA_FAR_CLIP 1000.0f

#define MOVE_SPEED (0.05f)

DebugCamera::DebugCamera()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Target = VGet(0.0f, 0.0f, 0.0f);
	m_UpVec = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
}

DebugCamera::~DebugCamera()
{
	Fin();
}

void DebugCamera::Init()
{
}

void DebugCamera::Load()
{
}

void DebugCamera::Start()
{
	// ニア、ファークリップの設定
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	// アップベクトル設定
	m_UpVec = VGet(0.0f, 1.0f, 0.0f);
}

void DebugCamera::Step()
{
	// 移動量をリセット
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	// キー入力処理
	if (Input::IsInputKey(Input::KEY_UP))
	{
		m_Move.y = MOVE_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_LEFT))
	{
		m_Move.x = -MOVE_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_DOWN))
	{
		m_Move.y = -MOVE_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_RIGHT))
	{
		m_Move.x = MOVE_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_Z))
	{
		m_Move.z = MOVE_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_X))
	{
		m_Move.z = -MOVE_SPEED;
	}

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
	m_Target = MyMath::VecAdd(m_Target, m_Move);
}

void DebugCamera::Update()
{
	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void DebugCamera::Draw()
{
	DrawSphere3D(m_Target, 0.25f, 8, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "デバッグカメラの座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
}

void DebugCamera::Fin()
{

}
