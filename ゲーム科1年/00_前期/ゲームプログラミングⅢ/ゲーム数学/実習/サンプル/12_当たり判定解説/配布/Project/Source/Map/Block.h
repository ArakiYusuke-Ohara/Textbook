#pragma once
#include "DxLib.h"
#include "MapParameter.h"

// ëOï˚êÈåæ
struct Body;

void InitBlock();
void LoadBlock();
void StartBlock();
void StepBlock();
void UpdateBlock();
void DrawBlock();
void FinBlock();

void ResolveNormalBlockX(Body* body, const BlockData* block);
void ResolveNormalBlockY(Body* body, const BlockData* block);

BlockData* CreateBlock(MapChipType type, VECTOR pos);
BlockData* GetBlocks();
