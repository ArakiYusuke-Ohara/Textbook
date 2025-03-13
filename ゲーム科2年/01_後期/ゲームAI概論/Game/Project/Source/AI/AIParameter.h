#pragma once

// CPUの行動の種類
enum CPUStrategy
{
	CPU_STRATEGY_NONE, // なし
	CPU_STRATEGY_CHASE,	// プレイヤー追尾
	CPU_STRATEGY_AWAY,	// プレイヤーから離れる
};
