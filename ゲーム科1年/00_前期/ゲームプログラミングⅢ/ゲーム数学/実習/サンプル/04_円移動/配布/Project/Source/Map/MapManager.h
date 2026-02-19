#pragma once

// 前方宣言
struct Body;
struct MapChipData;

void InitMap();
void LoadMap();
void StartMap();
void StepMap();
void UpdateMap();
void DrawMap();
void FinMap();

// 当たり判定関数
void ResolveMapCollision(Body* body, int range);	// 通常ブロック
void ResolveMapCollisionX(Body* body, int range);	// 通常ブロック
void ResolveMapCollisionY(Body* body, int range);	// 通常ブロック
