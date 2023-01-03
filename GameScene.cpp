#include "GameScene.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"

void GameScene::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // 変数初期化
    cameraT_ = std::make_unique<Camera>();

    // 地面ブロック
    for (size_t i = 0; i < terrainBlocks_.size(); i++) {
        terrainBlocks_[i] = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", cameraT_.get());
        terrainBlocks_[i]->SetTexture("Resources/thinking.png");
        terrainBlocks_[i]->worldCoordinate_.position_.x = i % 2 ? i - 1.0f : i;
        terrainBlocks_[i]->worldCoordinate_.position_.z = i % 2 ? 2.0f : 0.0f;
    }
}

void GameScene::Update(void)
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
    if (KEYS::IsDown(DIK_UPARROW)) {
        cameraT_->eye_.y += 5;
    }
    if (KEYS::IsDown(DIK_DOWNARROW)) {
        cameraT_->eye_.y -= 5;
    }
    if (KEYS::IsTrigger(DIK_SPACE)) {
        if (cameraT_->GetProjectionState()) {
            cameraT_->SetProjection(CameraProjection::ORTHOGRAPHIC);
        }
        else {
            cameraT_->SetProjection(CameraProjection::PERSPECTIVE);
        }
    }

    // 地面ブロック
    for (size_t i = 0; i < terrainBlocks_.size(); i++) {
        terrainBlocks_[i]->Update();
    }
}

void GameScene::Draw3d(void)
{
    // 地面ブロック
    for (size_t i = 0; i < terrainBlocks_.size(); i++) {
        terrainBlocks_[i]->Draw();
    }
}

void GameScene::Draw2d(void)
{
}

void GameScene::Finalize(void)
{
}
