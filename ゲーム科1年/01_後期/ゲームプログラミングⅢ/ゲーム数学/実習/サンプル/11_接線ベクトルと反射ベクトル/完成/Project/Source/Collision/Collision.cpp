#include "DxLib.h"
#include "Collision.h"
#include "../Player/Player.h"
#include "../Map/Block.h"
#include "../Map//MapManager.h"
#include <math.h>

// 矩形と点の当たり判定
bool CheckSquarePoint(VECTOR squarePos, float squareWidth, float squareHeight, VECTOR point)
{
	// 点のX座標が矩形の間にあるか
	if (point.x >= squarePos.x && point.x <= (squarePos.x + squareWidth))
	{
		// 点のY座標が矩形の間にあるか
		if (point.y >= squarePos.y && (point.y <= squarePos.y + squareHeight))
		{
			// 当たっている
			return true;
		}
	}

	return false;
}

// 矩形と矩形の当たり判定
bool CheckSquareSquare(VECTOR posA, float widthA, float heightA, VECTOR posB, float widthB, float heightB)
{
	// 矩形Aの各辺の位置を計算する
	float leftA = posA.x;
	float rightA = posA.x + widthA;
	float topA = posA.y;
	float bottomA = posA.y + heightA;

	// 矩形Bの各辺の位置を計算する
	float leftB = posB.x;
	float rightB = posB.x + widthB;
	float topB = posB.y;
	float bottomB = posB.y + heightB;

	// 左右の辺がめり込んでいるかチェック
	if (rightA > leftB && leftA < rightB)
	{
		// 上下の片がめり込んでいるかチェック
		if (bottomA > topB && topA < bottomB)
		{
			// 当たっている
			return true;
		}
	}

	return false;
}

// 円と点の当たり判定
bool CheckCirclePoint(VECTOR circlePos, float circleRadius, VECTOR point)
{
	// 円の中心から点までの距離を計算する
	float distance = sqrtf((point.x - circlePos.x) * (point.x - circlePos.x) + (point.y - circlePos.y) * (point.y - circlePos.y));

	// 求めた距離が半径の長さ以下であれば当たっている
	if (distance <= circleRadius)
	{
		return true;
	}

	return false;
}

// 円と点の当たり判定
bool CheckCircleCircle(VECTOR posA, float radA, VECTOR posB, float radB)
{
	// 円の中心間の距離を計算する
	float distance = sqrtf((posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y));

	// 中心間の距離が2つの円の半径の合計以下であれば当たっている
	if (distance <= (radA + radB))
	{
		return true;
	}

	return false;
}
