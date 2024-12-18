#include "DxLib.h"
#include "Collision.h"
#include "../Player/Player.h"

void CheckCollision()
{
	// ここに当たり判定の処理を書く

	// プレイヤーとマウスカーソルの当たり判定
	PlayerData* player = GetPlayer();	// プレイヤー取得

	// マウス座標取得
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
}

