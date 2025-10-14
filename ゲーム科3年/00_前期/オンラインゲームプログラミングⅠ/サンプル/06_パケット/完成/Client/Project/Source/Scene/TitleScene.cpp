#include "TitleScene.h"
#include "../Input/Input.h"
#include "SceneManager.h"
#include "DxLib.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::Load()
{
}

void TitleScene::Start()
{
}

void TitleScene::Step()
{
	if (Input::IsTriggerKey(KEY_Z))
	{
		SceneManager::GetInstance()->ChangeScene(ONLINE_PLAY);
	}
	else if (Input::IsTriggerKey(KEY_X))
	{
		SceneManager::GetInstance()->ChangeScene(PLAY);
	}
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Zキーでオンラインプレイ");
	DrawFormatString(0, 20, GetColor(255, 255, 255),"Xキーでオフラインプレイ");
}

void TitleScene::Fin()
{
}
