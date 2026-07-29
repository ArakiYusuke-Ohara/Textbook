#include "DxLib.h"
#include "Collision.h"
#include "CollisionParameter.h"
#include "../Math/MyMath.h"

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
bool CheckSquareSquare(const Body* bodyA, const Body* bodyB)
{
	// 矩形Aの各辺の位置を計算する
	float leftA = bodyA->pos.x;
	float rightA = bodyA->pos.x + bodyA->width;
	float topA = bodyA->pos.y;
	float bottomA = bodyA->pos.y + bodyA->height;

	// 矩形Bの各辺の位置を計算する
	float leftB = bodyB->pos.x;
	float rightB = bodyB->pos.x + bodyB->width;
	float topB = bodyB->pos.y;
	float bottomB = bodyB->pos.y + bodyB->height;

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

// X軸の衝突解決
void ResolveCollisionX(Body* self, const Body* other)
{
	// 左からあたったか
	if ((self->prevPos.x + self->width) <= other->prevPos.x + COLLISION_EPS)
	{
		// 左に押し出す
		self->pos.x -= (self->pos.x + self->width) - other->pos.x;
	}
	// 右からあたったか
	else if (self->prevPos.x >= (other->prevPos.x + other->width + COLLISION_EPS))
	{
		// 右に押し出す
		self->pos.x += (other->pos.x + other->width) - self->pos.x;
	}

	// 移動量は0にする
	self->move.x = 0.0f;
}

// Y軸の衝突解決
void ResolveCollisionY(Body* self, const Body* other)
{
	// 上からあたったか
	if ((self->prevPos.y + self->height) <= other->prevPos.y + COLLISION_EPS)
	{
		// 上に押し出す
		self->pos.y -= (self->pos.y + self->height) - other->pos.y;
		// 着地
		self->isAir = false;
		// 足元ブロックとして登録
		self->groundBody = other;
		// 移動量は0にする
		self->move.y = 0.0f;
	}
	// 下からあたったか
	else if (self->prevPos.y >= (other->prevPos.y + other->height + COLLISION_EPS))
	{
		// 下に押し出す
		self->pos.y += (other->pos.y + other->height) - self->pos.y;
		// 移動量はブロックに合わせる
		self->move.y = other->move.y;
	}
}
