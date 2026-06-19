#include "stdio.h"

int g_MainBoard[3][3] = { 0 };

void PrintBoard();			// 盤面をプリント
int CheckBoard();			// 勝敗チェック
int CheckXY(int x, int y);	// 行列番号チェック

int main(void)
{
	int winner = 0;
	while (1)
	{
		int x = 0;
		int y = 0;

		printf_s("先攻（〇）入力\n");
		printf_s("行番号");
		scanf_s("%d", &y);
		printf_s("列番号");
		scanf_s("%d", &x);
		x--; y--;

		while (CheckXY(x, y) == -1)
		{
			printf_s("もう一度正しい番号を入力してね\n");
			printf_s("行番号");
			scanf_s("%d", &y);
			printf_s("列番号");
			scanf_s("%d", &x);
			x--; y--;
		}

		// このif文がないと警告が出る
		if (x >= 0 && x <= 2 && y >= 0 && y <= 2)
		{
			g_MainBoard[y][x] = 1;
		}

		PrintBoard();
		winner = CheckBoard();
		if (winner != 0) break;

		printf_s("後攻（×）入力\n");
		printf_s("行番号");
		scanf_s("%d", &y);
		printf_s("列番号");
		scanf_s("%d", &x);
		x--; y--;

		while (CheckXY(x, y) == -1)
		{
			printf_s("もう一度正しい番号を入力してね\n");
			printf_s("行番号");
			scanf_s("%d", &y);
			printf_s("列番号");
			scanf_s("%d", &x);
			x--; y--;
		}

		// このif文がないと警告が出る
		if (x >= 0 && x <= 2 && y >= 0 && y <= 2)
		{
			g_MainBoard[y][x] = 2;
		}
		PrintBoard();
		winner = CheckBoard();
		if (winner != 0) break;
	}

	if (winner == 1)
	{
		printf_s("先攻（〇）のかち！！\n");
	}
	else if (winner == 2)
	{
		printf_s("後攻（×）のかち！！\n");
	}
	else if (winner == 3)
	{
		printf_s("ひきわけちゃった。。。\n");
	}

	while (getchar() != '\n');
	getchar();
	return 0;
}

void PrintBoard()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (g_MainBoard[i][j] == 1)
			{
				printf_s("〇");
			}
			else if (g_MainBoard[i][j] == 2)
			{
				printf_s("×");
			}
			else
			{
				printf_s("□");
			}
		}

		printf_s("\n");
	}
}

int CheckBoard()
{
	// 横並びチェック
	for (int i = 0; i < 3; i++)
	{
		if (g_MainBoard[i][0] == 1 && g_MainBoard[i][1] == 1 && g_MainBoard[i][2] == 1)
		{
			return 1;
		}
		else if (g_MainBoard[i][0] == 2 && g_MainBoard[i][1] == 2 && g_MainBoard[i][2] == 2)
		{
			return 2;
		}
	}

	// 縦並びチェック
	for (int i = 0; i < 3; i++)
	{
		if (g_MainBoard[0][i] == 1 && g_MainBoard[1][i] == 1 && g_MainBoard[2][i] == 1)
		{
			return 1;
		}
		else if (g_MainBoard[0][i] == 2 && g_MainBoard[1][i] == 2 && g_MainBoard[2][i] == 2)
		{
			return 2;
		}
	}

	// 右下がり斜めチェック
	if (g_MainBoard[0][0] == 1 && g_MainBoard[1][1] == 1 && g_MainBoard[2][2] == 1)
	{
		return 1;
	}
	else if (g_MainBoard[0][0] == 2 && g_MainBoard[1][1] == 2 && g_MainBoard[2][2] == 2)
	{
		return 2;
	}

	// 右上がり斜めチェック
	if (g_MainBoard[2][0] == 1 && g_MainBoard[1][1] == 1 && g_MainBoard[0][2] == 1)
	{
		return 1;
	}
	else if (g_MainBoard[2][0] == 2 && g_MainBoard[1][1] == 2 && g_MainBoard[0][2] == 2)
	{
		return 2;
	}

	// 引き分けチェック
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 盤面に１つでも0があれば引き分けじゃない
			if (g_MainBoard[i][j] == 0)
			{
				return 0;
			}
		}
	}

	// ここまでくるということは引き分け
	return 3;
}

int CheckXY(int x, int y)
{
	// 列番号チェック
	if (x < 0 || x > 2)
	{
		// ダメな番号になってる
		return -1;
	}

	// 行番号チェック
	if (y < 0 || y > 2)
	{
		// ダメな番号になってる
		return -1;
	}

	// 既に配置済みかチェック
	if (g_MainBoard[y][x] != 0)
	{
		// 既に配置済みだからダメ
		return -1;
	}

	return 0;
}
