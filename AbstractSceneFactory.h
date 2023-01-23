#pragma once
#include "BaseScene.h"
#include <string>
#include <memory>

class AbstractSceneFactory
{
public:
    // ’è‹`
    enum class Type
    {
        TITLE,
        PLAYGAME,
        END,
    };


    virtual ~AbstractSceneFactory(void) = default;

    virtual std::unique_ptr<BaseScene> CreateScene(Type sceneType) = 0;
};

