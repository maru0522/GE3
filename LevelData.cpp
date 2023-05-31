#include "LevelData.h"
#include <fstream>
#include <cassert>
#include "json.hpp"

LevelData* LevelData::Load(const std::string& path)
{
    std::ifstream ifs;
    ifs.open(path);
    assert(!ifs.fail());

    // json文字列のデータ
    nlohmann::json deserialized;

    // 解凍
    ifs >> deserialized;

    // 正しいレベルデータファイルかチェック
    assert(deserialized.is_object());
    assert(deserialized.contains("name"));
    assert(deserialized["name"].is_string());

    // "name"を文字列として取得
    std::string name = deserialized["name"].get<std::string>();
    // 正しいレベルデータファイルかチェック
    assert(name.compare("scene") == 0);

    // レベルデータ格納用インスタンス生成
    LevelData* levelData = new LevelData();

    // objectsの全オブジェクトを走査
    for (nlohmann::json& object : deserialized["objects"]) {
        ScanRecursive(object, levelData);

        // 再起呼出で枝を走査する
        for (nlohmann::json& child : object["children"])
        {
            ScanRecursive(child, levelData);
        }
    }

    return levelData;
}

void LevelData::ScanRecursive(nlohmann::json& jsonObject, LevelData* levelDataPtr)
{
    assert(jsonObject.contains("type"));

    // 種別を取得
    std::string type = jsonObject["type"].get<std::string>();

    // MESH
    if (type.compare("MESH") == 0) {
        // 要素追加
        levelDataPtr->objects_.emplace_back(LevelData::ObjectData_t{});
        // 今追加した要素の参照を得る
        LevelData::ObjectData_t& objectData = levelDataPtr->objects_.back();

        if (jsonObject.contains("file_name")) {
            // ファイル名
            objectData.name_ = jsonObject["file_name"];
        }

        // トランスフォームのパラメータ読み込み
        nlohmann::json& transform = jsonObject["transform"];

        // 平行移動
        objectData.trans_.x = (float)transform["translation"][1];
        objectData.trans_.y = (float)transform["translation"][2];
        objectData.trans_.z = -(float)transform["translation"][0];

        // 回転角
        objectData.rot_.x = -(float)transform["rotation"][1];
        objectData.rot_.y = -(float)transform["rotation"][2];
        objectData.rot_.z = (float)transform["rotation"][0];

        // スケーリング
        objectData.scale_.x = (float)transform["scaling"][1];
        objectData.scale_.y = (float)transform["scaling"][2];
        objectData.scale_.z = (float)transform["scaling"][0];
    }
}
