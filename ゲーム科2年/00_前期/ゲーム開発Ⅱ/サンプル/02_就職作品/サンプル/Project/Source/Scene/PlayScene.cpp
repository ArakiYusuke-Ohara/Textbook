#include "DxLib.h"
#include "PlayScene.h"
#include "../Scene/SceneManager.h"
#include "../Block/BlockManager.h"


PlayScene::PlayScene() : SceneBase()
{

}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	// ブロック管理生成
	BlockManager::CreateInstance();
}

void PlayScene::Load()
{
	// ブロックをロード
	BlockManager::GetInstance()->Load();
}

void PlayScene::Start()
{
	BlockManager::GetInstance()->SpawnBlock(BLOCK_ID_GRASS, VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f));
}


void PlayScene::Update()
{
	// ブロック更新
	BlockManager::GetInstance()->Update();
}

void PlayScene::Fin()
{
	// ブロック管理削除
	BlockManager::DeleteInstance();
}
