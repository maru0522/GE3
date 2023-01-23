#include "SceneFactory.h"

std::unique_ptr<BaseScene> SceneFactory::CreateScene(Type sceneType)
{
    std::unique_ptr<BaseScene> newScene{ nullptr };

    switch (sceneType)
    {
    case AbstractSceneFactory::Type::TITLE:
        newScene = std::make_unique<TitleScene>();
        break;

    case AbstractSceneFactory::Type::PLAYGAME:
        newScene = std::make_unique<GameScene>();
        break;

    case AbstractSceneFactory::Type::END:
        break;

    default:
        newScene = std::make_unique<TitleScene>();
        break;
    }

    return std::move(newScene);
}
