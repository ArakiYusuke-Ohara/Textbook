#pragma once
// ‘O•ûéŒ¾
struct BlockData;
struct Body;

void StepCircleMoveBlock(BlockData* block);
void UpdateCircleMoveBlock(BlockData* block);
void ResolveCircleMoveBlockX(Body* body, const BlockData* block);
void ResolveCircleMoveBlockY(Body* body, const BlockData* block);
