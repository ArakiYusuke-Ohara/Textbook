#pragma once
#include "MapParameter.h"

void InitMapChip();
void LoadMapChipData();
void CreateMap();
const MapChipData* GetMapChipData(int x, int y);
