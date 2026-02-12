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
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
	DrawString(0, 0, "テストシーン", GetColor(255, 255, 255));
}

void TestScene::Fin()
{
	// Zバッファーは非常に重いので、
	// 必要な時だけONにしておきたい

	// Zバッファーを無効にする
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);
}
