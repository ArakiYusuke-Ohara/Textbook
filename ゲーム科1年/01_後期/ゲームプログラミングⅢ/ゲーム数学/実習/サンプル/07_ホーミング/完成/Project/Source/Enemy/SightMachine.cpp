#include "SightMachine.h"
#include "EnemyParameter.h"
#include "../Bullet/BulletManager.h"
#include "../Math/MyMath.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"

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
	// 回転
	g_SightMachineData.angle += SIGHT_MACHINE_ROTATION_SPEED;
	if (g_SightMachineData.angle > DX_TWO_PI_F)
	{
		g_SightMachineData.angle -= DX_TWO_PI_F;
	}

	// インターバルが0になったらバレット発射
	if (g_SightMachineData.bulletInterval <= 0)
	{
		// プレイヤーの情報
		PlayerData player = GetPlayer();

		// ① 自身の座標からプレイヤーの座標までのベクトルを生成
		VECTOR bulletMove = VecCreate(g_SightMachineData.pos, player.body.pos);

		// ② ①のベクトルを正規化
		bulletMove = VecNormalize(bulletMove);

		// ③ ②のベクトルをバレットの速度でスカラー倍
		bulletMove = VecScale(bulletMove, SIGHT_MACHINE_BULLET_SPEED);

		// バレット発射データ作成
		FireBulletData fireData = { 0 };
		fireData.life = SIGHT_MACHINE_BULLET_LIFE;
		fireData.pos = g_SightMachineData.pos;

		// ③のベクトルをmoveに代入する
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
