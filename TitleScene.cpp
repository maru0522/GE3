#include "TitleScene.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"
#include "SceneManager.h"
#include "GameScene.h"

void TitleScene::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // テクスチャ読み込み
    Texture::Load("Resources/titleSprite.png","tsp");

    // 3d.obj読み込み
    Model::Load("Resources/3dModels/cube/cube.obj");

    // 変数初期化
    cameraT_ = std::make_unique<Camera>();
    spriteT_ = std::make_unique<Sprite>("tsp", CMode::ID);
}

void TitleScene::Update(void)
{
    cameraT_->Update();

    if (KEYS::IsDown(DIK_W)) {
        cameraT_->eye_.z += 5;
    }
    if (KEYS::IsDown(DIK_S)) {
        cameraT_->eye_.z -= 5;
    }
    if (KEYS::IsDown(DIK_A)) {
        cameraT_->eye_.x -= 5;
    }
    if (KEYS::IsDown(DIK_D)) {
        cameraT_->eye_.x += 5;
    }

    spriteT_->Update();

    if (KEYS::IsTrigger(DIK_RETURN)) {
        std::unique_ptr<BaseScene> nextScene{ sceneManager_->CreateScene("GAMEPLAY") };
        sceneManager_->RequestChangeScene(nextScene);
    }
}

void TitleScene::Draw3d(void)
{
}

void TitleScene::Draw2d(void)
{
    spriteT_->Draw();
}

void TitleScene::Finalize(void)
{
}
