#include "DxLib.h"
#include "DragonFly.h"
#include "EnemyParameter.h"
#include "../GameSetting/GameSetting.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Sound/SoundManager.h"

// 撃破時のスコア
#define ENEMY_DRAGON_FLY_SCORE (300)

#define ENEMY_DRAGON_FLY_MOVE_X_MAX	(25.0f)	// 最大移動速度（初速）
#define ENEMY_DRAGON_FLY_BREAK_X	(1.5f)	// ブレーキ力（減速力）
#define ENEMY_DRAGON_FLY_MOVE_Y_MAX	(7.0f)	// 最大移動速度（初速）
#define ENEMY_DRAGON_FLY_BREAK_Y	(0.30f)	// ブレーキ力（減速力）

// 生存できるエリア
#define ENEMY_DRAGON_FLY_ACTIVE_AREA_LEFT	(-100)
#define ENEMY_DRAGON_FLY_ACTIVE_AREA_TOP	(-100)
#define ENEMY_DRAGON_FLY_ACTIVE_AREA_RIGHT	(2000)
#define ENEMY_DRAGON_FLY_ACTIVE_AREA_BOTTOM	(1000)

// 再移動までのインターバル
#define ENEMY_DRAGON_FLY_MOVE_INTERVAL (90)

// 死亡エフェクトのインターバル
#define ENEMY_DRAGON_FLY_DEAD_EFFECT_INTERVAL	(3)

// 変数
EnemyDragonFlyData g_DragonFlyData[ENEMY_DRAGON_FLY_MAX] = { 0 };

// 画像ハンドル
int g_EnemyDragonFlyHandle = 0;

void InitDragonFly()
{
	// ポインタを使って配列を参照する
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		dragonFly->base.posX = 0.0f;
		dragonFly->base.posY = 0.0f;
		dragonFly->base.moveX = 0.0f;
		dragonFly->base.moveY = 0.0f;

		dragonFly->base.active = false;
		dragonFly->isMoveChange = false;

		dragonFly->directionY = 0;
	}
}

void LoadDragonFly()
{
	g_EnemyDragonFlyHandle = LoadGraph("Data/Enemy/DragonFly.png");
}

void StepDragonFly()
{
	// ポインタを使って配列を参照する
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		// 死んでいたら処理しない
		if (!dragonFly->base.active) continue;

		// 徐々に減速
		dragonFly->base.moveX += ENEMY_DRAGON_FLY_BREAK_X;
		// 反対方向にはいかない
		if (dragonFly->base.moveX > 0.0f)
		{
			dragonFly->base.moveX = 0.0f;
		}

		// 上下は交互になるので減速処理も交互
		if (dragonFly->directionY > 0)
		{
			dragonFly->base.moveY -= ENEMY_DRAGON_FLY_BREAK_Y;
			if (dragonFly->base.moveY < 0.0f)
			{
				dragonFly->base.moveY = 0.0f;
			}
		}
		else if(dragonFly->directionY < 0)
		{
			dragonFly->base.moveY += ENEMY_DRAGON_FLY_BREAK_Y;
			if (dragonFly->base.moveY > 0.0f)
			{
				dragonFly->base.moveY = 0.0f;
			}
		}

		// タイマーが0になったら再移動
		if (dragonFly->timer <= 0)
		{
			dragonFly->timer = ENEMY_DRAGON_FLY_MOVE_INTERVAL;

			// 初速を移動量に設定
			dragonFly->base.moveX = -ENEMY_DRAGON_FLY_MOVE_X_MAX;	// 必ず左
			// 上下は交互に
			dragonFly->directionY = -dragonFly->directionY;
			dragonFly->base.moveY = ENEMY_DRAGON_FLY_MOVE_Y_MAX * dragonFly->directionY;
		}

		dragonFly->timer--;
	}
}

void UpdateDragonFly()
{
	// ポインタを使って配列を参照する
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		// 死んでいたら処理しない
		if (!dragonFly->base.active) continue;

		dragonFly->base.posX += dragonFly->base.moveX;
		dragonFly->base.posY += dragonFly->base.moveY;

		// 画面外にでたら死亡
		if (dragonFly->base.posX <= ENEMY_DRAGON_FLY_ACTIVE_AREA_LEFT || dragonFly->base.posX >= ENEMY_DRAGON_FLY_ACTIVE_AREA_RIGHT)
		{
			dragonFly->base.active = false;
		}
		else if (dragonFly->base.posY <= ENEMY_DRAGON_FLY_ACTIVE_AREA_TOP || dragonFly->base.posY >= ENEMY_DRAGON_FLY_ACTIVE_AREA_BOTTOM)
		{
			dragonFly->base.active = false;
		}

	}

}

void DrawDragonFly()
{
	// ポインタを使って配列を参照する
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		// 死んでいたら処理しない
		if (!dragonFly->base.active) continue;

		DrawGraph((int)dragonFly->base.posX, (int)dragonFly->base.posY, dragonFly->base.handle, TRUE);
	}
}

void FinDragonFly()
{
	DeleteGraph(g_EnemyDragonFlyHandle);
}

EnemyDragonFlyData* GetDragonFly()
{
	// 配列の先頭アドレスを返却する
	return g_DragonFlyData;
}

EnemyBaseData* SpawnDragonFly(float posX, float posY)
{
	// ポインタを使って配列を参照する
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		// 未使用のDragonFlyを探す
		if (!dragonFly->base.active)
		{
			// 生存フラグを立てる
			dragonFly->base.active = true;

			// 方向転換フラグを折る
			dragonFly->isMoveChange = false;

			// 画像ハンドル設定
			dragonFly->base.handle = g_EnemyDragonFlyHandle;

			// 座標設定
			dragonFly->base.posX = posX;
			dragonFly->base.posY = posY;

			// 移動量リセット
			dragonFly->base.moveX = 0.0f;
			dragonFly->base.moveY = 0.0f;

			// タイマーリセット
			dragonFly->timer = 0;

			// Y移動方向設定
			dragonFly->directionY = 1;

			break;
		}
	}

	return &dragonFly->base;
}

void DragonFlyHitPlayer(int index)
{
	EnemyDragonFlyData* dragonFly = &g_DragonFlyData[index];

	// 衝突したら死亡
	dragonFly->base.active = false;

	// 死亡エフェクト
	StartAnimationEffect(ENEMY_DEAD, dragonFly->base.posX, dragonFly->base.posY, ENEMY_DRAGON_FLY_DEAD_EFFECT_INTERVAL);
}

void DragonFlyHitPlayerBullet(int index)
{
	EnemyDragonFlyData* dragonFly = &g_DragonFlyData[index];

	// 衝突したら死亡
	dragonFly->base.active = false;

	// スコア加算
	int score = GetScore() + ENEMY_DRAGON_FLY_SCORE;
	SetScore(score);

	// 死亡エフェクト
	StartAnimationEffect(ENEMY_DEAD, dragonFly->base.posX, dragonFly->base.posY, ENEMY_DRAGON_FLY_DEAD_EFFECT_INTERVAL);

	// 死亡SE再生
	PlaySE(SE_ENEMY_DEAD);
}

