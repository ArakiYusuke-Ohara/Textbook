#include "DxLib.h"
#include "TestScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"

TestScene::TestScene() : SceneBase()
{
}

TestScene::~TestScene()
{
	Fin();
}

void TestScene::Init()
{
	// 適当にカメラを設定
	SetCameraNearFar(0.1f, 1000.0f);
	SetCameraPositionAndTargetAndUpVec(VGet(10.0f, 0.0f, -30.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));

	// Zバッファーを有効にする
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
}

void TestScene::Load()
{
}

void TestScene::Start()
{
}

void TestScene::Step()
{
	// Zキーでタイトルシーンへ
	if (Input::IsTriggerKey(KEY_Z))
	{
		SceneManager::GetInstance()->ChangeScene(TITLE);
	}
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
	DrawString(0, 0, "テストシーン", GetColor(255, 255, 255));

	// 3Dの三角形を2つめり込むように表示
	VECTOR vertexA[3] =
	{
		{-10.0f,  10.0f, -5.0f},
		{ 10.0f,  10.0f, -5.0f},
		{  5.0f, -10.0f, -5.0f},
	};

	VECTOR vertexB[3] =
	{
		{-10.0f, -10.0f,  10.0f},
		{ 10.0f, -10.0f,  10.0f},
		{  5.0f,  10.0f, -10.0f},
	};
	DrawTriangle3D(vertexA[0], vertexA[1], vertexA[2], GetColor(255, 0, 0), TRUE);
	DrawTriangle3D(vertexB[0], vertexB[1], vertexB[2], GetColor(0, 255, 0), TRUE);
}

void TestScene::Fin()
{
	// Zバッファーは非常に重いので、
	// 必要な時だけONにしておきたい

	// Zバッファーを無効にする
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);
}
