#include "Player.h"
#include "../MyMath/MyMath.h"
#include "../Camera/CameraManager.h"
#include "../Camera/Camera.h"

constexpr float MOVE_SPEED = 0.1f;

Player::Player()
{
	m_Transform = {};
	m_Gravity = {};
	m_ModelHandle = -1;
}

Player::~Player()
{
	Fin();
}

void Player::Init()
{
	m_Transform.pos = VGet(0.0f, 0.0f, 0.0f);
	m_Transform.rotation = MyQuaternion::QIdentity();
	m_Transform.scale = VGet(1.0f, 1.0f, 1.0f);

	m_Gravity = VGet(-1.0f, 0.0f, 0.0f);
}

void Player::Load()
{
	m_ModelHandle = MV1LoadModel("Data/Player/Player.x");
}

void Player::Step()
{
	// 移動ベクトル計算
	VECTOR move = CalcMove();

	// 座標更新
	m_Transform.pos = MyMath::VecAdd(m_Transform.pos, move);
}

void Player::Update()
{
	// スケール行列
	MATRIX scaleMat = MyMath::MatScale(m_Transform.scale);
	// 回転行列
	MATRIX rotMat = MyQuaternion::QToMatrix(m_Transform.rotation);
	// 平行移動行列
	MATRIX transMat = MyMath::MatTranslation(m_Transform.pos);

	// 行列を合成
	MATRIX worldMat = MyMath::MatMult(transMat, rotMat);
	worldMat = MyMath::MatMult(worldMat, scaleMat);
	worldMat = MyMath::MatTransposition(worldMat);

	// 描画行列設定
	MV1SetMatrix(m_ModelHandle, worldMat);
}

void Player::Draw()
{
	MV1DrawModel(m_ModelHandle);
}

void Player::Fin()
{
	MV1DeleteModel(m_ModelHandle);
}

VECTOR Player::CalcMove()
{
	// 上向きベクトル
	VECTOR worldUp = MyMath::VecScale(m_Gravity, -1.0f);

	// カメラの前方ベクトル
	Camera* camera = CameraManager::GetInstance()->GetCamera();
	VECTOR cameraForward = camera->GetForward();

	// worldUpを法線とした平面にカメラの前方ベクトルを投影する
	// これが前方移動ベクトルとなる
	VECTOR moveForward = MyMath::ProjectOnPlane(cameraForward, worldUp);
	moveForward = MyMath::VecNormalize(moveForward);

	// 外積で右向きベクトルを計算
	VECTOR moveRight = MyMath::VecCross3D(worldUp, moveForward);
	moveRight = MyMath::VecNormalize(moveRight);

	// 入力移動
	VECTOR move = {};
	if (CheckHitKey(KEY_INPUT_UP))
	{
		move = moveForward;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		move = MyMath::VecScale(moveForward, -1.0f);
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		move = MyMath::VecScale(moveRight, -1.0f);
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		move = moveRight;
	}

	// 移動速度設定
	return MyMath::VecScale(move, MOVE_SPEED);
}
