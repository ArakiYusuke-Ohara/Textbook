#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Camera/Camera.h"
#include "../Map/MapManager.h"

// アニメーション用パラメータ
struct PlayerAnimationParam
{
	int interval;
	int frameNum;
	int width;
	int height;
};
const PlayerAnimationParam PLAYER_ANIM_PARAM[PLAYER_ANIM_MAX] =
{
	8, 4, 72, 72,
	5, 8, 72, 72,
	8, 2, 72, 72,
	8, 2, 72, 72,
	8, 1, 72, 72,
};

// プレイヤー設定関連
#define PLAYER_RADIUS	(36.0f)
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (700.0f)
#define PLAYER_MOVE_SPEED (3.0f)
#define PLAYER_WIDTH (20)
#define PLAYER_HEIGHT (44)

// ジャンプ力
#define PLAYER_JUMP_POWER (12.0f)
// 重力
#define PLAYER_GRAVITY (0.4f)
// 地面吸いつき力
#define PLAYER_GROUND_SNAP (3.0f)

// 描画位置補正
#define PLAYER_DRAW_OFFSET_X (-24)
#define PLAYER_DRAW_OFFSET_Y (-20)
// 落下判定になるY移動量
#define PLAYER_FALL_Y_MOVE (1.6f)
// キャラクターの周囲何マスまでチェックするか
#define PLAYER_CHECK_ROUND_NUM (16)

PlayerData g_PlayerData = { 0 };

// このCPPでのみ使用する関数の宣言
void StartPlayerAnimation(PlayerAnimationType anim);	// アニメーション再生
void UpdatePlayerAnimation();							// アニメーション更新

void InitPlayer()
{
	g_PlayerData.active = false;
	g_PlayerData.body = {};
	g_PlayerData.playAnim = PLAYER_ANIM_NONE;

	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		InitAnimation(&g_PlayerData.animation[i]);
	}
}

void LoadPlayer()
{
	g_PlayerData.animation[PLAYER_ANIM_IDLE].handle = LoadGraph("Data/Player/PlayerIdle.png");
	g_PlayerData.animation[PLAYER_ANIM_RUN].handle = LoadGraph("Data/Player/PlayerRun.png");
	g_PlayerData.animation[PLAYER_ANIM_JUMP].handle = LoadGraph("Data/Player/PlayerJump.png");
	g_PlayerData.animation[PLAYER_ANIM_FALL].handle = LoadGraph("Data/Player/PlayerFall.png");
	g_PlayerData.animation[PLAYER_ANIM_LANDING].handle = LoadGraph("Data/Player/PlayerLanding.png");
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;

	// 初期位置
	g_PlayerData.body.pos.x = PLAYER_DEFAULT_POS_X;
	g_PlayerData.body.pos.y = PLAYER_DEFAULT_POS_Y;

	// サイズ
	g_PlayerData.body.width = PLAYER_WIDTH;
	g_PlayerData.body.height = PLAYER_HEIGHT;

	// 待機アニメーションから開始する
	StartPlayerAnimation(PLAYER_ANIM_IDLE);
}

void StepPlayer()
{
	// 死んでいたら何もしない
	if (!g_PlayerData.active)
	{
		return;
	}

	// 前回の座標を記憶
	g_PlayerData.body.prevPos.x = g_PlayerData.body.pos.x;
	g_PlayerData.body.prevPos.y = g_PlayerData.body.pos.y;

	// X移動量は毎回リセットする
	g_PlayerData.body.move.x = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.body.move.y += PLAYER_GRAVITY;

	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.body.move.x = -PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = true;
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.body.move.x = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;
	}

	// Z入力
	if (IsTriggerKey(KEY_Z))
	{
		g_PlayerData.body.move.y = -PLAYER_JUMP_POWER;
	}
}

void UpdatePlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// アニメーション更新
	UpdatePlayerAnimation();

	// 当たり判定付き移動
	ResolveMapCollision(&g_PlayerData.body, PLAYER_CHECK_ROUND_NUM);

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_PlayerData.body.move.y < 0.0f || g_PlayerData.body.move.y > PLAYER_FALL_Y_MOVE)
	{
		g_PlayerData.body.isAir = true;
	}

	// 地面にいる場合、足元ブロックに吸いつく（簡単に浮かないようにする）
	if (!g_PlayerData.body.isAir)
	{
		g_PlayerData.body.move.y += PLAYER_GROUND_SNAP;
		ResolveMapCollisionY(&g_PlayerData.body, PLAYER_CHECK_ROUND_NUM);
	}

	// 足元ブロックが動いていればプレイヤーも動く
	if (g_PlayerData.body.groundBlock != NULL)
	{
		g_PlayerData.body.pos.x += g_PlayerData.body.groundBlock->move.x;
		g_PlayerData.body.pos.y += g_PlayerData.body.groundBlock->move.y;
		ResolveMapCollisionY(&g_PlayerData.body, PLAYER_CHECK_ROUND_NUM);
	}
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// カメラ取得
	CameraData camera = GetCamera();

	// 画像の余白が大きいため位置調整が必要
	int x = (int)(g_PlayerData.body.pos.x + PLAYER_DRAW_OFFSET_X - camera.pos.x);
	int y = (int)(g_PlayerData.body.pos.y + PLAYER_DRAW_OFFSET_Y - camera.pos.y);

	// アニメーション描画でプレイヤーを描画する
	PlayerAnimationType animType = g_PlayerData.playAnim;
	AnimationData* animData = &g_PlayerData.animation[animType];
	DrawAnimation(animData, VGet(x, y, 0.0f), g_PlayerData.isTurn);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "プレイヤーの座標＝[%f, %f]", g_PlayerData.body.pos.x, g_PlayerData.body.pos.y);
}

void FinPlayer()
{
	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		DeleteGraph(g_PlayerData.animation[i].handle);
	}
}

PlayerData GetPlayer()
{
	return g_PlayerData;
}

void StartPlayerAnimation(PlayerAnimationType anim)
{
	// 再生中のアニメーションであれば何もしない
	if (anim == g_PlayerData.playAnim) return;

	// 再生中アニメーション設定
	g_PlayerData.playAnim = anim;

	// 再生に必要なデータを取得
	AnimationData* animData = &g_PlayerData.animation[anim];
	PlayerAnimationParam animParam = PLAYER_ANIM_PARAM[anim];

	// アニメーション再生
	StartAnimation(animData, g_PlayerData.body.pos, animParam.interval, animParam.frameNum, animParam.width, animParam.height, true);
}

void UpdatePlayerAnimation()
{
	// 地上にいるか
	if (!g_PlayerData.body.isAir)
	{
		// 横に移動していれば走っている
		if (g_PlayerData.body.move.x < 0.0f || g_PlayerData.body.move.x > 0.0f)
		{
			// 走るアニメーション
			StartPlayerAnimation(PLAYER_ANIM_RUN);
		}
		else
		{
			// 移動していなければ待機
			StartPlayerAnimation(PLAYER_ANIM_IDLE);
		}
	}
	// 空中にいる
	else
	{
		// 上昇していればジャンプアニメーション
		if (g_PlayerData.body.move.y < 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_JUMP);
		}
		// 下降していれば落下アニメーション
		else if (g_PlayerData.body.move.y > 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_FALL);
		}
	}

	// アニメーション更新
	PlayerAnimationType animType = g_PlayerData.playAnim;
	AnimationData* animData = &g_PlayerData.animation[animType];
	UpdateAnimation(animData);
}
