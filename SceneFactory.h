#pragma once
#include "AbstractSceneFactory.h"
#include <memory>
#include "TitleScene.h"
#include "GameScene.h"

class SceneFactory :
    public AbstractSceneFactory
{
public:
    std::unique_ptr<BaseScene> CreateScene(Type sceneType) override;
};

