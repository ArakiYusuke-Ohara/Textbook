#pragma once
// ëOï˚êÈåæ
struct BlockData;
struct Body;

void StartArchMoveBlock(BlockData* block);
void StepArchMoveBlock(BlockData* block);
void UpdateArchMoveBlock(BlockData* block);
void ResolveArchMoveBlockX(Body* body, const BlockData* block);
void ResolveArchMoveBlockY(Body* body, const BlockData* block);
