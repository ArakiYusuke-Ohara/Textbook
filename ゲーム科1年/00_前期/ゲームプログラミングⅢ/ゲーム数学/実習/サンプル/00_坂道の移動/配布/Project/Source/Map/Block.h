#pragma once
#include "MapParameter.h"

void InitBlock();
void LoadBlock();
void StartBlock();
void StepBlock();
void DrawBlock();
void FinBlock();

BlockData* CreateBlock(MapChipType type, float posX, float posY);
BlockData* GetBlocks();
