#include "DxLib.h"
#include "Collision.h"
#include "../Player/Player.h"
#include "../Enemy/BlueEnemy.h"
#include "../Enemy/RedEnemy.h"

// 矩形と点の当たり判定
// 引数
// squarePosX:矩形の左上X座標
// squarePosY:矩形の左上Y座標
// squareWidth:矩形の横幅
// squareHeight:矩形の高さ
// pointX:点のX座標
// pointY:点のY座標
// 戻り値
// 当たっていればtrue
bool CheckSquarePoint(float squarePosX, float squarePosY, float squareWidth, float squareHeight, float pointX, float pointY)
{
	// 点のX座標が矩形の間にあるか
	if (pointX >= squarePosX && pointX <= (squarePosX + squareWidth))
	{
		// 点のY座標が矩形の間にあるか
		if (pointY >= squarePosY && (pointY <= squarePosY + squareHeight))
		{
			// 当たっている
			return true;
		}
	}

	return false;
}

// 矩形と点の当たり判定
// 引数
// squareA_PosX:矩形Aの左上X座標
// squareA_PosY:矩形Aの左上Y座標
// squareA_Width:矩形Aの横幅
// squareA_Height:矩形Aの高さ
// squareB_PosX:矩形Bの左上X座標
// squareB_PosY:矩形Bの左上Y座標
// squareB_Width:矩形Bの横幅
// squareB_Height:矩形Bの高さ
// 戻り値
// 当たっていればtrue
bool CheckSquareSquare(float squareA_PosX, float squareA_PosY, float squareA_Width, float squareA_Height, float squareB_PosX, float squareB_PosY, float squareB_Width, float squareB_Height)
{
	// 矩形Aの各辺の位置を計算する
	float leftA = squareA_PosX;
	float rightA = squareA_PosX + squareA_Width;
	float topA = squareA_PosY;
	float bottomA = squareA_PosY + squareA_Height;

	// 矩形Bの各辺の位置を計算する
	float leftB = squareB_PosX;
	float rightB = squareB_PosX + squareB_Width;
	float topB = squareB_PosY;
	float bottomB = squareB_PosY + squareB_Height;

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

void CheckCollision()
{
	// ここに当たり判定の処理を書く

	// 当たったら移動前の場所に戻す方法（簡単～普通の場合）
	{
		//PlayerData* player = GetPlayer();
		//BlueEnemyData* blueEnemy = GetBlueEnemy();
		//if (CheckSquareSquare(player->posX, player->posY, PLAYER_WIDTH, PLAYER_HEIGHT,
		//	blueEnemy->posX, blueEnemy->posY, BLUE_ENEMY_WIDTH, BLUE_ENEMY_HEIGHT))
		//{
		//	PlayerHitBlueEnemy();
		//}
	}

	// 当たりながらスライドする方法（難しい）
	{
		PlayerMoveAndCollision();
	}
}

