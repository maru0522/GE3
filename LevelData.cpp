#include "LevelData.h"
#include <fstream>
#include <cassert>
#include "json.hpp"

LevelData* LevelData::Load(const std::string& path)
{
    std::ifstream ifs;
    ifs.open(path);
    assert(!ifs.fail());

    // json������̃f�[�^
    nlohmann::json deserialized;

    // ��
    ifs >> deserialized;

    // ���������x���f�[�^�t�@�C�����`�F�b�N
    assert(deserialized.is_object());
    assert(deserialized.contains("name"));
    assert(deserialized["name"].is_string());

    // "name"�𕶎���Ƃ��Ď擾
    std::string name = deserialized["name"].get<std::string>();
    // ���������x���f�[�^�t�@�C�����`�F�b�N
    assert(name.compare("scene") == 0);

    // ���x���f�[�^�i�[�p�C���X�^���X����
    LevelData* levelData = new LevelData();

    // objects�̑S�I�u�W�F�N�g�𑖍�
    for (nlohmann::json& object : deserialized["objects"]) {
        ScanRecursive(object, levelData);

        // �ċN�ďo�Ŏ}�𑖍�����
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

    // ��ʂ��擾
    std::string type = jsonObject["type"].get<std::string>();

    // MESH
    if (type.compare("MESH") == 0) {
        // �v�f�ǉ�
        levelDataPtr->objects_.emplace_back(LevelData::ObjectData_t{});
        // ���ǉ������v�f�̎Q�Ƃ𓾂�
        LevelData::ObjectData_t& objectData = levelDataPtr->objects_.back();

        if (jsonObject.contains("file_name")) {
            // �t�@�C����
            objectData.name_ = jsonObject["file_name"];
        }

        // �g�����X�t�H�[���̃p�����[�^�ǂݍ���
        nlohmann::json& transform = jsonObject["transform"];

        // ���s�ړ�
        objectData.trans_.x = (float)transform["translation"][1];
        objectData.trans_.y = (float)transform["translation"][2];
        objectData.trans_.z = -(float)transform["translation"][0];

        // ��]�p
        objectData.rot_.x = -(float)transform["rotation"][1];
        objectData.rot_.y = -(float)transform["rotation"][2];
        objectData.rot_.z = (float)transform["rotation"][0];

        // �X�P�[�����O
        objectData.scale_.x = (float)transform["scaling"][1];
        objectData.scale_.y = (float)transform["scaling"][2];
        objectData.scale_.z = (float)transform["scaling"][0];
    }
}
