#include "DxLib.h"
#include "CollisionSphere.h"
#include "../MyMath/MyMath.h"

// コンストラクタ
CollisionSphere::CollisionSphere()
{
	m_TargetPos = nullptr;
	m_LocalPos = VGet(0.0f, 0.0f, 0.0f);
	m_Radius = 0.0f;
}

// デストラクタ
CollisionSphere::~CollisionSphere()
{

}

void CollisionSphere::Draw()
{
	// デバッグ用の当たり判定の可視化
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
//	DrawSphere3D(centerPos, m_Radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), false);
}

bool CollisionSphere::CheckSphere(CollisionSphere* other)
{
	// 自身の中心座標
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	// 相手側の中心座標
	VECTOR otherCenterPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
	// 相手側の半径
	float otherRadius = other->GetRadius();

	// ２つの球の中心間の距離を計算する




	// 計算した距離が２つの球の半径の合計以下であれば当たっている



	return false;
}

