#include "Character/Player.h"
#include "Character/Jabujabu.h"
#include "Character/Tekuteku.h"
#include <iostream>

using namespace std;

int main()
{
	// プレイヤー生成
	Player* player = new Player;
	// 初期位置設定
	player->SetPos(100, 100);

	// エネミー生成
	Jabujabu* jabujabu = new Jabujabu;
	Tekuteku* tekuteku = new Tekuteku;
	// 初期位置設定
	jabujabu->SetPos(200, 200);
	tekuteku->SetPos(300, 300);
	// 各パラメータ設定
	jabujabu->SetSwimSpeed(20);
	tekuteku->SetWalkSpeed(30);

	// 入力
	char input;
	while (1)
	{
		cout << "プレイヤー操作を入力してください" << endl;
		cout << "wasdで方向設定 fで前進 jでジャンプ" << endl;
		cout << "qで終了" << endl;
		cin >> input;

		// 見やすくするため改行
		cout << endl;

		// qで終了
		if (input == 'q')
		{
			break;
		}

		// 入力に合わせてプレイヤーを操作
		switch (input)
		{
			case 'w':
				player->SetDirection(0);
				break;

			case 'a':
				player->SetDirection(3);
				break;

			case 's':
				player->SetDirection(2);
				break;

			case 'd':
				player->SetDirection(1);
				break;

			case 'f':
				player->MoveForward();
				break;

			case 'j':
				player->Jump();
				break;
		}

		// エネミー操作
		jabujabu->Swim();
		tekuteku->Walk();

		// 画面表示
		player->Draw();
		jabujabu->Draw();
		tekuteku->Draw();

		// 見やすくするため改行
		cout << endl;
	}

	// 各オブジェクトを削除
	delete player;
	delete jabujabu;
	delete tekuteku;

	return 0;
}