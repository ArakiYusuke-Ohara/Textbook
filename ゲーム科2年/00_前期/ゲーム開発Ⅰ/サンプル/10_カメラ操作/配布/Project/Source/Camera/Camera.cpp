#include "Camera.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"

#define CAMERA_NEAR_CLIP 0.01f
#define CAMERA_FAR_CLIP 1000.0f

#define PLAYER_DISTANCE -7.0f
#define ROTATION_SPEED 0.025f

#define X_ROTATION_MAX (DX_PI_F * 0.49f)

Camera::Camera()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Target = VGet(0.0f, 0.0f, 0.0f);
	m_UpVec = VGet(0.0f, 0.0f, 0.0f);
	m_TargetPlayer = nullptr;
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

	// アップベクトル設定
	m_UpVec = VGet(0.0f, 1.0f, 0.0f);

	// 追従するプレイヤー
	m_TargetPlayer = PlayerManager::GetInstance()->GetPlayer();
}

void Camera::Step()
{
	// キー入力処理
	if (Input::IsInputKey(KEY_A))
	{
		// 左回転
		m_Rot.y += ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_D))
	{
		// 右回転
		m_Rot.y -= ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_W))
	{
		// 手前回転
		m_Rot.x += ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_S))
	{
		// 奥回転
		m_Rot.x -= ROTATION_SPEED;
	}

	// X軸回転は頭上や足元を超えようとするとカメラ向きがひっくり返るため
	// 超えないように止める
	if (m_Rot.x >= X_ROTATION_MAX)
	{
		m_Rot.x = X_ROTATION_MAX;
	}
	else if (m_Rot.x <= -X_ROTATION_MAX)
	{
		m_Rot.x = -X_ROTATION_MAX;
	}
}

void Camera::Update()
{
	// プレイヤーの座標
	VECTOR playerPos = m_TargetPlayer->GetPos();

	// ① プレイヤーを原点に移動させる平行移動行列



	// ② プレイヤーの手前に移動する平行移動行列を用意


	// ③ カメラのピッチ行列


	// ④ カメラのヨー行列


	// ⑤ プレイヤーを元の位置に戻す平行移動行列


	// ⑥ ①～⑤の行列を逆順に合成





	// ⑦ プレイヤーの位置から行列変換を計算したものがカメラの座標となる


	// 注視点はプレイヤーの座標
	m_Target = playerPos;

	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void Camera::Draw()
{
	DrawFormatString(0, 60, GetColor(255, 255, 255), "カメラの座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
}

void Camera::Fin()
{

}
