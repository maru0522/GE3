#pragma once
#include <memory>
#include "Sprite.h"
#include "Obj3d.h"

class AbstractBlock
{
public: // �萔
    static constexpr uint32_t lengthX_{ 64 };
    static constexpr uint32_t lengthY_{ 64 };
    static constexpr uint32_t lengthZ_{ 64 };

    // ��`
    enum class Type
    {
        NONE,
        GRASS,
        GRASS_SURFACE,
        DIRT,
        BRICK,
        QUESTION,
        EMPTY,
        PLASTIC,
        PIPE,
        GOAL,
    };

    // �֐�
    virtual ~AbstractBlock(void) = default;

    virtual void Update(void) = 0;
    virtual void Draw(void) = 0;
};