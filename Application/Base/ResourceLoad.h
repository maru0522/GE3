#pragma once
#include <memory>
#include "Camera.h"
#include "Sprite.h"
#include "Obj3d.h"
#include "BaseScene.h"

class ResourceLoad :
    public BaseScene
{
public: // ä÷êî
    void Initialize(SceneManager* pSceneManager) override;
    void Update(void) override;
    void Draw3d(void) override;
    void Draw2d(void) override;
    void Finalize(void) override;

    void LoadImageFolder(const std::experimental::filesystem::path& folderPath);
};

