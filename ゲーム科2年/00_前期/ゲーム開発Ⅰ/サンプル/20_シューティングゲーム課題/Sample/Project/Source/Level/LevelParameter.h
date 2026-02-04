#pragma once
// Levelとは1ステージ分のデータをまとめたもの

enum LevelType
{
	LEVEL_TEST,
	LEVEL_1_1,
	LEVEL_TYPE_NONE = -1
};

struct LevelParameter
{
	int skyID;
	int groundID;
	int blockTableID;
	int enemyTableID;
};

