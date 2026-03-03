#include <stdio.h>
#include <string.h>

#define NAME_LENGTH 32
#define ACCOUNT_DATA_MAX 10

struct AccountData
{
	char Name[NAME_LENGTH];	// 口座名
	unsigned short int pin;	// 暗証番号
	int balance;			// 残高
};

enum Mode
{
	CREATE_ACCOUNT = 1,	// 口座開設
	DEPOSIT,			// 預入
	DRAWER				// 引出
};

void ModeInput();
void CreateAccount();
void Deposit();
void Drawer();
void OutputAccountData();

// 入力されたモード
int g_Mode = 0;
// 口座数
int g_AccountNum = 0;
// 口座データ
AccountData g_AccountData[ACCOUNT_DATA_MAX];

int main(void)
{
	ModeInput();

	while (g_Mode >= 1 && g_Mode <= 3)
	{
		switch (g_Mode)
		{
		case CREATE_ACCOUNT:
			CreateAccount();
			break;

		case DEPOSIT:
			Deposit();
			break;

		case DRAWER:
			Drawer();
			break;
		}

		ModeInput();
	}

	// 口座データをファイルに出力
	OutputAccountData();

	printf_s("終了します\n");

	return 0;
}

/// <summary>
/// モード入力
/// </summary>
void ModeInput()
{
	printf_s("ご用件はどちらですか？\n");
	printf_s("1：口座開設\n2：預入\n3：引出\n");

	// 操作モードを入力
	scanf_s("%d", &g_Mode);
}

/// <summary>
/// 口座開設処理
/// </summary>
void CreateAccount()
{
	if (g_AccountNum < ACCOUNT_DATA_MAX)
	{
		printf_s("口座名を入力してください\n");
		scanf_s("%s", g_AccountData[g_AccountNum].Name, NAME_LENGTH);

		printf_s("4桁の暗証番号を設定してください\n");
		scanf_s("%hu", &g_AccountData[g_AccountNum].pin);

		// 設定できるのは0001～9999
		while (g_AccountData[g_AccountNum].pin <= 0 || g_AccountData[g_AccountNum].pin > 9999)
		{
			printf_s("入力した番号では設定できません\n");
			printf_s("4桁の暗証番号を設定してください\n");
			scanf_s("%hu", &g_AccountData[g_AccountNum].pin);
		}

		printf_s("口座開設しました\n\n");

		// アカウント数 + 1
		g_AccountNum++;
	}
	else
	{
		printf_s("これ以上開設できません\n");
	}
}

/// <summary>
/// 預入処理
/// </summary>
void Deposit()
{
	int pin = 0;
	printf_s("暗証番号を入力してください\n");
	scanf_s("%d", &pin);

	for (int i = 0; i < ACCOUNT_DATA_MAX; i++)
	{
		// 暗証番号が一致
		if (g_AccountData[i].pin > 0 && g_AccountData[i].pin == pin)
		{
			int amount = 0;
			printf_s("預入金額を入力してください\n");
			scanf_s("%d", &amount);

			// 預入金額を加算して終了
			g_AccountData[i].balance += amount;

			printf_s("預入が完了しました\n\n");
			break;
		}

		// ここでiが末尾であるならば暗証番号が一致するものが見つからなかった
		if (i == (ACCOUNT_DATA_MAX - 1))
		{
			printf_s("暗証番号が間違っています\n");
			break;
		}
	}

}

/// <summary>
/// 引き出し処理
/// </summary>
void Drawer()
{
	unsigned short int pin = 0;
	printf_s("暗証番号を入力してください\n");
	scanf_s("%hu", &pin);

	for (int i = 0; i < ACCOUNT_DATA_MAX; i++)
	{
		// 暗証番号が一致
		if (g_AccountData[i].pin > 0 && g_AccountData[i].pin == pin)
		{
			int amount = 0;
			printf_s("引出金額を入力してください\n");
			scanf_s("%d", &amount);

			// 残高不足チェック
			while (amount > g_AccountData[i].balance)
			{
				printf_s("残高が不足しています\n");

				printf_s("引出金額を入力してください\n");
				scanf_s("%d", &amount);
			}

			printf_s("引出が完了しました\n\n");

			// 引出金額を減算して終了
			g_AccountData[i].balance -= amount;
			break;
		}

		// ここでiが末尾であるならば暗証番号が一致するものが見つからなかった
		if (i == (ACCOUNT_DATA_MAX - 1))
		{
			printf_s("暗証番号が間違っています\n");
			break;
		}
	}
}

/// <summary>
/// 口座情報を出力
/// </summary>
void OutputAccountData()
{
	FILE* fp;
	fopen_s(&fp, "Data/AccountData.txt", "w");

	if (fp == 0)
	{
		printf_s("ファイルが開けませんでした\n");
		return;
	}

	for (int i = 0; i < ACCOUNT_DATA_MAX; i++)
	{
		// 暗証番号が設定されている口座か
		if (g_AccountData[i].pin > 0)
		{
			fprintf_s(fp, "口座名：%s\n", g_AccountData[i].Name);
			fprintf_s(fp, "暗証番号：%04hu\n", g_AccountData[i].pin);
			fprintf_s(fp, "残高：%d\n\n", g_AccountData[i].balance);
		}
	}

	printf_s("口座情報を出力しました\n");

	// 閉じる
	fclose(fp);
}
