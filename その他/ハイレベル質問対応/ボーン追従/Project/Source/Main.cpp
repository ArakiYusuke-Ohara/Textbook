#include "DxLib.h"
#include "Player/PlayerManager.h"
#include "Camera/CameraManager.h"
#include "Block/BlockManager.h"
#include "Goal/GoalManager.h"
#include "Collision/CollisionManager.h"
#include "Enemy/EnemyManager.h"
#include "Scene/SceneManager.h"
#include "Input/Input.h"
#include "FPS/FPS.h"
#include "Floor/Floor.h"
#include "MyMath/MyMath.h"
#include "MyEffekseer/EffekseerManager.h"
#include "Animation/Animation.h"
#include "Memory/Memory.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

MATRIX GetBoneWorldMatrix(int modelHandle, int frameIndex);

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	// Effekseerセットアップ
	EffekseerManager::CreateInstence();
	EffekseerManager::GetInstance()->Setup();

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// シーンマネージャー生成
	SceneManager::CreateInstance();
	// シーン初期化
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Init();

	// 入力初期化
	Input::Init();

	// FPS初期化
	FPSSystem::Init();

	int cubeHandleA = MV1LoadModel("Data/Cube.x");
	int cubeHandleB = MV1LoadModel("Data/Cube.x");

	int animHandle = MV1LoadModel("Data/Animation.x");
	UniquePtr<Animation> anim = MakeUnique<Animation>(animHandle);
	anim->Play(0, 0.5f, true);

	int bone003Index = MV1SearchFrame(animHandle, "Bone.003");
	int bone004Index = MV1SearchFrame(animHandle, "Bone.004");

	VECTOR animPos = VGet(-5.0f, 0.0f, 0.0f);

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 1ミリ秒待機すると処理が安定する
		Sleep(1);

		// 画面をクリア
		ClearDrawScreen();

		// 入力更新
		Input::Update();

		// シーンを更新
		sceneManager->Update();

		animPos = MyMath::VecAdd(animPos, VGet(0.01f, 0.01f, 0.01f));

		MV1SetPosition(animHandle, animPos);

		anim->Update();

		DrawSphere3D(animPos, 0.5f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);

		MATRIX worldMat = GetBoneWorldMatrix(animHandle, bone003Index);
		MATRIX modelMat = MV1GetMatrix(animHandle);
		MATRIX result = MyMath::MatMult(worldMat, modelMat);

		MV1SetMatrix(cubeHandleA, result);
		MV1DrawModel(cubeHandleA);

		worldMat = GetBoneWorldMatrix(animHandle, bone004Index);
		result = MyMath::MatMult(worldMat, modelMat);
		MV1SetMatrix(cubeHandleB, result);
		MV1DrawModel(cubeHandleB);

		// 入力描画
		Input::Draw();

		// FPS更新
		FPSSystem::Update();
		// FPS描画
		FPSSystem::Draw();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 1フレームが速すぎた場合の待機
		FPSSystem::WaitFPS();

		// 画面フリップ
		ScreenFlip();
	}

	// シーンマネージャー削除
	SceneManager::DeleteInstance();

	// Effekseer削除
	EffekseerManager::DeleteInstance();

	// 入力終了
	Input::Fin();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

MATRIX GetBoneWorldMatrix(int modelHandle, int frameIndex)
{
	MATRIX local = MV1GetFrameLocalMatrix(modelHandle, frameIndex);
	int parent = MV1GetFrameParent(modelHandle, frameIndex);

	if (parent == -1)
	{
		// 親なし＝ルートボーン
		return local;
	}
	else
	{
		MATRIX parentMat = GetBoneWorldMatrix(modelHandle, parent);
		return MMult(local, parentMat); // 親×自分
	}
}