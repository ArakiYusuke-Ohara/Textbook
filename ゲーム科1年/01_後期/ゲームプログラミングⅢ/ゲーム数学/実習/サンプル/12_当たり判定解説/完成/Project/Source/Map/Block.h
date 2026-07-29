#pragma once
#include "DxLib.h"
#include "MapParameter.h"

// ‘O•ûéŒ¾
struct Body;

void InitBlock();
void LoadBlock();
void StartBlock();
void StepBlock();
void UpdateBlock();
void DrawBlock();
void FinBlock();

BlockData* CreateBlock(MapChipType type, VECTOR pos);
BlockData* GetBlocks();
