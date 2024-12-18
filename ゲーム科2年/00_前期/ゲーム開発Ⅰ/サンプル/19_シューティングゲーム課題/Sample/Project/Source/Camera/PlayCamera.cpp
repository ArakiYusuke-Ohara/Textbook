#include "PlayCamera.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"

#define CAMERA_NEAR_CLIP 0.01f
#define CAMERA_FAR_CLIP 3000.0f

#define PLAYER_DISTANCE VGet(0.0f, 2.0f, -7.0f)
#define ROTATION_SPEED 0.025f

#define X_ROTATION_MAX (DX_PI_F * 0.49f)

// 基底クラスのコンストラクタ呼ぶ際は追加で書く
PlayCamera::PlayCamera() : CameraBase()
{
}

PlayCamera::~PlayCamera()
{
	Fin();
}

void PlayCamera::Init()
{
}

void PlayCamera::Load()
{
}

void PlayCamera::Start()
{
	// ニア、ファークリップの設定
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	// 初期位置
	m_Pos = VGet(0.0f, 34.0f, -10.0f);

	// アップベクトル設定
	m_UpVec = VGet(0.0f, 1.0f, 0.0f);

	// 注視点の設定
	m_Target = VGet(0.0f, 32.0f, 0.0f);
}

void PlayCamera::Step()
{
	VECTOR playerPos = PlayerManager::GetInstance()->GetPlayer()->GetPos();
	playerPos = PlayerManager::GetInstance()->ConvertPlayerLocalPos(playerPos);

	m_Pos = MyMath::VecAdd(playerPos, PLAYER_DISTANCE);
	m_Target = playerPos;
}

void PlayCamera::Update()
{
	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void PlayCamera::Draw()
{
	DrawFormatString(0, 60, GetColor(0, 0, 0), "カメラの座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
	DrawFormatString(0, 80, GetColor(0, 0, 0), "カメラの注視点[%f, %f, %f]", m_Target.x, m_Target.y, m_Target.z);
}

void PlayCamera::Fin()
{

}
