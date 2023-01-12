#include "ResourceLoad.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"

void ResourceLoad::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // テクスチャ読み込み
    Texture::Load("Resources/Image/Title/Wii - Super Paper Mario - Wii Menu Banner & Save Data Graphics.png", "title_atlas");
    Texture::Load("Resources/Image/Title/frame.png", "titleFrame");
    Texture::Load("Resources/Image/Chapter1/Wii - Super Paper Mario - The Adventure Unfolds.png", "chapter1_atlas");
    Texture::Load("Resources/Image/Chapter1/grass.png", "chapter1_grass");
    Texture::Load("Resources/Image/Chapter1/dirt.png", "chapter1_dirt");
    Texture::Load("Resources/mario.jpg");
    Texture::Load("Resources/thinking.png");
    Texture::Load("Resources/Image/Chapter1/BrickBlock.png", "chapter1_brick");
    Texture::Load("Resources/Image/Chapter1/EmptyBlock.png", "chapter1_empty");
    Texture::Load("Resources/Image/Chapter1/QuestionBlock.png", "chapter1_question");
    Texture::Load("Resources/Image/Chapter1/grass_surface.png", "chapter1_grassSurface");
    Texture::Load("Resources/Image/Chapter1/goal.png", "chapter1_goal");
    Texture::Load("Resources/Image/Chapter1/sprite_goal.png", "chapter1_clear");
    Texture::Load("Resources/Image/Chapter1/plastic.png", "chapter1_plastic");
    Texture::Load("Resources/Image/Chapter1/mario.png", "main");
    Texture::Load("Resources/Image/Chapter1/mario2.png", "main2");


    // 3d.obj読み込み
    Model::Load("Resources/3dModels/cube/cube.obj");
    Model::Load("Resources/3dModels/greenPipe/GreenPipe.obj");
}

void ResourceLoad::Update(void)
{
    std::unique_ptr<BaseScene> nextScene{ sceneManager_->CreateScene("TITLE") };
    sceneManager_->RequestChangeScene(nextScene);
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
