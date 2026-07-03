#include "DxLib.h"
#include "Flies.h"
#include "EnemyParameter.h"
#include "../GameSetting/GameSetting.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Sound/SoundManager.h"

#define ENEMY_FLIES_MOVE_SPEED	(5.0f)	// 移動速度
#define ENEMY_FLIES_CHANGE_MOVE_TIME (150)	// 方向転換するまでの時間

#define ENEMY_FLIES_ACTIVE_AREA_LEFT	(-100)
#define ENEMY_FLIES_ACTIVE_AREA_TOP		(-100)
#define ENEMY_FLIES_ACTIVE_AREA_RIGHT	(2000)
#define ENEMY_FLIES_ACTIVE_AREA_BOTTOM	(1000)

// 撃破時のスコア
#define ENEMY_FLIES_SCORE (100)

// 死亡エフェクトのインターバル
#define ENEMY_FLIES_DEAD_EFFECT_INTERVAL (3)

// 変数
EnemyFliesData g_FliesData[ENEMY_FLIES_MAX] = { 0 };

// 画像ハンドル
int g_EnemyFliesHandle = 0;

void InitFlies()
{
	// ポインタを使って配列を参照する
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		flies->base.posX = 0.0f;
		flies->base.posY = 0.0f;
		flies->base.moveX = 0.0f;
		flies->base.moveY = 0.0f;

		flies->base.active = false;
		flies->isMoveChange = false;
	}
}

void LoadFlies()
{
	g_EnemyFliesHandle = LoadGraph("Data/Enemy/Flies.png");
}

void StepFlies()
{
	// ポインタを使って配列を参照する
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// 死んでいたら処理しない
		if (!flies->base.active) continue;

		// 左に移動
		flies->base.moveX = -ENEMY_FLIES_MOVE_SPEED;

		// まだ方向転換していないか
		if (!flies->isMoveChange)
		{
			// 方向転換する位置まで移動したか
			if (flies->base.posX <= 700.0f)
			{
				// 画面上側にいるときは下、下側にいるときは上に移動
				flies->base.moveY = flies->base.posY < (SCREEN_HEIGHT / 2) ? ENEMY_FLIES_MOVE_SPEED : -ENEMY_FLIES_MOVE_SPEED;
				flies->isMoveChange = true;
			}
		}
	}
}

void UpdateFlies()
{
	// ポインタを使って配列を参照する
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// 死んでいたら処理しない
		if (!flies->base.active) continue;

		flies->base.posX += flies->base.moveX;
		flies->base.posY += flies->base.moveY;

		// 画面外にでたら死亡
		if (flies->base.posX <= ENEMY_FLIES_ACTIVE_AREA_LEFT || flies->base.posX >= ENEMY_FLIES_ACTIVE_AREA_RIGHT)
		{
			flies->base.active = false;
		}
		else if (flies->base.posY <= ENEMY_FLIES_ACTIVE_AREA_TOP || flies->base.posY >= ENEMY_FLIES_ACTIVE_AREA_BOTTOM)
		{
			flies->base.active = false;
		}

	}

}

void DrawFlies()
{
	// ポインタを使って配列を参照する
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// 死んでいたら処理しない
		if (!flies->base.active) continue;

		DrawGraph((int)flies->base.posX, (int)flies->base.posY, flies->base.handle, TRUE);
	}
}

void FinFlies()
{
	DeleteGraph(g_EnemyFliesHandle);
}

EnemyFliesData* GetFlies()
{
	// 配列の先頭アドレスを返却する
	return g_FliesData;
}

EnemyBaseData* SpawnFlies(float posX, float posY)
{
	// ポインタを使って配列を参照する
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// 未使用のFliesを探す
		if (!flies->base.active)
		{
			// 生存フラグを立てる
			flies->base.active = true;

			// 方向転換フラグを折る
			flies->isMoveChange = false;

			// 画像ハンドル設定
			flies->base.handle = g_EnemyFliesHandle;

			// 座標設定
			flies->base.posX = posX;
			flies->base.posY = posY;

			// 移動量リセット
			flies->base.moveX = 0.0f;
			flies->base.moveY = 0.0f;

			break;
		}
	}

	return &flies->base;
}

void FliesHitPlayer(int index)
{
	EnemyFliesData* flies = &g_FliesData[index];

	// 衝突したら死亡
	flies->base.active = false;

	// 死亡エフェクト
	StartAnimationEffect(ENEMY_DEAD, flies->base.posX, flies->base.posY, ENEMY_FLIES_DEAD_EFFECT_INTERVAL);
}

void FliesHitPlayerBullet(int index)
{
	EnemyFliesData* flies = &g_FliesData[index];

	// 衝突したら死亡
	flies->base.active = false;

	// 死亡エフェクト
	StartAnimationEffect(ENEMY_DEAD, flies->base.posX, flies->base.posY, ENEMY_FLIES_DEAD_EFFECT_INTERVAL);

	// スコアを加算
	int score = GetScore() + ENEMY_FLIES_SCORE;
	SetScore(score);

	// 死亡SE再生
	PlaySE(SE_ENEMY_DEAD);
}

