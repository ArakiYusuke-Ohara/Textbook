#include "DxLib.h"
#include "Bullet.h"
#include "../Effect/AnimationEffect.h"
#include "../Sound/SoundManager.h"

#define HIT_EFFECT_INTERVAL (1)
#define HIT_EFFECT_OFFSET_X (-10.0f)
#define HIT_EFFECT_OFFSET_Y (-10.0f)

// 弾丸の配列


// 各弾丸の画像ハンドル
int g_BulletHandle = 0;

void InitBullet()
{
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet->handle = 0;
		bullet->life = 0;
		bullet->posX = 0.0f;
		bullet->posY = 0.0f;
		bullet->moveX = 0.0f;
		bullet->moveY = 0.0f;
		bullet->active = false;
	}
}

void LoadBullet()
{
	// 画像をロード
	g_BulletHandle = LoadGraph("Data/Bullet/PlayerNormalBullet.png");
}

void StepBullet()
{

}

void UpdateBullet()
{

}

void DrawBullet()
{
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ描画する
		if (!bullet->active) continue;

		DrawGraph((int)bullet->posX, (int)bullet->posY, bullet->handle, TRUE);
	}
}

void FinBullet()
{
	DeleteGraph(g_BulletHandle);
}


BulletData* GetBullet()
{
	return g_BulletData;
}

void BulletHitEnemy(int index)
{
	BulletData* bullet = &g_BulletData[index];

	// 衝突したら死亡
	bullet->active = false;

	// エフェクトを表示
	float effectPosX = bullet->posX;
	float effectPosY = bullet->posY;
	StartAnimationEffect(PLAYER_NORMAL_SHOT_HIT, effectPosX, effectPosY, HIT_EFFECT_INTERVAL);

	// ヒットSE再生
	PlaySE(SE_PLAYRE_SHOT_HIT);
}

void BulletHitPlayer(int index)
{
	BulletData* bullet = &g_BulletData[index];

	// 衝突したら死亡
	bullet->active = false;

	// エフェクトを表示
	float effectPosX = bullet->posX;
	float effectPosY = bullet->posY;
	StartAnimationEffect(ENEMY_BULLET_HIT, effectPosX, effectPosY, HIT_EFFECT_INTERVAL);
}
