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

	switch (job)
	{
	case KNIGHT:
		printf_s("あなたが選んだジョブはナイトです\n");
		break;

	case THIEF:
		printf_s("あなたが選んだジョブはシーフです\n");
		break;

	case MAGICIAN:
		printf_s("あなたが選んだジョブは魔法使いです\n");
		break;

	case NINJA:
		printf_s("あなたが選んだジョブは忍者です\n");
		break;

	default:
		printf_s("正しい入力がされていません\n");
	}

	return 0;
}
