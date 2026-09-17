#include "MapManager.h"
#include "MapParameter.h"
#include "../Player/PlayerManager.h"
#include <fstream>

MapManager* MapManager::m_Instance = nullptr;

// usingして使いやすくする
using json = nlohmann::json;

// データがまとまっている階層のキー名
constexpr const char* KEY_ITEMS = "items";

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
    Fin();
}

void MapManager::Load(const char* fileName)
{
    // jsonファイルを開く
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return;
    }

    // 開いたjsonファイルをjsonクラスに取り込み
    json stageJson;
    file >> stageJson;

    // from_json関数を元にjsonをvectorに格納
    m_MappingData = stageJson[KEY_ITEMS].get<std::vector<MappingData>>();

    // ファイルを閉じる
    file.close();
}

/// <summary>
/// ステージ開始処理
/// 主に各オブジェクトを配置する
/// </summary>
void MapManager::Start()
{
    // jsonデータを元に配置
    for (MappingData obj : m_MappingData)
    {
    }
}

void MapManager::Draw()
{
}

void MapManager::Fin()
{

}
