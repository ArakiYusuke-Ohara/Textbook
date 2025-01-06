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

void CheckCollision()
{
	// ここに当たり判定の処理を書く

	// プレイヤーとマウスカーソルの当たり判定
	PlayerData* player = GetPlayer();	// プレイヤー取得

	// マウス座標取得
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	// 矩形と点の当たり判定
	if (CheckSquarePoint(player->posX, player->posY, PLAYER_WIDTH, PLAYER_HEIGHT, (float)mouseX, (float)mouseY))
	{
		// 当たった
		player->hitFlag = true;
	}

	// 青エネミーとマウスポインタの当たり判定

	// 青エネミー取得
	BlueEnemyData* blueEnemy = GetBlueEnemy();
	if (CheckSquarePoint(blueEnemy->posX, blueEnemy->posY, BLUE_ENEMY_WIDTH, BLUE_ENEMY_HEIGHT, (float)mouseX, (float)mouseY))
	{
		blueEnemy->hitFlag = true;
	}

	// 赤エネミーとマウスポインタの当たり判定

	// 赤エネミー取得
	RedEnemyData* redEnemy = GetRedEnemy();
	for (int i = 0000; i < RED_ENEMY_MAX; i++)
	{
		if (CheckSquarePoint(redEnemy[i].posX, redEnemy[i].posY, RED_ENEMY_WIDTH, RED_ENEMY_HEIGHT, (float)mouseX, (float)mouseY))
		{
			redEnemy[i].hitFlag = true;
		}
	}
}

