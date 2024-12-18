#pragma once

// 関数のプロトタイプ宣言
// 矩形と点の当たり判定
bool CheckSquarePoint(float squarePosX, float squarePosY, float squareWidth, float squareHeight, float pointX, float pointY);

// 各当たり判定を行う
void CheckCollision();

