#pragma once

#include "DxLib.h"

class MyMath
{
public:
	static VECTOR VecCreate(VECTOR startPos, VECTOR endPos);
	static VECTOR VecAdd(VECTOR vecA, VECTOR vecB);
	static VECTOR VecScale(VECTOR vecA, float scale);
	static float VecDot(VECTOR vecA, VECTOR vecB);
	static float VecCross2D(VECTOR vecA, VECTOR vecB);
	static VECTOR VecCross3D(VECTOR vecA, VECTOR vecB);
	static float VecLong(VECTOR vec);
	static VECTOR VecNormalize(VECTOR vec);
};
