#pragma once

#include "DxLib.h"

class Stage 
{
public:
	Stage();
	~Stage();

	void Load();
	void Start();
	void Draw();
	void Fin();

	MV1_COLL_RESULT_POLY_DIM CheckCollisionSphere(VECTOR pos, float r);

private:
	int m_Handle;
	int m_CollisionHandle;
};