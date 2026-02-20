#include "SightMachine.h"
#include "EnemyParameter.h"
#include "../Bullet/BulletManager.h"
#include "../Math/MyMath.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include "../GameSetting/GameSetting.h"
#include <math.h>

#define SIGHT_MACHINE_BULLET_INTERVAL	(60)
#define SIGHT_MACHINE_BULLET_LIFE		(300)
#define SIGHT_MACHINE_BULLET_SPEED		(3.0f)
#define SIGHT_MACHINE_ROTATION_SPEED	(0.03f)

#define SIGHT_MACHINE_VIEWING_ANGLE		(2.5f)
#define SIGHT_MACHINE_FOV_RANGE				(200.0f)

#define BULLET_REFLACT_POWER	(1.0f)

SightMachineData g_SightMachineData = { 0 };

// このCPPでしか使わない関数
bool CheckFieldOfView(VECTOR targetPos);	// 視野判定

void InitSightMachine()
{
	g_SightMachineData.pos = VGet(0.0f, 0.0f, 0.0f);
	g_SightMachineData.handle = 0;
	g_SightMachineData.bulletInterval = 0;
	g_SightMachineData.angle = 0.0f;
}

void LoadSightMachine()
{
	g_SightMachineData.handle = LoadGraph("Data/Enemy/SightMachine.png");
}

void StartSightMachine()
{
	g_SightMachineData.pos = VGet(500.0f, 600.0f, 0.0f);
	g_SightMachineData.bulletInterval = SIGHT_MACHINE_BULLET_INTERVAL;
	g_SightMachineData.angle = 0.0f;
}

void StepSightMachine()
{
	// プレイヤーの情報を取得
	PlayerData player = GetPlayer();

	// 現在向いている向きを計算
	g_SightMachineData.dir.x = cosf(g_SightMachineData.angle);
	g_SightMachineData.dir.y = sinf(g_SightMachineData.angle);

	// 向きのベクトルは常に正規化しておく
	g_SightMachineData.dir = VecNormalize(g_SightMachineData.dir);

	// 視野範囲にプレイヤーがいたら回転する
	if (CheckFieldOfView(player.body.pos))
	{
		// エネミーからプレイヤーまでのベクトルを作る
		VECTOR playerVec = VecCreate(g_SightMachineData.pos, player.body.pos);

		// プレイヤーまでのベクトルと向きのベクトルの外積を求める
		float cross = VecCross2D(playerVec, g_SightMachineData.dir);

		// 計算結果がプラスなら反時計回り
		if (cross >= 0.0f)
		{
			g_SightMachineData.angle -= SIGHT_MACHINE_ROTATION_SPEED;
		}
		// 計算結果がマイナスなら時計回り
		else
		{
			g_SightMachineData.angle += SIGHT_MACHINE_ROTATION_SPEED;
		}

		// 回転値を0～2πに収める
		if (g_SightMachineData.angle > DX_TWO_PI_F)
		{
			g_SightMachineData.angle -= DX_TWO_PI_F;
		}
		else if (g_SightMachineData.angle < 0.0f)
		{
			g_SightMachineData.angle += DX_TWO_PI_F;
		}
	}

	// インターバルが0になったらバレット発射
	if (g_SightMachineData.bulletInterval <= 0)
	{
		// 向いている方向にバレットを発射する
		VECTOR bulletMove = VecScale(g_SightMachineData.dir, SIGHT_MACHINE_BULLET_SPEED);

		// バレット発射データ作成
		FireBulletData fireData = { 0 };
		fireData.life = SIGHT_MACHINE_BULLET_LIFE;
		fireData.pos = g_SightMachineData.pos;
		fireData.move = bulletMove;
		fireData.reflactPower = BULLET_REFLACT_POWER;

		// バレット発射
		FireBullet(BULLET_CATEGORY_STRAIGHT, (int)STRAIGHT_BULLET_TYPE_SIGHT_MACHINE, fireData, BULLET_COLLISION_TAG_ENEMY);

		// インターバルをリセット
		g_SightMachineData.bulletInterval = SIGHT_MACHINE_BULLET_INTERVAL;
	}
	else
	{
		// インターバルをカウントダウン
		g_SightMachineData.bulletInterval--;
	}
}

void UpdateSightMachine()
{
}

void DrawSightMachine()
{
	CameraData camera = GetCamera();
	DrawRotaGraph((int)(g_SightMachineData.pos.x - camera.pos.x), (int)(g_SightMachineData.pos.y - camera.pos.y), 1.0, g_SightMachineData.angle, g_SightMachineData.handle, TRUE);

	// 視野範囲を１ドットずつ半透明で描画
	// （めちゃくちゃ重いので確認用のみで使うこと）
	//int left = (int)(g_SightMachineData.pos.x - SIGHT_MACHINE_FOV_RANGE);
	//int right = (int)(g_SightMachineData.pos.x + SIGHT_MACHINE_FOV_RANGE);
	//int top = (int)(g_SightMachineData.pos.y - SIGHT_MACHINE_FOV_RANGE);
	//int bottom = (int)(g_SightMachineData.pos.y + SIGHT_MACHINE_FOV_RANGE);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//for (int i = left; i < right; i++)
	//{
	//	for (int j = top; j < bottom; j++)
	//	{
	//		if (CheckFieldOfView(VGet((float)i, (float)j, 0.0f)))
	//		{
	//			DrawPixel((int)(i - camera.pos.x), (int)(j - camera.pos.y), GetColor(255, 0, 0));
	//		}
	//	}
	//}
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FinSightMachine()
{
	DeleteGraph(g_SightMachineData.handle);
}

bool CheckFieldOfView(VECTOR targetPos)
{
	// ① エネミーからターゲットまでのベクトルを作る
	VECTOR targetVec = VecCreate(g_SightMachineData.pos, targetPos);

	// ② ターゲットまでの距離を求める
	float targetDistance = VecLong(targetVec);

	// ③ ターゲットまでの距離が視野範囲よりも近いか判定
	if (targetDistance <= SIGHT_MACHINE_FOV_RANGE)
	{
		// ④ ①のベクトルを正規化する
		targetVec = VecNormalize(targetVec);

		// ⑤ ターゲットまでのベクトルと向きのベクトルの内積を計算する
		float targetDot = VecDot(targetVec, g_SightMachineData.dir);

		// ⑥ 視野の淵に沿ったベクトルと向きのベクトルの内積を計算する
		//    淵に沿ったベクトルは計算できないので
		//    ||A|| * ||B|| * cosθ の方法で内積を計算する
		float fovDot = cosf(SIGHT_MACHINE_VIEWING_ANGLE / 2.0f);

		// ⑦ ⑤ >= ⑥ であれば視野範囲にターゲットがいる
		if (targetDot > fovDot)
		{
			return true;
		}
	}

	return false;
}