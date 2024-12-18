#pragma once

#include "DxLib.h"
#include "../ObjectMover/ObjectMoverParameter.h"

enum EnemyType
{
	ENEMY_BEE,
	ENEMY_DIA,
	ENEMY_TYPE_MAX,
	ENEMY_TYPE_NONE = -1
};

// 敵のデータ
struct EnemyParameter
{
	int hp;
	int interval;
	float speed;
	float radius;
};

// 敵配置データ
struct EnemyLocate
{
	EnemyType type;		// 敵の種類
	float encountDist;	// 出現する距離
	VECTOR pos;			// 配置位置
	VECTOR rot;			// 初期回転値
	int moveType;		// 移動タイプ
	int moveParamId;	// 移動パラメータID
};
