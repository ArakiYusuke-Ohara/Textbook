#include "StraightBullet.h"
#include "../Effect/AnimationEffect.h"
#include "../Sound/SoundManager.h"
#include "../Camera/Camera.h"
#include "../Math/MyMath.h"
#include "../Map/MapManager.h"
#include "../Map/MapParameter.h"

#define HIT_EFFECT_INTERVAL (1)
#define HIT_EFFECT_OFFSET_X (-10.0f)
#define HIT_EFFECT_OFFSET_Y (-10.0f)
#define CHECK_ROUND_NUM (16)

#define REFLACT_POWER (1.0f)

StraightBulletData g_StraightBulletData[STRAIGHT_BULLET_MAX] = { 0 };

// 各弾丸の画像ハンドル
int g_BulletHandle[STRAIGHT_BULLET_TYPE_MAX] = { 0 };

// 各弾丸の半径データ
float g_BulletRadius[STRAIGHT_BULLET_TYPE_MAX] = { 0 };

void InitStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++)
	{
		bullet->handle = 0;
		bullet->life = 0;
		bullet->body = {};
		bullet->active = false;
	}

	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		g_BulletHandle[i] = 0;
	}
}

void LoadStraightBullet()
{
	int handle = 0;
	int width, height;
	
	// 各バレットの画像をロード
	// プレイヤー通常弾
	handle = LoadGraph("Data/Bullet/PlayerNormalBullet.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = handle;

	// 画像からサイズを取得 画像は正方形が前提
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = (float)width / 2.0f;

	// SightMachine撃つ弾
	handle = LoadGraph("Data/Bullet/SightMachineBullet.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_SIGHT_MACHINE] = handle;

	// 画像からサイズを取得 画像は正方形が前提
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_SIGHT_MACHINE] = (float)width / 2.0f;
}

void StepStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ処理をする
		if (!bullet->active)continue;

		// 寿命を減らす
		bullet->life--;
	}
}

void UpdateStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ処理する
		if (!bullet->active)continue;

		// 当たり判定付き移動
		ResolveMapCollision(&bullet->body, CHECK_ROUND_NUM);

		// 何かに当たり反射しないのであれば志望
		if (bullet->body.hitBody && !(bullet->body.hitBody->reflact))
		{
			bullet->active = false;
		}

		// 寿命チェック
		if (bullet->life <= 0)
		{
			// 生存フラグを折る
			bullet->active = false;
		}
	}
}

void DrawStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ描画する
		if (!bullet->active) continue;

		CameraData camera = GetCamera();
		DrawGraph((int)(bullet->body.pos.x - camera.pos.x), (int)(bullet->body.pos.y - camera.pos.y), bullet->handle, TRUE);
	}
}

void FinStraightBullet()
{
	// ロードした分だけ削除
	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		DeleteGraph(g_BulletHandle[i]);
	}
}

void FireStraightBullet(StraightBulletType type, FireBulletData fireData, BulletCollisionTag tag)
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 配列内で使われていないところを探す
		if (!bullet->active)
		{
			// 発射処理
			bullet->active = true;

			// 寿命設定
			bullet->life = fireData.life;

			// 画像設定
			bullet->handle = g_BulletHandle[type];

			// 座標設定
			bullet->body.pos = fireData.pos;

			// 移動量設定
			bullet->body.move = fireData.move;

			// 画像から幅と高さを取得
			int w, h;
			GetGraphSize(bullet->handle, &w, &h);
			bullet->body.width = (float)w;
			bullet->body.height = (float)h;

			// 画像が正方形の前提で半径を設定
			bullet->body.radius = (float)w / 2;

			// 当たり判定タグ設定
			bullet->tag = tag;

			// 反射力は固定
			bullet->body.reflactPower = REFLACT_POWER;

			// 1発発射したら抜ける
			break;
		}
	}
}

StraightBulletData* GetStraightBullet()
{
	return g_StraightBulletData;
}

void StraightBulletHitEnemy(int index)
{
	StraightBulletData* bullet = &g_StraightBulletData[index];

	// 衝突したら死亡
	bullet->active = false;

	// エフェクトを表示
	StartAnimationEffect(PLAYER_NORMAL_SHOT_HIT, bullet->body.pos, HIT_EFFECT_INTERVAL, false);

	// ヒットSE再生
	PlaySE(SE_PLAYRE_SHOT_HIT);
}

void StraightBulletHitPlayer(int index)
{
	StraightBulletData* bullet = &g_StraightBulletData[index];

	// 衝突したら死亡
	bullet->active = false;

	// エフェクトを表示
	StartAnimationEffect(ENEMY_BULLET_HIT, bullet->body.pos, HIT_EFFECT_INTERVAL, false);
}
