#pragma once

// 入力ボタン定義
enum InputKey
{
	KEY_UP = (1 << 0),	// 0x0000 0001
	KEY_DOWN = (1 << 1),	// 0x0000 0010
	KEY_LEFT = (1 << 2), // 0x0000 0100
	KEY_RIGHT = (1 << 3), // 0x0000 1000
	KEY_Z = (1 << 4), // 0x0001 0000
};

class Input
{
public:
	// 関数のプロトタイプ宣言 
	static void Init();
	static void Update();
	static void Draw();
	static void Fin();

	static bool IsInputKey(InputKey key);		// キー入力判定
	static bool IsTriggerKey(InputKey key);	// キー押した瞬間判定

private:
	// 入力ビットフラグ
	static int m_InputState;
	// 前回の入力ビット
	static int m_PrevInputState;

};




