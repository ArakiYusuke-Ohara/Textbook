#pragma once
#include <DxLib.h>
#include "../Quatrenion/Quatrenion.h"

// position_3D,posX_2D,posY_2D,rotation,scaleを持った構造体
struct Transform
{
	VECTOR pos;
	Quaternion rotation;
	VECTOR scale;
};
