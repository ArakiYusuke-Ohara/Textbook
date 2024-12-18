#include <fstream>
#include <iostream>

using namespace std;

// 保存するデータは構造体にまとめておくと便利
struct EnemyStatus
{
	char name[32];
	int hp;
	int power;
	int defense;
	float damageOffset;
};

int main()
{
	EnemyStatus enemyStatus = { 0 };
	char isLoadFile = ' ';
	char isSaveFile = ' ';

	cout << "ファイルをロードしますか？" << endl;
	cout << "y：はい　n：いいえ" << endl;
	cin >> isLoadFile;

	if (isLoadFile == 'y')
	{
		// ファイルを開く
		ifstream file("Data/EnemyStatus.bin", ios::binary);
		if (!file)
		{
			// ファイルが開けなかった
			cout << "ファイルが開けませんでした" << endl;
			return 0;
		}

		// ファイルを読み込む
		file.read(reinterpret_cast<char*>(&enemyStatus), sizeof(enemyStatus));

		// 使わなくなったら閉じる
		file.close();

		cout << "敵の名前：" << enemyStatus.name << endl;
		cout << "敵のHP：" << enemyStatus.hp << endl;
		cout << "敵の攻撃力：" << enemyStatus.power << endl;
		cout << "敵の防御力：" << enemyStatus.defense << endl;
		cout << "敵のダメージ補正：" << enemyStatus.damageOffset << endl;

	}

	cout << "敵ステータスをセーブしますか？" << endl;
	cout << "y：はい　n：いいえ" << endl;
	cin >> isSaveFile;

	if (isSaveFile == 'y')
	{
		cout << "敵の名前を入力（16文字以内）" << endl;
		cin >> enemyStatus.name;

		cout << "敵のHPを入力" << endl;
		cin >> enemyStatus.hp;

		cout << "敵の攻撃力を入力" << endl;
		cin >> enemyStatus.power;

		cout << "敵の防御力を入力" << endl;
		cin >> enemyStatus.defense;

		cout << "敵のダメージ補正を入力" << endl;
		cin >> enemyStatus.damageOffset;

		// ファイルを開く
		ofstream file("Data/EnemyStatus.bin", std::ios::binary);
		if (!file)
		{
			// ファイルが開けなかった
			cout << "ファイルが開けませんでした" << endl;
			return 0;
		}

		// ファイルを書き出す
		file.write(reinterpret_cast<char*>(&enemyStatus), sizeof(enemyStatus));

		// ファイルを閉じる
		file.close();
	}

	return 0;
}