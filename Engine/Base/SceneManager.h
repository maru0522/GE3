#pragma once
#include <memory>
#include "BaseScene.h"
#include "AbstractSceneFactory.h"
#include "SceneFactory.h"

using std::unique_ptr;

class SceneManager
{
public: 
    // ä÷êî
    ~SceneManager(void);

    std::unique_ptr<BaseScene> CreateScene(AbstractSceneFactory::Type type);
    void RequestChangeScene(AbstractSceneFactory::Type type);
    void RequestChangeScene(std::unique_ptr<BaseScene>& scene);

    void Update(void);
    void Draw3d(void);
    void Draw2d(void);
    void Finalize(void);

private:
    // ïœêî
    unique_ptr<BaseScene> currentScene_{ nullptr };
    unique_ptr<BaseScene> nextScene_{ nullptr };
    unique_ptr<AbstractSceneFactory> sceneFactory_{ std::make_unique<SceneFactory>() };
};