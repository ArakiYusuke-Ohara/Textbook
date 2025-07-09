#pragma once
#include "DxLib.h"
#include "PlayerBase.h"

// プレイヤークラス
class Player : public PlayerBase
{
public:
	Player();	// コンストラクタ
	~Player();	// デストラクタ

	void Step() override;	// ステップ

	void InputMove();
	void InputBullet();

};

