#pragma once
// ‘O•ûéŒ¾
struct BlockData;
struct Body;

void StepAutoDoor(BlockData* block);
void UpdateAutoDoor(BlockData* block);
void ResolveAutoDoorX(Body* body, const BlockData* block);
void ResolveAutoDoorY(Body* body, const BlockData* block);
