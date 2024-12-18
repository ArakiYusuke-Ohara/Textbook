#include <stdio.h>
#include <string.h>

// 騎士のデータをまとめた構造体
struct Knight
{
	char name[32];	// 名前
	int attack;		// 攻撃力
	int defense;	// 防御力
	int magic;		// 魔力
	int speed;		// すばやさ
};

int main(void)
{
	// Knight型の変数
	Knight knight = { 0 };

	// Knightポインタ型の変数
	Knight* pointer = &knight;

	// ポインタ変数で構造体のメンバ変数にアクセスするには
	// アロー演算子を使う
	strcpy_s(pointer->name, "ナイト");
	pointer->attack = 10;
	pointer->defense = 6;
	pointer->magic = 4;
	pointer->speed = 2;

	printf_s("職業名：%s\n", pointer->name);
	printf_s("攻撃力：%d\n", pointer->attack);
	printf_s("防御力：%d\n", pointer->defense);
	printf_s("魔力：%d\n", pointer->magic);
	printf_s("すばやさ：%d\n", pointer->speed);

	return 0;
}

int main(void)
{
	// Knight型の配列
	Knight knights[2] = {0};

	// アドレスは配列名だけ
	Knight* pointer = knights;

	// 1体目の設定
	strcpy_s(pointer->name, "ナイト");
	pointer->attack = 10;
	pointer->defense = 6;
	pointer->magic = 4;
	pointer->speed = 2;

	// ポインタを右にずらす
	pointer++;

	// 2体目の設定
	strcpy_s(pointer->name, "ロイヤルナイト");
	pointer->attack = 100;
	pointer->defense = 60;
	pointer->magic = 40;
	pointer->speed = 20;

	// ポインタを0番目に戻す
	pointer = knights;

	// ポインタを使って出力
	for (int i = 0; i < 2; i++, pointer++)
	{
		printf_s("職業名：%s\n", pointer->name);
		printf_s("攻撃力：%d\n", pointer->attack);
		printf_s("防御力：%d\n", pointer->defense);
		printf_s("魔力：%d\n", pointer->magic);
		printf_s("すばやさ：%d\n", pointer->speed);
		printf_s("\n");
	}

	return 0;
}
