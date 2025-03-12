#pragma once

#include "DxLib.h"

enum ObjectMoverType
{
	OBJECT_MOVER_EASE_IN_OUT,
};

struct EaseInOutParam
{
	VECTOR easeInTarget;
	VECTOR easeOutTarget;
	int easeInTime;
	int waitTime;
	int easeOutTime;
};

struct FloatingParam
{
	VECTOR speed;
	VECTOR width;
};
