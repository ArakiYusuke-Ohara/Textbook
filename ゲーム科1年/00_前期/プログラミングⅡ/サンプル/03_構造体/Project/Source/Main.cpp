#include <stdio.h>
#include <string.h>

// 人間のデータをまとめた構造体
struct Human
{
	// 構造体にある変数をメンバ変数と言う
	char name[32];	// 名前
	int age;		// 年齢
	float height;	// 身長
	float weight;	// 体重
};

int main(void)
{
	// 構造体Human型の変数
	Human teacher = { 0 };

	// 各メンバ変数にはドット（.）でアクセスする
	strcpy_s(teacher.name, "荒木 優介");	// 文字列は代入できないのでstrcpy_s関数を使う
	teacher.age = 33;
	teacher.height = 170.4f;
	teacher.weight = 71.5f;

	printf_s("名前：%s\n", teacher.name);
	printf_s("年齢：%d\n", teacher.age);
	printf_s("身長：%f\n", teacher.height);
	printf_s("体重：%f\n", teacher.weight);

	return 0;
}

int main(void)
{
	// 構造体は{}で初期値を設定できる
	Human teacher = 
	{
		"荒木 優介",
		33,
		170.4f,
		71.5f
	};

	printf_s("名前：%s\n", teacher.name);
	printf_s("年齢：%d\n", teacher.age);
	printf_s("身長：%f\n", teacher.height);
	printf_s("体重：%f\n", teacher.weight);

	return 0;
}

int main(void)
{
	// 構造体も配列にできる
	Human teachers[2] = { 0 };

	// メンバ変数へのアクセスは添字＋ドットになる
	strcpy_s(teachers[0].name, "山田 一郎");
	teachers[0].age = 54;
	teachers[0].height = 165.3f;
	teachers[0].weight = 60.2f;

	strcpy_s(teachers[1].name, "田中 二郎");
	teachers[1].age = 41;
	teachers[1].height = 175.9f;
	teachers[1].weight = 73.8f;

	// 配列だからfor文で網羅できる
	for (int i = 0; i < 2; i++)
	{
		printf_s("名前：%s\n", teachers[i].name);
		printf_s("年齢：%d\n", teachers[i].age);
		printf_s("身長：%f\n", teachers[i].height);
		printf_s("体重：%f\n", teachers[i].weight);
		printf_s("\n");
	}
};
