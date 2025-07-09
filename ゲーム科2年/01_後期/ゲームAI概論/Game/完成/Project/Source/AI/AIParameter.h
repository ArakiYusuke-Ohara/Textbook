#pragma once

// CPUの行動の種類
enum CPUStrategy
{
	CPU_STRATEGY_NONE, // なし
	CPU_STRATEGY_CHASE_TARGET,	// プレイヤー追尾
	CPU_STRATEGY_AWAY,	// プレイヤーから離れる
	CPU_STRATEGY_ATTACK,	// 攻撃
};
