#pragma once

void InitMap();
void LoadMap();
void StartMap();
void DrawMap();
void FinMap();

bool CheckMapCollision(float posX, float posY, float width, float height, int range, float& o_HitX, float& o_HitY);
