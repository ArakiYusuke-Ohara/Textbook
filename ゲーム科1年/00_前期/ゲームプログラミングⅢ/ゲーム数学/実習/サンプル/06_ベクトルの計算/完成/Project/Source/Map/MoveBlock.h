#pragma once
// ‘O•ûéŒ¾
struct BlockData;
struct Body;

void StepMoveBlock(BlockData* block);
void UpdateMoveBlock(BlockData* block);
void ResolveMoveBlockX(Body* body, const BlockData* block);
void ResolveMoveBlockY(Body* body, const BlockData* block);
