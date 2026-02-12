#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "../Collision/Collision.h"

void InitMap()
{
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

/// <summary>
/// マップに配置されたブロックとの当たり判定
/// </summary>
/// <param name="posX">判定したい物体のX座標</param>
/// <param name="posY">判定したい物体のY座標</param>
/// <param name="width">判定したい物体の横幅</param>
/// <param name="height">判定したい物体の縦幅</param>
/// <param name="range">周囲何マスまでチェックするか</param>
/// <param name="o_HitX">当たったブロックのX座標（出力）</param>
/// <param name="o_HitY">当たったブロックのY座標（出力）</param>
/// <param name="o_HitW">当たったブロックの横幅（出力）</param>
/// <param name="o_HitH">当たったブロックの縦幅（出力）</param>
/// <returns>当たったかどうか</returns>
bool CheckMapCollision(float posX, float posY, float width, float height, int range, float &o_HitX, float &o_HitY)
{
	// 座標を添字に変換
	int x = (int)((posX + width / 2) / MAP_CHIP_WIDTH);
	int y = (int)((posY + height / 2) / MAP_CHIP_HEIGHT);
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
			// マップチップが0の場合は何もない
			if (mapChipData.mapChip == 0) continue;

			// ブロックを取り出して当たり判定
			BlockData* block = mapChipData.data;
			// 当たったブロックを返却
			if (CheckSquareSquare(posX, posY, width, height, block->pos.x, block->pos.y, block->width, block->height))
			{
				o_HitX = block->pos.x;
				o_HitY = block->pos.y;
				return true;
			}
		}
	}

	return false;
}
