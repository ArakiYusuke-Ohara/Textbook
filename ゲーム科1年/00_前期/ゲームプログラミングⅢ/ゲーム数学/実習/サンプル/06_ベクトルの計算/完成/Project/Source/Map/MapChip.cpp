#include "MapChip.h"
#include "MapParameter.h"
#include "Block.h"

MapChipData g_MapChip[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM] = { 0 };

void InitMapChip()
{
	memset(g_MapChip, 0, sizeof(g_MapChip));
}

void LoadMapChipData()
{
	FILE* mapfp;
	FILE* colfp;
	if (fopen_s(&mapfp, "Data/Map/Map.bin", "rb") != 0) return;
	if (fopen_s(&colfp, "Data/Map/MapCollision.bin", "rb") != 0) return;

	for (int i = 0; i < MAP_CHIP_Y_NUM; i++)
	{
		for (int j = 0; j < MAP_CHIP_X_NUM; j++)
		{
			// マップ情報は１バイトずつ保存されているので、
			// fgetc関数でちょうど１バイト取得できる
			int map = fgetc(mapfp);
			int col = fgetc(colfp);
			g_MapChip[i][j].type = map;
			g_MapChip[i][j].isCollision = col;
		}
	}

	// ファイルを閉じる
	fclose(mapfp);
	fclose(colfp);
}

void CreateMap()
{
	for (int i = 0; i < MAP_CHIP_Y_NUM; i++)
	{
		for (int j = 0; j < MAP_CHIP_X_NUM; j++)
		{
			// マップチップに合わせてブロックを生成
			MapChipType type = (MapChipType)g_MapChip[i][j].type;

			// MAP_CHIP_NONEの場合は何もしない
			if (type == MAP_CHIP_NONE) continue;

			// インデックスから座標を計算
			float posX = j * MAP_CHIP_WIDTH;
			float posY = i * MAP_CHIP_HEIGHT;
			// 生成したブロックはMapChipDataで参照しておく
			g_MapChip[i][j].data = CreateBlock(type, posX, posY);
		}
	}
}

const MapChipData* GetMapChipData(int x, int y)
{
	return &g_MapChip[y][x];
}
