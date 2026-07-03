#include "DxLib.h"
#include "Kapu.h"
#include "EnemyParameter.h"
#include "../GameSetting/GameSetting.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Bullet/BulletManager.h"
#include "../Sound/SoundManager.h"

#define ENEMY_KAPU_CHANGE_MOVE_TIME (150)	// 方向転換するまでの時間
#define ENEMY_KAPU_SPEED	(-20.0f)
#define ENEMY_KAPU_BREAK	(0.5f) 

#define ENEMY_KAPU_ACTIVE_AREA_LEFT	(-100)
#define ENEMY_KAPU_ACTIVE_AREA_TOP		(-100)
#define ENEMY_KAPU_ACTIVE_AREA_RIGHT	(2000)
#define ENEMY_KAPU_ACTIVE_AREA_BOTTOM	(1000)

// 撃破時のスコア
#define ENEMY_KAPU_SCORE (1000)

// 死亡エフェクトのインターバル
#define ENEMY_KAPU_DEAD_EFFECT_INTERVAL (3)

// 死亡エフェクト位置オフセット
#define ENEMY_KAPU_DEAD_EFFECT_OFFSET (16.0f)

// バレット関連
#define ENEMY_KAPU_BULLET_INTERVAL	(60)
#define ENEMY_KAPU_BULLET_SPEED		(10.0f)
#define ENEMY_KAPU_BULLET_LIFE		(300)

// HP
#define ENEMY_KAPU_HP (10)

// 変数
EnemyKapuData g_KapuData[ENEMY_KAPU_MAX] = { 0 };

// 画像ハンドル
int g_EnemyKapuHandle = 0;

// 撃破した数
int g_EnemyKapuDestroyNum = 0;

void InitKapu()
{
	// 共通変数初期化
	g_EnemyKapuHandle = 0;
	g_EnemyKapuDestroyNum = 0;

	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		kapu->base.handle = 0;
		kapu->bulletTimer = 0;
		kapu->hp = 0;

		kapu->base.posX = 0.0f;
		kapu->base.posY = 0.0f;
		kapu->base.moveX = 0.0f;
		kapu->base.moveY = 0.0f;

		kapu->base.active = false;
		kapu->isMoveChange = false;
	}
}

void LoadKapu()
{
	g_EnemyKapuHandle = LoadGraph("Data/Enemy/Kapu.png");
}

void StepKapu()
{
	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// 死んでいたら処理しない
		if (!kapu->base.active) continue;

		// 徐々に減速
		kapu->base.moveX += ENEMY_KAPU_BREAK;

		// 移動量が反転しそうになったら止める
		if (kapu->base.moveX > 0.0f)
		{
			kapu->base.moveX = 0.0f;
		}

		// バレットタイマーをカウントダウン
		kapu->bulletTimer--;
	}
}

void UpdateKapu()
{
	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// 死んでいたら処理しない
		if (!kapu->base.active) continue;

		// 移動処理
		kapu->base.posX += kapu->base.moveX;
		kapu->base.posY += kapu->base.moveY;

		// インターバル時間になったら弾発射
		if (kapu->bulletTimer <= 0)
		{
			// 発射
			// FireBullet(kapu->posX, kapu->posY, -5.0f, 0.0f);
			
			// タイマーリセット
			kapu->bulletTimer = ENEMY_KAPU_BULLET_INTERVAL;
		}

		// 画面外にでたら死亡
		if (kapu->base.posX <= ENEMY_KAPU_ACTIVE_AREA_LEFT || kapu->base.posX >= ENEMY_KAPU_ACTIVE_AREA_RIGHT)
		{
			kapu->base.active = false;
		}
		else if (kapu->base.posY <= ENEMY_KAPU_ACTIVE_AREA_TOP || kapu->base.posY >= ENEMY_KAPU_ACTIVE_AREA_BOTTOM)
		{
			kapu->base.active = false;
		}

	}

}

void DrawKapu()
{
	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// 死んでいたら処理しない
		if (!kapu->base.active) continue;

		DrawGraph((int)kapu->base.posX, (int)kapu->base.posY, kapu->base.handle, TRUE);
	}
}

void FinKapu()
{
	DeleteGraph(g_EnemyKapuHandle);
}

EnemyKapuData* GetKapu()
{
	// 配列の先頭アドレスを返却する
	return g_KapuData;
}

EnemyBaseData* SpawnKapu(float posX, float posY)
{
	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// 未使用のKapuを探す
		if (!kapu->base.active)
		{
			// 生存フラグを立てる
			kapu->base.active = true;

			// バレットタイマーを設定
			kapu->bulletTimer = ENEMY_KAPU_BULLET_INTERVAL;

			// HP
			kapu->hp = ENEMY_KAPU_HP;

			// 方向転換フラグを折る
			kapu->isMoveChange = false;

			// 画像ハンドル設定
			kapu->base.handle = g_EnemyKapuHandle;

			// 座標設定
			kapu->base.posX = posX;
			kapu->base.posY = posY;

			// 移動量設定
			kapu->base.moveX = ENEMY_KAPU_SPEED;	// 初速
			kapu->base.moveY = 0.0f;

			break;
		}
	}

	return &kapu->base;
}

void KapuHitPlayer(int index)
{
	EnemyKapuData* kapu = &g_KapuData[index];

	// 衝突したら死亡
	kapu->base.active = false;

	// 死亡エフェクト
	StartAnimationEffect(ENEMY_DEAD, kapu->base.posX, kapu->base.posY, ENEMY_KAPU_DEAD_EFFECT_INTERVAL);

	// 撃破数を加算
	g_EnemyKapuDestroyNum++;
}

void KapuHitPlayerBullet(int index)
{
	EnemyKapuData* kapu = &g_KapuData[index];

	// ダメージ
	kapu->hp--;

	// HPが0になったら死亡
	if (kapu->hp <= 0)
	{
		kapu->base.active = false;

		// 死亡エフェクト
		StartAnimationEffect(ENEMY_DEAD, kapu->base.posX + ENEMY_KAPU_DEAD_EFFECT_OFFSET, kapu->base.posY + ENEMY_KAPU_DEAD_EFFECT_OFFSET, ENEMY_KAPU_DEAD_EFFECT_INTERVAL);

		// スコアを加算
		int score = GetScore() + ENEMY_KAPU_SCORE;
		SetScore(score);

		// 死亡SE再生
		PlaySE(SE_ENEMY_DEAD);

		// 撃破数を加算
		g_EnemyKapuDestroyNum++;
	}
}

// 撃破数を取得
int GetKapuDestroyNum()
{
	return g_EnemyKapuDestroyNum;
}
