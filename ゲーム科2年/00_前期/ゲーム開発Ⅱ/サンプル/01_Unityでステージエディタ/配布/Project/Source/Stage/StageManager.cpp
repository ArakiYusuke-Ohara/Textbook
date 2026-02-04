#include "StageManager.h"
#include "StageParameter.h"
#include "../StageObject/StageObjectManager.h"
#include "../Player/PlayerManager.h"
#include "../Enemy/EnemyManager.h"
#include <fstream>

StageManager* StageManager::m_Instance = nullptr;

// usingして使いやすくする

// データがまとまっている階層のキー名


StageManager::StageManager()
{
}

StageManager::~StageManager()
{
    Fin();
}

void StageManager::Load(const char* fileName)
{

}

/// <summary>
/// ステージ開始処理
/// 主に各オブジェクトを配置する
/// </summary>
void StageManager::Start()
{
}

void StageManager::Draw()
{
}

void StageManager::Fin()
{

}
