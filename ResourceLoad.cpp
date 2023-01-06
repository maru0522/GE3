#include "ResourceLoad.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"

void ResourceLoad::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // �e�N�X�`���ǂݍ���
    Texture::Load("Resources/Image/Title/Wii - Super Paper Mario - Wii Menu Banner & Save Data Graphics.png", "title_atlas");
    Texture::Load("Resources/Image/Title/frame.png", "titleFrame");
    Texture::Load("Resources/Image/Chapter1/Wii - Super Paper Mario - The Adventure Unfolds.png", "chapter1_atlas");
    Texture::Load("Resources/Image/Chapter1/grass.png", "chapter1_grass");
    Texture::Load("Resources/Image/Chapter1/dirt.png", "chapter1_dirt");
    Texture::Load("Resources/mario.jpg");
    Texture::Load("Resources/thinking.png");

    // 3d.obj�ǂݍ���
    Model::Load("Resources/3dModels/cube/cube.obj");
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
