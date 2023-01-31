#include "GameScene.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"

void GameScene::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // �ϐ�������
    cameraT_ = std::make_unique<Camera>();
    spriteT_ = std::make_unique<Sprite>("Resources/reimu.png", CMode::PATH);
    objT_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", cameraT_.get());

    for (size_t i = 0; i < obj_.size(); i++) {
        obj_[i] = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", cameraT_.get());
        obj_[i]->worldCoordinate_.position_ = {i * 2.0f, 0.0f,0.0f};
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

    if (KEYS::IsTrigger(DIK_SPACE)) {
        cameraT_->SwitchProjection();
    }


    if (KEYS::IsDown(DIK_LEFTARROW)) {
        objT_->worldCoordinate_.position_.x -= 2;
    }
    if (KEYS::IsDown(DIK_RIGHTARROW)) {
        objT_->worldCoordinate_.position_.x += 2;
    }

    spriteT_->Update();
    objT_->Update();

    for (size_t i = 0; i < obj_.size(); i++) {
        obj_[i]->Update();
    }
}

void GameScene::Draw3d(void)
{
    objT_->Draw();
    for (size_t i = 0; i < obj_.size(); i++) {
        obj_[i]->Draw();
    }
}

void GameScene::Draw2d(void)
{
    spriteT_->Draw();
}

void GameScene::Finalize(void)
{
}