#include "TitleScene.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"
#include "SceneManager.h"
#include "GameScene.h"

void TitleScene::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // 変数初期化
    cameraT_ = std::make_unique<Camera>();

#pragma region タイトル画面素材
    // タイトル背景
    for (size_t i = 0; i < sprite_titleBackGrounds_.size(); i++) {
        sprite_titleBackGrounds_.at(i) = std::make_unique<Sprite>("title_atlas", CMode::ID);
        sprite_titleBackGrounds_.at(i)->SetSize({ 256,640 });
        sprite_titleBackGrounds_.at(i)->SetCutStartPoint({ 6,215 });
        sprite_titleBackGrounds_.at(i)->SetCutLength({ 128,320 });
        sprite_titleBackGrounds_.at(i)->SetPosition({ 253.0f * i,0.0f });
    }

    // タイトル背景アイテム
    for (size_t i = 0; i < sprite_titleBackPieces_.size(); i++) {
        sprite_titleBackPieces_.at(i) = std::make_unique<Sprite>("title_atlas", CMode::ID);
        sprite_titleBackPieces_.at(i)->SetSize({510,220});
        sprite_titleBackPieces_.at(i)->SetCutStartPoint({ 143,296 });
        sprite_titleBackPieces_.at(i)->SetCutLength({ 255.9f,110 });
        sprite_titleBackPieces_.at(i)->SetPosition({ 507.0f * i - 158, 280 });
    }

    // タイトルブロック
    for (size_t i = 0; i < sprite_titleBlocks_.size(); i++) {
        sprite_titleBlocks_.at(i) = std::make_unique<Sprite>("title_atlas", CMode::ID);
        sprite_titleBlocks_.at(i)->SetSize({ 64,64 });
        sprite_titleBlocks_.at(i)->SetCutStartPoint({ 5,546 });
        sprite_titleBlocks_.at(i)->SetCutLength({ 64,64 });
        sprite_titleBlocks_.at(i)->SetPosition({ 64.0f * i, 490 });
    }

    // タイトル木
    sprite_titleTree_->SetSize({320,330});
    sprite_titleTree_->SetCutStartPoint({ 408,243 });
    sprite_titleTree_->SetCutLength({ 126,163 });
    sprite_titleTree_->SetPosition({ 780,160 });

    // タイトルロゴ
    sprite_titleLogo_->SetSize({ 531,232.5f });
    sprite_titleLogo_->SetCutStartPoint({ 550,241 });
    sprite_titleLogo_->SetCutLength({ 354,155 });
    sprite_titleLogo_->SetPosition({ 374.5f,60 });

    // タイトルフレーム
    sprite_titleFrame_ = std::make_unique<Sprite>("titleFrame", CMode::ID);
#pragma endregion
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

    for (size_t i = 0; i < sprite_titleBackGrounds_.size(); i++) {
        sprite_titleBackGrounds_.at(i)->Update();
    }
    for (size_t i = 0; i < sprite_titleBackPieces_.size(); i++) {
        sprite_titleBackPieces_.at(i)->Update();
    }
    for (size_t i = 0; i < sprite_titleBlocks_.size(); i++) {
        sprite_titleBlocks_.at(i)->Update();
    }
    sprite_titleTree_->Update();
    sprite_titleLogo_->Update();
    sprite_titleFrame_->Update();

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
    for (size_t i = 0; i < sprite_titleBackGrounds_.size(); i++) {
        sprite_titleBackGrounds_.at(i)->Draw();
    }
    for (size_t i = 0; i < sprite_titleBackPieces_.size(); i++) {
        sprite_titleBackPieces_.at(i)->Draw();
    }
    for (size_t i = 0; i < sprite_titleBlocks_.size(); i++) {
        sprite_titleBlocks_.at(i)->Draw();
    }
    sprite_titleTree_->Draw();
    sprite_titleLogo_->Draw();
    sprite_titleFrame_->Draw();

}

void TitleScene::Finalize(void)
{
}
