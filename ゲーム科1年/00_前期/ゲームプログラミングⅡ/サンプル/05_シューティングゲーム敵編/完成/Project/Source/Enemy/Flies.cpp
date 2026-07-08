#include "DxLib.h"
#include "Flies.h"
#include "../GameSetting/GameSetting.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Sound/SoundManager.h"
#include "../Bullet/Bullet.h"
#include "../Collision/Collision.h"

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
		flies->posX = 0.0f;
		flies->posY = 0.0f;
		flies->moveX = 0.0f;
		flies->moveY = 0.0f;

		flies->active = false;
	}
}

void LoadFlies()
{
	g_EnemyFliesHandle = LoadGraph("Data/Enemy/Flies.png");
}

void StartFlies()
{
	// 敵の配置座標をまとめた配列
	float LOCATE[ENEMY_FLIES_MAX][2] = {
//			x		 y
		{1000.0f, 200.0f},
		{1000.0f, 250.0f},
		{1000.0f, 300.0f},
		{1000.0f, 350.0f},
		{1000.0f, 400.0f},
		{1000.0f, 450.0f},
		{1000.0f, 500.0f},
		{1000.0f, 550.0f},
		{1000.0f, 600.0f},
		{1000.0f, 650.0f},

		{1050.0f, 200.0f},
		{1050.0f, 250.0f},
		{1050.0f, 300.0f},
		{1050.0f, 350.0f},
		{1050.0f, 400.0f},
		{1050.0f, 450.0f},
		{1050.0f, 500.0f},
		{1050.0f, 550.0f},
		{1050.0f, 600.0f},
		{1050.0f, 650.0f},
	};

	// 配置処理
	for (int i = 0; i < ENEMY_FLIES_MAX; i++)
	{
		SpawnFlies(LOCATE[i][0], LOCATE[i][1]);
	}
}

void StepFlies()
{
	// ポインタを使って配列を参照する
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// 死んでいたら処理しない
		if (!flies->active) continue;

	}
}

void UpdateFlies()
{
	// ポインタを使って配列を参照する
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// 死んでいたら処理しない
		if (!flies->active) continue;

		flies->posX += flies->moveX;
		flies->posY += flies->moveY;

		// 画面外にでたら死亡
		if (flies->posX <= ENEMY_FLIES_ACTIVE_AREA_LEFT || flies->posX >= ENEMY_FLIES_ACTIVE_AREA_RIGHT)
		{
			flies->active = false;
		}
		else if (flies->posY <= ENEMY_FLIES_ACTIVE_AREA_TOP || flies->posY >= ENEMY_FLIES_ACTIVE_AREA_BOTTOM)
		{
			flies->active = false;
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
		if (!flies->active) continue;

		DrawGraph((int)flies->posX, (int)flies->posY, flies->handle, TRUE);
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

void SpawnFlies(float posX, float posY)
{
	// ポインタを使って配列を参照する
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// 未使用のFliesを探す
		if (!flies->active)
		{
			// 生存フラグを立てる
			flies->active = true;

			// 画像ハンドル設定
			flies->handle = g_EnemyFliesHandle;

			// 座標設定
			flies->posX = posX;
			flies->posY = posY;

			// 移動量リセット
			flies->moveX = 0.0f;
			flies->moveY = 0.0f;

			break;
		}
	}
}

void FliesHitPlayer(int index)
{
	EnemyFliesData* flies = &g_FliesData[index];

	// 衝突したら死亡
	flies->active = false;

	// 死亡エフェクト
	StartAnimationEffect(ENEMY_DEAD, flies->posX, flies->posY, ENEMY_FLIES_DEAD_EFFECT_INTERVAL);
}

void FliesHitPlayerBullet(int index)
{
	EnemyFliesData* flies = &g_FliesData[index];

	// 衝突したら死亡
	flies->active = false;

	// 死亡エフェクト
	StartAnimationEffect(ENEMY_DEAD, flies->posX, flies->posY, ENEMY_FLIES_DEAD_EFFECT_INTERVAL);

	// スコアを加算
	int score = GetScore() + ENEMY_FLIES_SCORE;
	SetScore(score);

	// 死亡SE再生
	PlaySE(SE_ENEMY_DEAD);
}

