#include "DxLib.h"
#include "Bullet.h"
#include "../Effect/AnimationEffect.h"
#include "../Sound/SoundManager.h"
#include "../Enemy/EnemyManager.h"

#define HIT_EFFECT_INTERVAL (1)
#define HIT_EFFECT_OFFSET_X (-10.0f)
#define HIT_EFFECT_OFFSET_Y (-10.0f)

BulletData g_BulletData[BULLET_MAX] = { 0 };

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
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ処理をする
		if (!bullet->active)continue;

		// 寿命を減らす
		bullet->life--;
	}
}

void UpdateBullet()
{
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ処理する
		if (!bullet->active)continue;

		// 移動
		bullet->posX += bullet->moveX;
		bullet->posY += bullet->moveY;

		// 寿命処理
		if (bullet->life <= 0)
		{
			// 寿命が過ぎたら生存フラグを折る
			bullet->active = false;
		}
	}
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

void FireBullet(float posX, float posY, float moveX, float moveY)
{
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		// 配列内で使われていないところを探す
		if (!bullet->active)
		{
			// アクティブにする
			bullet->active = true;

			// 画像ハンドル
			bullet->handle = g_BulletHandle;

			// 寿命設定
			bullet->life = BULLET_LIFE;

			// 座標設定
			bullet->posX = posX;
			bullet->posY = posY;

			// 移動量設定
			bullet->moveX = moveX;
			bullet->moveY = moveY;

			// 1発発射準備したらfor文を抜ける
			break;
		}
	}
}

BulletData* GetBullet()
{
	return g_BulletData;
}

void CheckHitEnemy()
{
	// ポインターの配列を制御するにはダブルポインタを使う
	EnemyBaseData** enemyPt = GetEnemy();
	int enemyCount = GetEnemyCount();

	for (int i = 0; i < enemyCount; i++, enemyPt++)
	{
		// ダブルポインターの中にポインターが格納されている
		EnemyBaseData* enemy = (*enemyPt);

		// 生きてるかチェック
		if (!enemy->active) continue;

		BulletData* bullet = g_BulletData;
		for (int j = 0; j < BULLET_MAX; j++, bullet++)
		{

			if (!bullet->active) continue;
		}
	}


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
