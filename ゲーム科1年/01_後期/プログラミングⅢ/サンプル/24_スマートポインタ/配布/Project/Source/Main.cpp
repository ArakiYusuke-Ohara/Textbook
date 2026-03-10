#include "Player/Player.h"
#include <iostream>
#include <memory>


void CreateUniquePlayer();
void CreateSharedPlayer();
void PracticeWeakPointer();

// プログラムが終了するまで消えないグローバル変数
std::shared_ptr<Player> g_SharedPlayer;
std::weak_ptr<Player> g_WeakPlayer;

int main()
{
	CreateUniquePlayer();

	// 何かキーを押したら終了
	std::cin.get();

	return 0;
}

/// <summary>
/// ユニークポインターでPlayerを生成
/// </summary>
void CreateUniquePlayer()
{
}

/// <summary>
/// 共有ポインターでPlayerを生成
/// </summary>
void CreateSharedPlayer()
{
}

/// <summary>
/// Weakポインター練習
/// </summary>
void PracticeWeakPointer()
{
}
