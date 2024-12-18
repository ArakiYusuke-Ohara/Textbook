#pragma once

struct BoxCollision
{
	VECTOR pos;
	float width;
	float height;
};

// 関数のプロトタイプ宣言

// 矩形と点の当たり判定
bool CheckSquarePoint(VECTOR squarePos, float squareWidth, float squareHeight, VECTOR pointPos);

// 矩形と矩形の当たり判定
bool CheckSquareSquare(VECTOR squareAPos, float squareA_Width, float squareA_Height, VECTOR squareBPos, float squareB_Width, float squareB_Height);

// 円と点の当たり判定
bool CheckCirclePoint(VECTOR circlePos, float circleRadius, VECTOR pointPos);

// 円と円の当たり判定
bool CheckCircleCircle(VECTOR circleAPos, float circleA_Radius, VECTOR circleBPos, float circleB_Radius);

// 各当たり判定を行う
void CheckCollision();

