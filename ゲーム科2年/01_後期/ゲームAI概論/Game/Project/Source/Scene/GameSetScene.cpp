#include "DxLib.h"
#include "GameSetScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"

GameSetScene::GameSetScene() : SceneBase()
{
}

GameSetScene::~GameSetScene()
{
}

void GameSetScene::Init()
{
}

void GameSetScene::Load()
{
}

void GameSetScene::Start()
{
}

void GameSetScene::Step()
{
	// Zキーでプレイシーンへ
	if (Input::IsTriggerKey(KEY_Z))
	{
		SceneManager::GetInstance()->ChangeScene(PLAY);
	}
}

void GameSetScene::Update()
{
}

void GameSetScene::Draw()
{
	DrawString(800, 450, "！！決着！！", GetColor(255, 255, 255));
}

void GameSetScene::Fin()
{
}
