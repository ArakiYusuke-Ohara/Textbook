#include "SightMachine.h"
#include "EnemyParameter.h"
#include "../Bullet/BulletManager.h"
#include "../Math/MyMath.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"
#include <math.h>

#define SIGHT_MACHINE_BULLET_INTERVAL	(60)
#define SIGHT_MACHINE_BULLET_LIFE		(300)
#define SIGHT_MACHINE_BULLET_SPEED		(3.0f)
#define SIGHT_MACHINE_ROTATION_SPEED	(0.03f)

SightMachineData g_SightMachineData = { 0 };

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

	// エネミーからプレイヤーまでのベクトルを作る
	VECTOR playerVec = VecCreate(g_SightMachineData.pos, player.pos);


	// 現在向いている向きを計算
	g_SightMachineData.dir.x = cosf(g_SightMachineData.angle);
	g_SightMachineData.dir.y = sinf(g_SightMachineData.angle);

	// 向きのベクトルは常に正規化しておく
	g_SightMachineData.dir = VecNormalize(g_SightMachineData.dir);

	// ① プレイヤーまでのベクトルと向きのベクトルの内積を求める


	// ② 内積の結果が正であればプレイヤーは前方にいる
	if (0)
	{
		// 外積を計算する
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
}

void FinSightMachine()
{
	DeleteGraph(g_SightMachineData.handle);
}
