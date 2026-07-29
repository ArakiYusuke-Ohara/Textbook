#pragma once
#include "DxLib.h"

// 前方宣言
struct Body;

// 矩形と点の当たり判定
bool CheckSquarePoint(VECTOR squarePos, float squareWidth, float squareHeight, VECTOR point);

// 矩形と矩形の当たり判定
bool CheckSquareSquare(const Body* bodyA, const Body* bodyB);

// 円と点の当たり判定
bool CheckCirclePoint(VECTOR circlePos, float circleRadius, VECTOR point);

// 円と円の当たり判定
bool CheckCircleCircle(VECTOR posA, float radA, VECTOR posB, float radB);

// 衝突解決関数
void ResolveCollisionX(Body* self, const Body* other);
void ResolveCollisionY(Body* self, const Body* other);
