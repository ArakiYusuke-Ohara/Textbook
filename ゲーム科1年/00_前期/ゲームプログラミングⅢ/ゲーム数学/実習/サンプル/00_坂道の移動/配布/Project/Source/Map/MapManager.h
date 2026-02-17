#pragma once
#include "MapParameter.h"
#include "../Collision/CollisionParameter.h"

void InitMap();
void LoadMap();
void StartMap();
void DrawMap();
void FinMap();

// 通常ブロック
void MoveWithMapCollision(Body* body, int range);

// 坂ブロック
void SlopeCollision(Body* body, int range);		// 当たり判定
