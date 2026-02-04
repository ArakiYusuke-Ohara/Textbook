#include "DxLib.h"
#include "Input.h"

// 入力ビットフラグ
int g_InputState;
// 前回の入力ビット
int g_PrevInputState;

namespace Input
{
	void Input::Init()
	{
		g_InputState = 0;
		g_PrevInputState = 0;
	}

	void Input::Update()
	{
		// 前回の入力を覚えておく
		g_PrevInputState = g_InputState;

		// 入力状態をクリア
		g_InputState = 0;

		// 入力状態をビットフラグで設定
		if (CheckHitKey(KEY_INPUT_UP))
		{
			g_InputState |= KEY_UP;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			g_InputState |= KEY_DOWN;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			g_InputState |= KEY_LEFT;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			g_InputState |= KEY_RIGHT;
		}
		if (CheckHitKey(KEY_INPUT_Z))
		{
			g_InputState |= KEY_Z;
		}
	}

	void Input::Draw()
	{
	}

	void Input::Fin()
	{
	}

	bool Input::IsInputKey(InputKey key)
	{
		return g_InputState & key;
	}

	bool Input::IsTriggerKey(InputKey key)
	{
		return (g_InputState & key) && !(g_PrevInputState & key);
	}
}
