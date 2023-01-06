#include "GameScene.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"
#include "Block2d.h"

void GameScene::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // 変数初期化
    cameraT_ = std::make_unique<Camera>();

    spriteT_ = std::make_unique<Sprite>("a", CMode::PATH);

    // 地面ブロック2d-草
    for (size_t i = 0; i < terrainBlocks2d_.size(); i++) {
        const DirectX::XMFLOAT2 length{ 48,32 };
        terrainBlocks2d_[i] = std::make_unique<Block2d>(AbstractBlock::Type::GRASS, length);
        terrainBlocks2d_[i]->square_->SetPosition({ 48.0f * i,592.0f });
    }
    // 地面ブロック2d-土
    for (size_t i = 0; i < dirtBlocks2d_.size(); i++) {
        dirtBlocks2d_[i] = std::make_unique<Block2d>(AbstractBlock::Type::DIRT);
        dirtBlocks2d_[i]->square_->SetPosition({ 64.0f * i,624.0f });
    }

    // 地面ブロック3d
    for (size_t i = 0; i < terrainBlocks3d_.size(); i++) {
        terrainBlocks3d_[i] = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", cameraT_.get());
        terrainBlocks3d_[i]->SetTexture("Resources/thinking.png");
        terrainBlocks3d_[i]->worldCoordinate_.position_.x = i % 2 ? i - 1.0f : i;
        terrainBlocks3d_[i]->worldCoordinate_.position_.z = i % 2 ? 2.0f : 0.0f;
    }
}

void GameScene::Update(void)
{
    cameraT_->Update();

    spriteT_->Update();

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

    // 地面ブロック2d-草
    for (size_t i = 0; i < terrainBlocks2d_.size(); i++) {
        terrainBlocks2d_[i]->Update();
    }
    // 地面ブロック2d-土
    for (size_t i = 0; i < dirtBlocks2d_.size(); i++) {
        dirtBlocks2d_[i]->Update();
    }

    // 地面ブロック3d
    for (size_t i = 0; i < terrainBlocks3d_.size(); i++) {
        terrainBlocks3d_[i]->Update();
    }
}

void GameScene::Draw3d(void)
{
    // 地面ブロック3d
    for (size_t i = 0; i < terrainBlocks3d_.size(); i++) {
        terrainBlocks3d_[i]->Draw();
    }
}

void GameScene::Draw2d(void)
{
    spriteT_->Draw();

    // 地面ブロック2d-土
    for (size_t i = 0; i < dirtBlocks2d_.size(); i++) {
        dirtBlocks2d_[i]->Draw();
    }
    // 地面ブロック2d-草
    for (size_t i = 0; i < terrainBlocks2d_.size(); i++) {
        terrainBlocks2d_[i]->Draw();
    }
}

void GameScene::Finalize(void)
{
}
