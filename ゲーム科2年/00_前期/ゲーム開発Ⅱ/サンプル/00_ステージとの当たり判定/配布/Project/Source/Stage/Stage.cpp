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
	// 描画するモデルをロード
	m_Handle = MV1LoadModel("Data/Stage/Stage.x");
	// 当たり判定用のモデルをロード

}

void Stage::Start()
{
	// 衝突情報を構築

}

void Stage::Draw()
{
	MV1DrawModel(m_Handle);
}

void Stage::Fin()
{
	// 構築した衝突情報を削除

	// 画像を削除
	MV1DeleteModel(m_Handle);
	// 当たり判定用のモデルも削除

}

MV1_COLL_RESULT_POLY_DIM Stage::CheckCollisionSphere(VECTOR pos, float r)
{
	return MV1_COLL_RESULT_POLY_DIM();
}
