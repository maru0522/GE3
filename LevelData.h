#pragma once
#include <string>
#include "Model.h"
#include <DirectXMath.h>
#include "json.hpp"


class LevelData
{
public:
    static LevelData* Load(const std::string& path);
    static void ScanRecursive(nlohmann::json& jsonObject, LevelData* levelDataPtr);
    struct ObjectData_t
    {
        std::string name_;
        DirectX::XMFLOAT3 trans_;
        DirectX::XMFLOAT3 scale_;
        DirectX::XMFLOAT3 rot_;
        DirectX::XMMATRIX matWorld_;
    };

    std::list<ObjectData_t> objects_;
    std::map<std::string, Model> models_;
};

