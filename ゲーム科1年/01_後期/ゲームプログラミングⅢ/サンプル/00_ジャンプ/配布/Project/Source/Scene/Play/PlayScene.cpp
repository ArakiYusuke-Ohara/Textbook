#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/MapManager.h"
#include "../../Player/Player.h"
#include "../../Collision/Collision.h"


// 背景のスピード
#define BACK_GROUND_SPEED (-1.5f)

void InitPlayScene()
{
	// プレイヤー初期化
	InitPlayer();

	// マップ初期化
	InitMap();
}

void LoadPlayScene()
{
	// プレイヤーロード
	LoadPlayer();

	// マップをロード
	LoadMap();
}

void StartPlayScene()
{
	// プレイヤー開始
	StartPlayer();

	// マップを開始
	StartMap();
}

void StepPlayScene()
{
	// プレイヤーステップ
	StepPlayer();
}

void UpdatePlayScene()
{
	// マップ更新
	// プレイヤー更新
	UpdatePlayer();

	// 当たり判定
	CheckCollision();
}

void DrawPlayScene()
{
	// マップ描画
	DrawMap();

	// プレイヤー描画
	DrawPlayer();
}

void FinPlayScene()
{
	// マップ終了
	FinMap();

	// プレイヤー終了
	FinPlayer();
}
