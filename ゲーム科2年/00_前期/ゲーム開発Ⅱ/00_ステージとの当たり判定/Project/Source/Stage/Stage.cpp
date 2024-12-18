#include "Stage.h"

Stage::Stage()
{
	m_Handle = 0;
	m_CollisionHandle = 0;
	m_CollisionResult = {};
}

Stage::~Stage()
{
	Fin();
}

void Stage::Load()
{
	m_Handle = MV1LoadModel("Data/Stage/Stage.x");
	m_CollisionHandle = MV1LoadModel("Data/Stage/StageCollision.x");
}

void Stage::Start()
{
	// 衝突情報を構築
	MV1SetupCollInfo(m_CollisionHandle);
}

void Stage::Draw()
{
	MV1DrawModel(m_Handle);
}

void Stage::Fin()
{
	// 構築した衝突情報を削除
	MV1TerminateCollInfo(m_CollisionHandle);
	// 画像を削除
	MV1DeleteModel(m_Handle);
}

bool Stage::CheckCollisionSphere(VECTOR pos, float r)
{
	// ステージと球の当たり判定
	m_CollisionResult = MV1CollCheck_Sphere(m_CollisionHandle, -1, pos, r);

	// HitNumが0なら当たっていない
	return m_CollisionResult.HitNum != 0;
}
