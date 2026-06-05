#include "DxLib.h"
#include "CollisionSphere.h"
#include "../MyMath/MyMath.h"

// コンストラクタ
CollisionSphere::CollisionSphere()
{
	m_TargetPos = nullptr;
	m_LocalPos = VGet(0.0f, 0.0f, 0.0f);
	m_Radius = 0.0f;
	m_Active = false;
}

// デストラクタ
CollisionSphere::~CollisionSphere()
{

}

void CollisionSphere::Draw()
{
#ifdef _DEBUG
	if (!m_Active) return;

	// デバッグ用の当たり判定の可視化
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	DrawSphere3D(centerPos, m_Radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), false);
#endif
}

/// <summary>
/// 球の当たり判定
/// </summary>
/// <param name="other">判定対象の球</param>
/// <returns>当たったらtrue</returns>
bool CollisionSphere::CheckSphere(CollisionSphere* other)
{
	if (!m_Active) return false;

	// 自身の中心座標
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	// 自身の半径はm_Radius

	// 判定対象の中心座標
	VECTOR otherCenterPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
	// 判定対象の半径
	float otherRadius = other->GetRadius();

	// 課題１：２つの球の中心間の距離を計算する
	VECTOR vec = MyMath::VecCreate(centerPos, otherCenterPos);
	float distance = MyMath::VecLong(vec);

	// 課題２：計算した距離が２つの球の半径の合計以下であれば当たっている
	if (distance <= m_Radius + otherRadius)
	{
		return true;
	}

	return false;
}

