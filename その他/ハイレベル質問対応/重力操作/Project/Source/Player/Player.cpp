#include "Player.h"
#include "../MyMath/MyMath.h"

Player::Player()
{
	m_Transform = {};
	m_ModelHandle = -1;
}

Player::~Player()
{
	Fin();
}

void Player::Init()
{
	m_Transform.position_3D = VGet(0.0f, 0.0f, 0.0f);
	m_Transform.rotation = MyQuaternion::QIdentity();
	m_Transform.scale = VGet(1.0f, 1.0f, 1.0f);
}

void Player::Load()
{
	m_ModelHandle = MV1LoadModel("Data/Player/Player.x");
}

void Player::Step()
{
	VECTOR move = {};
	if (CheckHitKey(KEY_INPUT_UP))
	{
		move = cameraForward;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		move = MyMath::VecScale(cameraForward, -1.0f);
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		move = MyMath::VecScale(cameraRight, -1.0f);
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		move = cameraRight;
	}

	move.y = 0.0f;
	move = MyMath::VecNormalize(move);
	move = MyMath::VecScale(move, 0.1f);

	m_Transform.position_3D = MyMath::VecAdd(m_Transform.position_3D, move);

}

void Player::Update()
{
	// スケール行列
	MATRIX scaleMat = MyMath::MatScale(m_Transform.scale);
	// 回転行列
	MATRIX rotMat = MyQuaternion::QToMatrix(m_Transform.rotation);
	// 平行移動行列
	MATRIX transMat = MyMath::MatTranslation(m_Transform.position_3D);

	// 行列を合成
	MATRIX worldMat = MyMath::MatMult(transMat, rotMat);
	worldMat = MyMath::MatMult(worldMat, scaleMat);
	worldMat = MyMath::MatTransposition(worldMat);

	MV1SetMatrix(m_ModelHandle, worldMat);

	// 3Dモデルを描画する
	MV1DrawModel(m_ModelHandle);
}

void Player::Draw()
{
}

void Player::Fin()
{
}
