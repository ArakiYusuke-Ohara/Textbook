#pragma once
#include "DxLib.h"
#include "../Library/json/json.hpp"
#include <string>

// Unityが出力したjsonデータ
// 必ずUnityに合わせること
struct MappingData 
{
    int id = -1;
    VECTOR pos = {};
    VECTOR rot = {};
    VECTOR scale = {};
    std::string name = "";
};

// Unityが出力する配置オブジェクトID
// 必ずUnityに合わせること
enum LcateObjectID
{
    // Player
    PLAYER,
    // Grass
    GRASS,
};

// jsonにあるTransformをDxLibのVECTORに変換
inline void jsonConvXYZ(const nlohmann::json& j, VECTOR& v)
{
    v.x = j.value("x", 0.0f);
    v.y = j.value("y", 0.0f);
    v.z = j.value("z", 0.0f);
}

// jsonにあるオブジェクトデータをGameObject構造体に格納するために必要
inline void from_json(const nlohmann::json& j, MappingData& obj)
{
    obj.id = j.value("id", 0);
    obj.name = j.value("name", "");
    jsonConvXYZ(j.at("position"), obj.pos);
    jsonConvXYZ(j.at("rotation"), obj.rot);
    jsonConvXYZ(j.at("scale"), obj.scale);
}
