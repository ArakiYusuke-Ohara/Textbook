#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Map/MapManager.h"
#include "../../Bullet/BulletManager.h"
#include "../../Player/Player.h"
#include "../../Camera/Camera.h"
#include "../../Collision/Collision.h"


// 背景のスピード
#define BACK_GROUND_SPEED (-1.5f)

void InitPlayScene()
{
	// プレイヤー初期化
	InitPlayer();

	// エネミー初期化
	InitEnemy();

	// バレット初期化
	InitBullet();

	// マップ初期化
	InitMap();

	// カメラ初期化
	InitCamera();
}

void LoadPlayScene()
{
	// プレイヤーロード
	LoadPlayer();

	// エネミーロード
	LoadEnemy();

	// バレットロード
	LoadBullet();

	// マップをロード
	LoadMap();
}

void StartPlayScene()
{
	// プレイヤー開始
	StartPlayer();

	// エネミー開始
	StartEnemy();

	// マップを開始
	StartMap();
}

void StepPlayScene()
{
	// マップステップ
	StepMap();

	// プレイヤーステップ
	StepPlayer();

	// エネミーステップ
	StepEnemy();

	// バレットステップ
	StepBullet();

	// カメラステップ
	StepCamera();
}

void UpdatePlayScene()
{
	// マップ更新
	UpdateMap();

	// プレイヤー更新
	UpdatePlayer();

	// エネミー更新
	UpdateEnemy();

	// バレット更新
	UpdateBullet();
	
	// 当たり判定
	CheckCollision();
}

void DrawPlayScene()
{
	// マップ描画
	DrawMap();

	// プレイヤー描画
	DrawPlayer();

	// エネミー描画
	DrawEnemy();

	// バレット描画
	DrawBullet();

	// カメラ描画
	DrawCamera();
}

void FinPlayScene()
{
	// マップ終了
	FinMap();

	// プレイヤー終了
	FinPlayer();

	// エネミー終了
	FinEnemy();

	// バレット終了
	FinBullet();
}
