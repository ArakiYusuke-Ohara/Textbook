#include "MapChip.h"
#include "DxLib.h"
#include "../GameSetting/GameSetting.h"
#include "MapParameter.h"
#include "Block.h"

MapChipData g_MapChip[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM] = { 0 };


void LoadMapChipData()
{
}

void CreateMap()
{
}

MapChipData GetMapChipData(int x, int y)
{
	return g_MapChip[y][x];
}
