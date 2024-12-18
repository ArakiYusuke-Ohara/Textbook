#include "DxLib.h"
#include "Collision.h"
#include "../Player/Player.h"
#include "../Map/Block.h"
#include "../Map//MapManager.h"
#include <math.h>

// 矩形と点の当たり判定
// 引数
// squarePos:矩形の左上座標
// squareWidth:矩形の横幅
// squareHeight:矩形の高さ
// pointX:点のX座標
// pointY:点のY座標
// 戻り値
// 当たっていればtrue
bool CheckSquarePoint(VECTOR squarePos, float squareWidth, float squareHeight, VECTOR pointPos)
{
	// 点のX座標が矩形の間にあるか
	if (pointPos.x >= squarePos.x && pointPos.x <= (squarePos.x + squareWidth))
	{
		// 点のY座標が矩形の間にあるか
		if (pointPos.y >= squarePos.y && (pointPos.y <= squarePos.y + squareHeight))
		{
			// 当たっている
			return true;
		}
	}

	return false;
}

// 矩形と矩形の当たり判定
// 引数
// squareAPos:矩形Aの左上座標
// squareA_Width:矩形Aの横幅
// squareA_Height:矩形Aの高さ
// squareBPos:矩形Bの左上座標
// squareB_Width:矩形Bの横幅
// squareB_Height:矩形Bの高さ
// 戻り値
// 当たっていればtrue
bool CheckSquareSquare(VECTOR squareAPos, float squareA_Width, float squareA_Height, VECTOR squareBPos, float squareB_Width, float squareB_Height)
{
	// 矩形Aの各辺の位置を計算する
	float leftA = squareAPos.x;
	float rightA = squareAPos.x + squareA_Width;
	float topA = squareAPos.y;
	float bottomA = squareAPos.y + squareA_Height;

	// 矩形Bの各辺の位置を計算する
	float leftB = squareBPos.x;
	float rightB = squareBPos.x + squareB_Width;
	float topB = squareBPos.y;
	float bottomB = squareBPos.y + squareB_Height;

	// 左右の辺がめり込んでいるかチェック
	if (rightA >= leftB && leftA <= rightB)
	{
		// 上下の片がめり込んでいるかチェック
		if (bottomA >= topB && topA <= bottomB)
		{
			// 当たっている
			return true;
		}
	}

	return false;
}

// 円と点の当たり判定
// 引数
// circlePos:円の中心座標
// circleRadius:円の半径
// pointX:点のX座標
// pointY:点のY座標
// 戻り値
// 当たっていればtrue
bool CheckCirclePoint(VECTOR circlePos, float circleRadius, VECTOR pointPos)
{
	// 円の中心から点までの距離を計算する
	float distance = sqrtf((pointPos.x - circlePos.x) * (pointPos.x - circlePos.x) + (pointPos.y - circlePos.y) * (pointPos.y - circlePos.y));

	// 求めた距離が半径の長さ以下であれば当たっている
	if (distance <= circleRadius)
	{
		return true;
	}

	return false;
}

// 円と点の当たり判定
// 引数
// circleAPos:円Aの中心座標
// circleA_Radius:円Aの半径
// circleBPos:円Bの中心座標
// circleB_Radius:円Bの半径
// 戻り値
// 当たっていればtrue
bool CheckCircleCircle(VECTOR circleAPos, float circleA_Radius, VECTOR circleBPos, float circleB_Radius)
{
	// 円の中心間の距離を計算する
	float distance = sqrtf((circleBPos.x - circleAPos.x) * (circleBPos.x - circleAPos.x) + (circleBPos.y - circleAPos.y) * (circleBPos.y - circleAPos.y));

	// 中心間の距離が2つの円の半径の合計以下であれば当たっている
	if (distance <= (circleA_Radius + circleB_Radius))
	{
		return true;
	}

	return false;
}

void CheckCollision()
{
	// ここに当たり判定の処理を書く

	// プレイヤーとマップの当たり判定
	ChceckMapPlayerCollision();
}

