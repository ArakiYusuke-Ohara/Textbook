#include "MyMath.h"
#include <math.h>

/// <summary>
/// ベクトル生成
/// </summary>
/// <param name="start">生成するベクトルの始点座標</param>
/// <param name="end">生成するベクトルの終点座標</param>
/// <returns>生成されたベクトル</returns>
VECTOR VecCreate(VECTOR start, VECTOR end)
{
	VECTOR result = {};

	result.x = end.x - start.x;
	result.y = end.y - start.y;
	result.z = end.z - start.z;

	return result;
}

/// <summary>
/// ベクトルの足し算
/// </summary>
/// <param name="vecA">足し算するベクトルA</param>
/// <param name="vecB">足し算するベクトルB</param>
/// <returns>計算結果</returns>
VECTOR VecAdd(VECTOR vecA, VECTOR vecB)
{
	VECTOR result = {};

	result.x = vecA.x + vecB.x;
	result.y = vecA.y + vecB.y;
	result.z = vecA.z + vecB.z;

	return result;
}

/// <summary>
/// ベクトルのスカラー倍
/// </summary>
/// <param name="vec">掛け算するベクトル</param>
/// <param name="scale">掛け算するスカラー</param>
/// <returns>計算結果</returns>
VECTOR VecScale(VECTOR vec, float scale)
{
	VECTOR result = {};

	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}

/// <summary>
/// ベクトルの長さを計算する
/// </summary>
/// <param name="vec">長さを計るベクトル</param>
/// <returns>ベクトルの長さ</returns>
float VecLong(VECTOR vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

/// <summary>
/// ベクトルの正規化
/// </summary>
/// <param name="vec">正規化したいベクトル</param>
/// <returns>正規化されたベクトル</returns>
VECTOR VecNormalize(VECTOR vec)
{
	VECTOR result = {};

	// ベクトルの長さを計算する
	float vecLong = VecLong(vec);

	// 長さが0のベクトルは計算不可能
	if (vecLong == 0.0f)
	{
		return result;
	}

	// 各成分を長さで割る
	result = VecScale(vec, 1.0f / vecLong);

	return result;
}

/// <summary>
/// ベクトルの内積 A・B
/// </summary>
/// <param name="vecA">ベクトルA</param>
/// <param name="vecB">ベクトルB</param>
/// <returns>計算結果</returns>
float VecDot(VECTOR vecA, VECTOR vecB)
{
	return vecA.x * vecB.x + vecA.y * vecB.y + vecA.z * vecB.z;
}

/// <summary>
/// ベクトルの外積(2D)A×B
/// </summary>
/// <param name="vecA">ベクトルA</param>
/// <param name="vecB">ベクトルB</param>
/// <returns>計算結果</returns>
float VecCross2D(VECTOR vecA, VECTOR vecB)
{
	return vecA.x * vecB.y - vecA.y * vecB.x;
}

/// <summary>
/// ベクトルの外積(3D)A×B
/// </summary>
/// <param name="vecA">ベクトルA</param>
/// <param name="vecB">ベクトルB</param>
/// <returns>計算結果</returns>
VECTOR VecCross3D(VECTOR vecA, VECTOR vecB)
{
	VECTOR result = {};

	result.x = vecA.y * vecB.z - vecA.z * vecB.y;
	result.y = vecA.z * vecB.x - vecA.x * vecB.z;
	result.z = vecA.x * vecB.y - vecA.y * vecB.x;

	return result;
}
