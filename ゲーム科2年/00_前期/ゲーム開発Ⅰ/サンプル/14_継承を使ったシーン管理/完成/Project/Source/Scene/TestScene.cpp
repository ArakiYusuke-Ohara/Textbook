#include "DxLib.h"
#include "TestScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"

TestScene::TestScene() : SceneBase()
{
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
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
	if (Input::IsTriggerKey(Input::KEY_Z))
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
}

void TestScene::Fin()
{
}
