#include "DxLib.h"
#include "SlopeBlock.h"
#include "../Player/Player.h"
#include <math.h>

float GetSlopeHeight(float startX, float startY, float endX, float endY, float x);

/// <summary>
/// 衝突解決前の坂道解決
/// </summary>
/// <param name="body">当たり判定ボディ</param>
/// <param name="block">坂道ブロック</param>
void PreviewSlopeBlock(Body* body, const BlockData* block)
{
	// 坂道の始点（左側）
	float startX = block->posX;
	float startY = block->posY + block->width;
	// 坂道の終点（右側）
	float endX = block->posX + block->width;
	float endY = block->posY;
	// プレイヤーの足先のX座標
	float playerFootX = body->posX + body->width;
	// プレイヤーの足先座標は坂の端を超えてはいけない
	if (playerFootX < block->posX) playerFootX = block->posX;
	if (playerFootX > (block->posX + block->width)) playerFootX = (block->posX + block->width);

	float height = GetSlopeHeight(startX, startY, endX, endY, playerFootX);

	// 坂の高さまで押し出す
	if ((body->posY + body->height) >= height)
	{
		// 坂とめり込んでいる分だけ上へ移動
		body->posY -= (body->posY + body->height) - height;
	}
}

void ResolveSlopeBlockX(Body* body, const BlockData* block)
{
	// 何もしない
}

void ResolveSlopeBlockY(Body* body, const BlockData* block)
{
	// 坂道の始点（左側）
	float startX = block->posX;
	float startY = block->posY + block->width;
	// 坂道の終点（右側）
	float endX = block->posX + block->width;
	float endY = block->posY;
	// プレイヤーの足先のX座標
	float playerFootX = body->posX + body->width;
	// プレイヤーの足先座標は坂の端を超えてはいけない
	if (playerFootX < block->posX) playerFootX = block->posX;
	if (playerFootX > (block->posX + block->width)) playerFootX = (block->posX + block->width);

	float height = GetSlopeHeight(startX, startY, endX, endY, playerFootX);

	// 坂の高さまで押し出す
	if ((body->posY + body->height) >= height)
	{
		// 坂とめり込んでいる分だけ上へ移動
		body->posY -= (body->posY + body->height) - height;

		// 着地
		body->moveY = 0.0f;
		body->isAir = false;
	}
}

/// <summary>
/// 坂道の高さを計算する
/// </summary>
/// <param name="startX">坂道の始点X</param>
/// <param name="startY">坂道の始点Y</param>
/// <param name="endX">坂道の終点X</param>
/// <param name="endY">坂道の終点Y</param>
/// <param name="x">坂道上の1点のX座標</param>
/// <returns>坂道の高さ</returns>
float GetSlopeHeight(float startX, float startY, float endX, float endY, float x)
{
	// ① 傾きの値は「Yの増加量 / Xの増加量」
	float a = (endY - startY) / (endX - startX);

	// ② 始点の値と傾きの値を使って切片を計算する
	float b = startY - a * startX;

	// ③ X座標から坂道の高さを計算
	float height = a * x + b;

	return height;
}
