#include "MyMath.h"
#include <math.h>

// ベクトルを作る
// startPos	作るベクトルの始点
// endPos	作るベクトルの終点
VECTOR MyMath::VecCreate(VECTOR startPos, VECTOR endPos)
{
	VECTOR result;

	result.x = endPos.x - startPos.x;
	result.y = endPos.y - startPos.y;
	result.z = endPos.z - startPos.z;

	return result;
}

// ベクトルの足し算
// vecA ＋ vecB
VECTOR MyMath::VecAdd(VECTOR vecA, VECTOR vecB)
{
	VECTOR result;

	result.x = vecA.x + vecB.x;
	result.y = vecA.y + vecB.y;
	result.z = vecA.z + vecB.z;

	return result;
}

// ベクトルのスカラー倍
// vecA * scale
VECTOR MyMath::VecScale(VECTOR vecA, float scale)
{
	VECTOR result;

	result.x = vecA.x * scale;
	result.y = vecA.y * scale;
	result.z = vecA.z * scale;

	return result;
}

// ベクトルの内積
// vecA ・ vecB
float MyMath::VecDot(VECTOR vecA, VECTOR vecB)
{
	return vecA.x * vecB.x + vecA.y * vecB.y + vecA.z * vecB.z;
}

// ベクトルの外積(2D)
// vecA × vecB
float MyMath::VecCross2D(VECTOR vecA, VECTOR vecB)
{
	return vecA.x * vecB.y - vecA.y * vecB.x;
}

// ベクトルの外積(3D)
VECTOR MyMath::VecCross3D(VECTOR vecA, VECTOR vecB)
{
	VECTOR result;

	result.x = vecA.y * vecB.z - vecA.z * vecB.y;
	result.y = vecA.x * vecB.z - vecA.z * vecB.x;
	result.z = vecA.y * vecB.x - vecA.x * vecB.y;

	return result;
}

// ベクトルの長さを計算する
float MyMath::VecLong(VECTOR vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

// ベクトルを正規化する
VECTOR MyMath::VecNormalize(VECTOR vec)
{
	float vecLong = VecLong(vec);

	// 長さ0の場合は0ベクトルを返す
	if (vecLong == 0.0f) return VGet(0.0f, 0.0f, 0.0f);

	return VecScale(vec, 1.0f / vecLong);
}

// ZX平面上の前方ベクトル(長さ１)を取得する
VECTOR MyMath::VecForwardZX(float rotY)
{
	VECTOR result;

	// X成分はsin(Θ)
	result.x = sinf(rotY);
	// ZX平面なのでYは無視
	result.y = 0.0f;
	// Z成分はcos(Θ)
	result.z = cosf(rotY);

	return result;
}
