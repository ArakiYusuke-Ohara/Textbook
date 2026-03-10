#include "Player/Player.h"
#include <iostream>
#include <memory>


void CreateUniquePlayer();
void CreateSharedPlayer();
void PracticeWeakPointer();

// プログラムが終了するまで消えないグローバル変数
std::shared_ptr<Player> g_SharedPlayer;

int main()
{
	CreateUniquePlayer();

	// 何かキーを押したら終了
	std::cin.get();

	return 0;
}

/// <summary>
/// ユニークポインターでプレイヤーを生成
/// </summary>
void CreateUniquePlayer()
{
	// プレイヤーをユニークポインターで生成
	std::unique_ptr<Player> player = std::make_unique<Player>();

	// ユニークポインターは唯一無二なのでコピーできない
	// std::unique_ptr<Player> player2 = player;

	// 使い方は普通のポインタと同じ
	player->Move();

	// これまでのポインタで参照したい場合はget関数を使う
	Player* playerPtr = player.get();
	playerPtr->Jump();

	// コピーはできないが移動ならmove関数でできる
	// 移動なので移動元のポインタはnullptrになる（所有権の移動）
	std::unique_ptr<Player> player2 = std::move(player);

	// 移動したのでplayerはemptyになっている
	if (!player)
	{
		player2->Attack();
	}

	// 関数を抜けるとローカル変数playerは無くなる
	// スマートポインタで生成したオブジェクトは自動的にdeleteされる
	// （所有権放棄による自動削除）
}

/// <summary>
/// 共有ポインターでプレイヤーを生成
/// </summary>
void CreateSharedPlayer()
{
	// プレイヤーを共有ポインターで生成
	std::shared_ptr<Player> player = std::make_shared<Player>();

	// 共有ポインターはコピーできる
	g_SharedPlayer = player;

	// 使い方は普通のポインタと同じ
	player->Move();
	g_SharedPlayer->Jump();

	// 関数をぬけてplayerがなくなっても
	// g_SharedPlayerが所有しているのでdeleteされない
}

/// <summary>
/// Weakポインターの練習
/// </summary>
void PracticeWeakPointer()
{
	// Shared参照用のWeakポインター
	std::weak_ptr<Player> weakPlayer;

	// sharedが存在するブロック
	{
		// 共有ポインターで生成
		std::shared_ptr<Player> sharedPlayer = std::make_shared<Player>();

		// Weakポインターは共有ポインターをコピーできる
		weakPlayer = sharedPlayer;

		// Weakポインターからはメンバーにアクセスできない
		// weakPlayer->Move();

		// アクセスするにはlock関数を呼び、共有ポインターを取得する
		std::shared_ptr<Player> player = weakPlayer.lock();
		if (player)
		{
			player->Move();
		}

		// ブロックを抜けるとsharedPlayerがなくなる
		// Weakポインターには所有権がないのでPlayerはdeleteされる
	}

	// Weakポインターのlock関数はdeleteされた後はemptyを返す
	std::shared_ptr<Player> player = weakPlayer.lock();
	if (player)
	{
		// ここにはこない
		player->Jump();
	}
}
