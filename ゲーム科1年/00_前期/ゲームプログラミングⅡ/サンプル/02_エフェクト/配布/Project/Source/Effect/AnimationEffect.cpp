#include "DxLib.h"
#include "AnimationEffect.h"
#include "AnimationEffectParameter.h"

// アニメーションエフェクトデータ
AnimationEffectData g_AnimationEffectData[ANIMATION_EFFECT_MAX] = { 0 };

// エフェクトの画像ハンドル
int g_AnimationEffectHandle[ANIMATION_EFFECT_TYPE_MAX];

// エフェクト初期化
void InitAnimationEffect()
{
	AnimationEffectData* effect = g_AnimationEffectData;
	for (int i = 0; i < ANIMATION_EFFECT_MAX; i++, effect++)
	{
		effect->active = false;
		effect->handle = 0;
		effect->nowFrame = 0;
		effect->frameNum = 0;
		effect->frameWidth = 0;
		effect->frameHeight = 0;
		effect->timer = 0;
		effect->posX = 0.0f;
		effect->posY = 0.0f;
	}
}

// エフェクトロード
void LoadAnimationEffect()
{
	g_AnimationEffectHandle[PLAYER_NORMAL_SHOT_HIT] = LoadGraph("Data/Effect/PlayerNormalBulletHit.png");
	g_AnimationEffectHandle[PLAYER_DEAD] = LoadGraph("Data/Effect/PlayerDead.png");
	g_AnimationEffectHandle[ENEMY_DEAD] = LoadGraph("Data/Effect/EnemyDead.png");
	g_AnimationEffectHandle[ENEMY_BULLET_HIT] = LoadGraph("Data/Effect/KapuBulletHit.png");
}

// エフェクトステップ
void StepAnimationEffect()
{
	AnimationEffectData* effect = g_AnimationEffectData;
	for (int i = 0; i < ANIMATION_EFFECT_MAX; i++, effect++)
	{
		if (!effect->active) continue;

		// 次のコマへ進めるか
		if (effect->timer <= 0)
		{
			// 次のコマへ
			effect->nowFrame++;
			// タイマーリセット
			effect->timer = effect->interval;

			// 全コマ表示し終わったら非アクティブ
			if (effect->nowFrame >= effect->frameNum)
			{
				effect->active = false;

				// これ以上処理する必要なし
				continue;
			}
		}

		effect->timer--;
	}
}

// エフェクト更新
void UpdateAnimationEffect()
{
}

// エフェクト描画
void DrawAnimationEffect()
{
	AnimationEffectData* effect = g_AnimationEffectData;
	for (int i = 0; i < ANIMATION_EFFECT_MAX; i++, effect++)
	{
		// 未使用のエフェクトは処理しない
		if (!effect->active)continue;

		// 1コマ分の横幅（effect->frameWidth）と
		// 現在のコマ数（effect->nowFrame）から、
		// 切り取る部分を計算する


		// DrawRectGraph関数で描画すべきコマの部分だけ描画する


	}
}

// エフェクト終了
void FinAnimationEffect()
{
	for (int i = 0; i < ANIMATION_EFFECT_TYPE_MAX; i++)
	{
		DeleteGraph(g_AnimationEffectHandle[i]);
	}
}

// エフェクト再生
void PlayAnimationEffect(AnimationEffectType type, float posX, float posY, int interval)
{
	// マスターパラム取得
	AnimationEffectMasterParameter param = ANIM_EFFECT_MASTER_PARAM[type];

	AnimationEffectData* effect = g_AnimationEffectData;
	for (int i = 0; i < ANIMATION_EFFECT_MAX; i++, effect++)
	{
		// 未使用のエフェクトを探す
		if (!effect->active)
		{
			// アクティブ
			effect->active = true;

			// 座標設定
			effect->posX = posX;
			effect->posY = posY;

			// インターバル設定
			effect->interval = interval;

			// タイマー設定
			effect->timer = effect->interval;

			// 画像ハンドル
			effect->handle = g_AnimationEffectHandle[type];

			// 0コマ目にする
			effect->nowFrame = 0;

			// コマ数
			effect->frameNum = param.frameNum;

			// 1コマのサイズ
			effect->frameWidth = param.frameWidth;
			effect->frameHeight = param.frameHeight;

			break;
		}
	}
}
