#pragma once
#include "DxLib.h"

// ‹éŒ`‚Æ“_‚Ì“–‚½‚è”»’è
bool CheckSquarePoint(VECTOR squarePos, float squareWidth, float squareHeight, VECTOR point);

// ‹éŒ`‚Æ‹éŒ`‚Ì“–‚½‚è”»’è
bool CheckSquareSquare(VECTOR posA, float widthA, float heightA, VECTOR posB, float widthB, float heightB);

// ‰~‚Æ“_‚Ì“–‚½‚è”»’è
bool CheckCirclePoint(VECTOR circlePos, float circleRadius, VECTOR point);

// ‰~‚Æ‰~‚Ì“–‚½‚è”»’è
bool CheckCircleCircle(VECTOR posA, float radA, VECTOR posB, float radB);
