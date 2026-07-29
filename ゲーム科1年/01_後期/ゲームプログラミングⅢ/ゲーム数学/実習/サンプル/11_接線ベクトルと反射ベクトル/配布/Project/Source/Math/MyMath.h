#pragma once
#include "DxLib.h"

VECTOR VecCreate(VECTOR start, VECTOR end);		// ベクトル生成
VECTOR VecAdd(VECTOR vecA, VECTOR vecB);		// ベクトルの足し算
VECTOR VecScale(VECTOR vec, float scale);		// ベクトルのスカラー倍
float VecLong(VECTOR vec);						// ベクトルの長さ
VECTOR VecNormalize(VECTOR vec);				// ベクトルの正規化
float VecDot(VECTOR vecA, VECTOR vecB);			// ベクトルの内積
float VecCross2D(VECTOR vecA, VECTOR vecB);		// ベクトルの外積（2D）
VECTOR VecCross3D(VECTOR vecA, VECTOR vecB);	// ベクトルの外積（3D）
VECTOR GetDirXY(float angle);					// 角度に合わせた向きベクトルを計算
VECTOR VecTangent(VECTOR vecIncident, VECTOR vecNormal);	// 接線ベクトルを計算
VECTOR VecReflact(VECTOR vecIncident, VECTOR vecNormal);	// 反射ベクトルを計算

