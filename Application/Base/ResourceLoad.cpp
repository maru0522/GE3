#include "ResourceLoad.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include <iostream>
#if _MSC_VER > 1922 && !defined(_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif
#include <experimental/filesystem>

void ResourceLoad::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // テクスチャ読み込み
    Texture::Load("Resources/reimu.png", "reimuSprite");
    Texture::Load("Resources/mario.jpg");
    Texture::Load("Resources/thinking.png");
    Texture::Load("Resources/a.png");

    // 3d.obj読み込み
    Model::Load("Resources/3dModels/cube/cube.obj");
    Model::Load("Resources/3dModels/sphere/sphere.obj");
}

void ResourceLoad::Update(void)
{
    sceneManager_->RequestChangeScene(SceneFactory::Type::TITLE);
}

void ResourceLoad::Draw3d(void)
{
}

void ResourceLoad::Draw2d(void)
{
}

void ResourceLoad::Finalize(void)
{
}

void ResourceLoad::LoadImageFolder(const std::experimental::filesystem::path& folderPath)
{
    for (const std::experimental::filesystem::directory_entry& file : std::experimental::filesystem::directory_iterator(folderPath)) {
        std::experimental::filesystem::path fileName{ file.path().filename().string() };

        if (file.path().extension() == ".png" ||
            file.path().extension() == ".jpg" ||
            file.path().extension() == ".jpeg") {
            Texture::Load(folderPath / fileName);
        }
    }
}
