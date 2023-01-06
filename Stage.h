#pragma once
#include <string>
#include <array>
#include <memory>
#include "Sprite.h"
#include "Block.h"

class Stage
{
private: // 定数
    static constexpr uint32_t lengthX_{ 100 };
    static constexpr uint32_t lengthY_{ 100 };
    static constexpr uint32_t lengthZ_{ 100 };

    // 定義
    union Field
    {
        std::array<std::array<int32_t, lengthY_>, lengthX_> field2d_;
        std::array<std::array<std::array<int32_t, lengthZ_>, lengthY_>, lengthX_> field3d_;
    };

public: // 関数
    void LoadStage(const std::string& csv);

    void Draw(void);

private: // 変数
    Field fieldArray_{};
    Dimension state_{ Dimension::TWO };

    std::array<std::unique_ptr<Sprite>, 100> terrainBlocks2d_{};
    std::array<std::unique_ptr<Sprite>, 100> dirtBlocks2d_{};
};