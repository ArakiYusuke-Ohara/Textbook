#include <stdio.h>

// ファイルで読み書きするデータは構造体でまとめる
struct Score
{
	int japanese;
	int math;
	int science;
	int english;
};

//int main(void)
//{
//	Score score = {
//		80,
//		70,
//		90,
//		50
//	};
//
//	// ファイル操作に使用するファイルポインタ
//	FILE* fp;
//	// ファイルポインタを使って書き込みモードでファイルを開く
//	fopen_s(&fp, "Data/Score.bin", "wb");
//	// 何らかの理由でファイルが開けなかったら終了
//	if (fp == 0)
//	{
//		printf_s("ファイルが開けませんでした\n");
//		return 0;
//	}
//
//	// fwriteを使えば構造体の中身をまとめて書きだすことができる
//	fwrite(&score, sizeof(score), 1, fp);
//
//	// 使い終わったら必ず閉じること
//	fclose(fp);
//
//	return 0;
//}

int main(void)
{
	// ファイル操作に使用するファイルポインタ
	FILE* fp;
	// ファイルポインタを使って読み込みモードでファイルを開く
	fopen_s(&fp, "Data/Score.bin", "rb");
	// 何らかの理由でファイルが開けなかったら終了
	if (fp == 0)
	{
		printf_s("ファイルが開けませんでした\n");
		return 0;
	}

	Score score;

	// fread_s関数を使えば書き込んだ構造体と同じものをまとめて読み込める
	fread_s(&score, sizeof(score), sizeof(Score), 1, fp);

	// 読み込んだ点数を出力
	printf_s("国語：%d点\n", score.japanese);
	printf_s("数学：%d点\n", score.math);
	printf_s("理科：%d点\n", score.science);
	printf_s("英語：%d点\n", score.english);

	// 使い終わったら必ず閉じること
	fclose(fp);

	return 0;
}
