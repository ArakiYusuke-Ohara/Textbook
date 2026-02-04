#pragma once

#include "DxLib.h"

namespace MyMath
{
	VECTOR VecCreate(VECTOR startPos, VECTOR endPos);
	VECTOR VecAdd(VECTOR vecA, VECTOR vecB);
	VECTOR VecScale(VECTOR vecA, float scale);
	float VecDot(VECTOR vecA, VECTOR vecB);
	float VecCross2D(VECTOR vecA, VECTOR vecB);
	VECTOR VecCross3D(VECTOR vecA, VECTOR vecB);
	float VecLong(VECTOR vec);
	VECTOR VecNormalize(VECTOR vec);
};
