#include <stdio.h>

// ジョブの種類を並べた列挙型
enum JobType
{
	KNIGHT,		// ナイト(0)
	THIEF,		// シーフ(1)
	MAGICIAN,	// 魔法使い(2)
	NINJA		// 忍者(3)
};

int main(void)
{
	int job = -1;
	printf_s("ジョブを番号で入力してください\n");
	printf_s("0:ナイト 1:シーフ 2:魔法使い 3:忍者\n");
	scanf_s("%d", &job);

	if (job == KNIGHT)
	{
		printf_s("あなたが選んだジョブはナイトです\n");
	}
	else if (job == THIEF)
	{
		printf_s("あなたが選んだジョブはシーフです\n");
	}
	else if (job == MAGICIAN)
	{
		printf_s("あなたが選んだジョブは魔法使いです\n");
	}
	else if (job == NINJA)
	{
		printf_s("あなたが選んだジョブは忍者です\n");
	}
	else
	{
		printf_s("正しい入力がされていません\n");
	}

	return 0;
}
