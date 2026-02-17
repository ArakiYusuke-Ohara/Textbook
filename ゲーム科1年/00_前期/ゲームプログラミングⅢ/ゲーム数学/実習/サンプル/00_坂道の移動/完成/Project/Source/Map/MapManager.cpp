#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "../Player/Player.h"
#include "../Collision/Collision.h"

// 坂の吸い寄せ範囲
#define SLOPE_ATTRACTION (8.0f)

// このCPPでしか使わない関数
void ResolveSlope(Body* body, const BlockData* block);	// 坂の押し出し

void InitMap()
{
	InitBlock();
}

void LoadMap()
{
	LoadMapChipData();
	LoadBlock();
}

void StartMap()
{
	CreateMap();
}

void DrawMap()
{
	// ブロック描画
	DrawBlock();
}

void FinMap()
{
}

void MoveWithMapCollision(Body* body, int range)
{
	// 座標を添字に変換
	int x = (int)((body->posX + body->width / 2) / MAP_CHIP_WIDTH);
	int y = (int)((body->posY + body->height / 2) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = x - range;
	int top = y - range;
	// プレイヤーの右下にあるマップチップインデックス
	int right = x + range;
	int bottom = y + range;

	// X軸だけ移動する
	body->posX += body->moveX;

	// 左上からチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ取得
			MapChipData mapChipData = GetMapChipData(x, y);

			// フラグチェック
			if (!mapChipData.isCollision) continue;
			// 通常ブロックのみ当たり判定する
			if (mapChipData.type != NORMAL_BLOCK) continue;

			// ブロックを取り出して当たり判定
			BlockData* block = mapChipData.data;
			if (CheckSquareSquare(	body->posX, body->posY, body->width, body->height, 
									block->posX, block->posY, block->width, block->height ))
			{
				// 左からあたったか
				if (body->moveX > 0.0f)
				{
					// 左に押し出す
					body->posX -= (body->posX + body->width) - block->posX;
				}
				// 右からあたったか
				else if (body->moveX < 0.0f)
				{
					// 右に押し出す
					body->posX += (block->posX + block->width) - body->posX;
				}

				// 移動量は0にする
				body->moveX = 0.0f;
			}
		}
	}

	// Y軸だけ移動する
	body->posY += body->moveY;

	// 左上からチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ取得
			MapChipData mapChipData = GetMapChipData(x, y);

			// フラグチェック
			if (!mapChipData.isCollision) continue;
			// 通常ブロックのみ当たり判定する
			if (mapChipData.type != NORMAL_BLOCK) continue;

			// ブロックを取り出して当たり判定
			BlockData* block = mapChipData.data;
			if (CheckSquareSquare(body->posX, body->posY, body->width, body->height,
				block->posX, block->posY, block->width, block->height))
			{
				// 上からあたったか
				if (body->moveY > 0.0f)
				{
					// 上に押し出す
					body->posY -= (body->posY + body->height) - block->posY;
					// 着地
					body->isAir = false;
				}
				// 下からあたったか
				else if (body->moveY < 0.0f)
				{
					// 下に押し出す
					body->posY += (block->posY + block->height) - body->posY;
				}

				// 移動量は0にする
				body->moveY = 0.0f;
			}
		}
	}
}

void SlopeCollision(Body* body, int range)
{
	// 座標を添字に変換
	int x = (int)((body->posX + body->width / 2) / MAP_CHIP_WIDTH);
	int y = (int)((body->posY + body->height / 2) / MAP_CHIP_HEIGHT);
	// プレイヤーの左上にあるマップチップインデックス
	int left = x - range;
	int top = y - range;
	// プレイヤーの右下にあるマップチップインデックス
	int right = x + range;
	int bottom = y + range;

	// 左上からチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ取得
			MapChipData mapChipData = GetMapChipData(x, y);

			// フラグチェック
			if (!mapChipData.isCollision) continue;
			// 通常ブロックのみ当たり判定する
			if (mapChipData.type != SLOPE_BLOCK) continue;

			// ブロックを取り出して当たり判定
			BlockData* block = mapChipData.data;
			if (CheckSquareSquare(body->posX, body->posY, body->width, body->height,
				block->posX, block->posY, block->width, block->height))
			{
				// 押し出して解決
				ResolveSlope(body, block);
			}
		}
	}
}

void ResolveSlope(Body* body, const BlockData* block)
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

	// ① 傾きの値は「Yの増加量 / Xの増加量」
	float a = (endY - startY) / (endX - startX);

	// ② 始点の値と傾きの値を使って切片を計算する
	float b = startY - a * startX;

	// ③ プレイヤーのX座標の中心から坂道の高さ(Y座標を計算する)
	float slopeY = a * playerFootX + b;

	// 坂の高さからある程度上から吸い寄せないと、下るときに浮いてしまう
	if ((body->posY + body->height) >= (slopeY - SLOPE_ATTRACTION))
	{
		// 着地
		body->moveY = 0.0f;
		body->isAir = false;

		// 坂とめり込んでいる分だけ上へ移動
		body->posY -= (body->posY + body->height) - slopeY;
	}
}
