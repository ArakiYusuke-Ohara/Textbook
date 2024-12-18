#include "DxLib.h"
#include "Input.h"

int Input::m_InputState = 0;
int Input::m_PrevInputState = 0;

void Input::Init()
{
	m_InputState = 0;
	m_PrevInputState = 0;
}

void Input::Update()
{
	// 前回の入力を覚えておく
	m_PrevInputState = m_InputState;

	// 入力状態をクリア
	m_InputState = 0;

	// 入力状態をビットフラグで設定
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_InputState |= KEY_UP;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_InputState |= KEY_DOWN;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_InputState |= KEY_LEFT;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_InputState |= KEY_RIGHT;
	}
	if (CheckHitKey(KEY_INPUT_Z))
	{
		m_InputState |= KEY_Z;
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
	return m_InputState & key;
}

bool Input::IsTriggerKey(InputKey key)
{
	return (m_InputState & key) && !(m_PrevInputState & key);
}




