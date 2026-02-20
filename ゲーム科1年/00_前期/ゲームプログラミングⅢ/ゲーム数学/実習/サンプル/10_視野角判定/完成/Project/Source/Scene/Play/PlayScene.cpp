#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/MapManager.h"
#include "../../Player/Player.h"
#include "../../Camera/Camera.h"
#include "../../Collision/Collision.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Bullet/BulletManager.h"

void InitPlayScene()
{
	// プレイヤー初期化
	InitPlayer();

	// マップ初期化
	InitMap();

	// カメラ初期化
	InitCamera();

	// エネミー初期化
	InitEnemy();

	// 弾丸初期化
	InitBullet();
}

void LoadPlayScene()
{
	// プレイヤーロード
	LoadPlayer();

	// マップをロード
	LoadMap();

	// エネミーをロード
	LoadEnemy();

	// 弾丸をロード
	LoadBullet();
}

void StartPlayScene()
{
	// プレイヤー開始
	StartPlayer();

	// マップを開始
	StartMap();

	// エネミーを開始
	StartEnemy();
}

void StepPlayScene()
{
	// マップステップ
	StepMap();

	// プレイヤーステップ
	StepPlayer();

	// エネミーステップ
	StepEnemy();

	// 弾丸ステップ
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

	// 弾丸更新
	UpdateBullet();
}

void DrawPlayScene()
{
	// マップ描画
	DrawMap();

	// 弾丸描画
	DrawBullet();

	// プレイヤー描画
	DrawPlayer();

	// エネミー描画
	DrawEnemy();

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

	// 弾丸終了
	FinBullet();
}
