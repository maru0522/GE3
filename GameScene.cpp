#include "GameScene.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"
#include "Block.h"
#include "SceneManager.h"

void GameScene::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // 変数初期化

    // 透視投影カメラ
    perspectiveCamera_ = std::make_unique<Camera>();
    perspectiveCamera_->eye_ = { 0,10,-27 };
    perspectiveCamera_->target_ = { 0,10,0 };

    mario_ = std::make_unique<Player>(perspectiveCamera_.get());
    mario_->object_->worldCoordinate_.position_.y = 20;

    const DirectX::XMFLOAT3 scale{ 1,1,1 };

    // 地面ブロック-土
    for (size_t i = 0; i < dirtBlocks_.size(); i++) {
        dirtBlocks_[i] = std::make_unique<Block>(AbstractBlock::Type::DIRT, scale, perspectiveCamera_.get());
        dirtBlocks_[i]->cube_->worldCoordinate_.position_ = { scale.x * 2 * i, 0.0f, 0 };
    }
    //dirtBlocks_[dirtBlocks_.size() - 1]->cube_->SetTexture("Resources/thinking.png");

    // 地面ブロック-草
    for (size_t i = 0; i < grassBlocks_.size(); i++) {
        grassBlocks_[i] = std::make_unique<Block>(AbstractBlock::Type::GRASS, scale, perspectiveCamera_.get());
        grassBlocks_[i]->cube_->worldCoordinate_.position_ = { scale.x * 2 * i, 2.0f, 0 };
        grassBlocks_[i]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(-90);
    }

    // 地面ブロック-草表面
    for (size_t i = 0; i < grassSurfaceBlocks_.size(); i++) {
        grassSurfaceBlocks_[i] = std::make_unique<Block>(AbstractBlock::Type::GRASS_SURFACE, scale, perspectiveCamera_.get());
        grassSurfaceBlocks_[i]->cube_->worldCoordinate_.position_ = { scale.x * 2 * i, 2.1f, 0.1f };
        grassSurfaceBlocks_[i]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(-90);
    }

    // 地面ブロック-草表面2
    for (size_t i = 0; i < grassSurfaceBlocks2_.size(); i++) {
        grassSurfaceBlocks2_[i] = std::make_unique<Block>(AbstractBlock::Type::GRASS_SURFACE, scale, perspectiveCamera_.get());
        grassSurfaceBlocks2_[i]->cube_->worldCoordinate_.position_ = { scale.x * 2 * i, 2.1f, 2.1f };
        grassSurfaceBlocks2_[i]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(-90);
    }

    // 地面ブロック-草表面3
    for (size_t i = 0; i < grassSurfaceBlocks3_.size(); i++) {
        grassSurfaceBlocks3_[i] = std::make_unique<Block>(AbstractBlock::Type::GRASS_SURFACE, scale, perspectiveCamera_.get());
        grassSurfaceBlocks3_[i]->cube_->worldCoordinate_.position_ = { scale.x * 2 * i, 2.1f, 4.1f };
        grassSurfaceBlocks3_[i]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(-90);
    }

    // はてなブロック
    for (size_t i = 0; i < questionBlocks_.size(); i++) {
        questionBlocks_[i] = std::make_unique<Block>(AbstractBlock::Type::QUESTION, scale, perspectiveCamera_.get());
        questionBlocks_[i]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(-90);
    }
    questionBlocks_[0]->cube_->worldCoordinate_.position_ = { 26.0f, 10.0f, 0.0f };
    questionBlocks_[1]->cube_->worldCoordinate_.position_ = { 36.0f, 10.0f, 0.0f };
    questionBlocks_[2]->cube_->worldCoordinate_.position_ = { 40.0f, 10.0f, 0.0f };
    questionBlocks_[3]->cube_->worldCoordinate_.position_ = { 38.0f, 18.0f, 0.0f };

    // 空ブロック
    for (size_t i = 0; i < plasticBlocks_.size(); i++) {
        plasticBlocks_[i] = std::make_unique<Block>(AbstractBlock::Type::PLASTIC, scale, perspectiveCamera_.get());
        plasticBlocks_[i]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(-90);
    }
    plasticBlocks_[1]->cube_->worldCoordinate_.position_ = { 82.0f,10.0f,0.0f };
    plasticBlocks_[2]->cube_->worldCoordinate_.position_ = { 82.0f,12.0f,0.0f };
    plasticBlocks_[3]->cube_->worldCoordinate_.position_ = { 82.0f,14.0f,0.0f };
    plasticBlocks_[4]->cube_->worldCoordinate_.position_ = { 82.0f,16.0f,0.0f };
    plasticBlocks_[5]->cube_->worldCoordinate_.position_ = { 82.0f,18.0f,0.0f };
    plasticBlocks_[6]->cube_->worldCoordinate_.position_ = { 84.0f,18.0f,0.0f };
    plasticBlocks_[7]->cube_->worldCoordinate_.position_ = { 86.0f,18.0f,0.0f };
    plasticBlocks_[8]->cube_->worldCoordinate_.position_ = { 88.0f,18.0f,0.0f };
    plasticBlocks_[9]->cube_->worldCoordinate_.position_ = { 90.0f,18.0f,0.0f };
    plasticBlocks_[10]->cube_->worldCoordinate_.position_ = { 92.0f,18.0f,0.0f };
    plasticBlocks_[11]->cube_->worldCoordinate_.position_ = { 94.0f,18.0f,0.0f };
    plasticBlocks_[12]->cube_->worldCoordinate_.position_ = { 96.0f,18.0f,0.0f };
    plasticBlocks_[13]->cube_->worldCoordinate_.position_ = { 98.0f,18.0f,0.0f };

    // レンガブロック
    for (size_t i = 0; i < brickBlocks_.size(); i++) {
        brickBlocks_[i] = std::make_unique<Block>(AbstractBlock::Type::BRICK, scale, perspectiveCamera_.get());
        brickBlocks_[i]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(-90);
    }
    brickBlocks_[0]->cube_->worldCoordinate_.position_ = { 34.0f,10.0f,0.0f };
    brickBlocks_[1]->cube_->worldCoordinate_.position_ = { 38.0f,10.0f,0.0f };
    brickBlocks_[2]->cube_->worldCoordinate_.position_ = { 42.0f,10.0f,0.0f };
    brickBlocks_[3]->cube_->worldCoordinate_.position_ = { 64.0f,10.0f,0.0f };
    brickBlocks_[4]->cube_->worldCoordinate_.position_ = { 70.0f,10.0f,0.0f };
    brickBlocks_[5]->cube_->worldCoordinate_.position_ = { 76.0f,10.0f,0.0f };

    for (size_t i = 0; i < sQBlocks_.size(); i++) {
        sQBlocks_[i] = std::make_unique<Block>(AbstractBlock::Type::BRICK, scale, perspectiveCamera_.get());
        sQBlocks_[i]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(-90);
    }
    sQBlocks_[0]->cube_->worldCoordinate_.position_ = { 18.0f, 4.0f, 4.0f };
    sQBlocks_[0]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(45);
    sQBlocks_[1]->cube_->worldCoordinate_.position_ = { 48.0f, 4.0f, 4.0f };
    sQBlocks_[1]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(45);
    sQBlocks_[2]->cube_->worldCoordinate_.position_ = { 78.0f, 4.0f, 4.0f };
    sQBlocks_[2]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(45);
    sQBlocks_[3]->cube_->worldCoordinate_.position_ = { 45.2f, 4.0f, 3.2f };
    sQBlocks_[3]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(45);
    sQBlocks_[4]->cube_->worldCoordinate_.position_ = { 78.0f, 6.0f, 4.0f };
    sQBlocks_[4]->cube_->worldCoordinate_.rotation_.y = Util::Convert::DegToRad(35); 

    const DirectX::XMFLOAT3 pipeScale{ 2.5f,2.0f,2.5f };
    pipe_ = std::make_unique<Block>(AbstractBlock::Type::PIPE, pipeScale, perspectiveCamera_.get());
    pipe_->cube_->worldCoordinate_.position_ = { 52.0f,4.0f,0.0f };

    goal_ = std::make_unique<Block>(AbstractBlock::Type::GOAL, scale, perspectiveCamera_.get());
    goal_->cube_->worldCoordinate_.position_ = { 92.0f,10.0f,1.0f };
}

void GameScene::Update(void)
{
    perspectiveCamera_->Update();
#ifdef _DEBUG
    //if (KEYS::IsDown(DIK_W)) {
    //    perspectiveCamera_->eye_.z += cameraSpeed_;
    //    perspectiveCamera_->target_.z += cameraSpeed_;
    //}
    //if (KEYS::IsDown(DIK_S)) {
    //    perspectiveCamera_->eye_.z -= cameraSpeed_;
    //    perspectiveCamera_->target_.z -= cameraSpeed_;
    //}
    //if (KEYS::IsDown(DIK_UPARROW)) {
    //    perspectiveCamera_->eye_.y += cameraSpeed_;
    //    perspectiveCamera_->target_.y += cameraSpeed_;
    //}
    //if (KEYS::IsDown(DIK_DOWNARROW)) {
    //    perspectiveCamera_->eye_.y -= cameraSpeed_;
    //    perspectiveCamera_->target_.y -= cameraSpeed_;
    //}
    //if (KEYS::IsTrigger(DIK_SPACE)) {
    //    if (perspectiveCamera_->GetProjectionState()) {
    //        perspectiveCamera_->SetProjection(CameraProjection::ORTHOGRAPHIC);
    //    }
    //    else {
    //        perspectiveCamera_->SetProjection(CameraProjection::PERSPECTIVE);
    //    }
    //}
#endif

    // 地面ブロック2d-土
    for (size_t i = 0; i < dirtBlocks_.size(); i++) {
        dirtBlocks_[i]->Update();
    }

    // 地面ブロック2d-草
    for (size_t i = 0; i < grassBlocks_.size(); i++) {
        grassBlocks_[i]->Update();
    }

    for (size_t i = 0; i < grassSurfaceBlocks_.size(); i++) {
        grassSurfaceBlocks_[i]->Update();
    }

    for (size_t i = 0; i < grassSurfaceBlocks2_.size(); i++) {
        grassSurfaceBlocks2_[i]->Update();
    }

    for (size_t i = 0; i < grassSurfaceBlocks3_.size(); i++) {
        grassSurfaceBlocks3_[i]->Update();
    }

    // はてなブロック
    for (size_t i = 0; i < questionBlocks_.size(); i++) {
        questionBlocks_[i]->Update();
    }

    // 空ブロック
    for (size_t i = 0; i < plasticBlocks_.size(); i++) {
        plasticBlocks_[i]->Update();
    }

    // レンガブロック
    for (size_t i = 0; i < brickBlocks_.size(); i++) {
        brickBlocks_[i]->Update();
    }

    for (size_t i = 0; i < sQBlocks_.size(); i++) {
        sQBlocks_[i]->Update();
    }

    pipe_->Update();

    goal_->Update();

    mario_->Update();

    // プレイヤーを常に中央に添えるため camera.x = player.x とする
    perspectiveCamera_->eye_.x = mario_->object_->worldCoordinate_.position_.x;
    perspectiveCamera_->target_.x = mario_->object_->worldCoordinate_.position_.x;

    if (mario_->object_->worldCoordinate_.position_.y >= 22.0f) {
        perspectiveCamera_->eye_.y = 22.0f;
        perspectiveCamera_->target_.y = 22.0f;
    } 
    else {
        perspectiveCamera_->eye_.y = 10.0f;
        perspectiveCamera_->target_.y = 10.0f;
    }

    if (mario_->object_->worldCoordinate_.position_.x <= 12.0f) {
        mario_->object_->worldCoordinate_.position_.x = 12.0f;
    }
    if (mario_->object_->worldCoordinate_.position_.x >= 116.0f) {
        mario_->object_->worldCoordinate_.position_.x = 116.0f;
    }

    Col();

    if (isClear_) {
        sprite_clear->Update();
        if (KEYS::IsTrigger(DIK_SPACE)) {
            std::unique_ptr<BaseScene> nextScene{ sceneManager_->CreateScene("TITLE") };
            sceneManager_->RequestChangeScene(nextScene);
        }
    }
}

void GameScene::Draw3d(void)
{
    // 地面ブロック2d-土
    for (size_t i = 0; i < dirtBlocks_.size(); i++) {
        dirtBlocks_[i]->Draw();
    }
    // 地面ブロック2d-草
    for (size_t i = 0; i < grassBlocks_.size(); i++) {
        grassBlocks_[i]->Draw();
    }

    for (size_t i = 0; i < grassSurfaceBlocks_.size(); i++) {
        grassSurfaceBlocks_[i]->Draw();
    }

    for (size_t i = 0; i < grassSurfaceBlocks2_.size(); i++) {
        grassSurfaceBlocks2_[i]->Draw();
    }

    for (size_t i = 0; i < grassSurfaceBlocks3_.size(); i++) {
        grassSurfaceBlocks3_[i]->Draw();
    }

    // はてなブロック
    for (size_t i = 0; i < questionBlocks_.size(); i++) {
        questionBlocks_[i]->Draw();
    }

    // 空ブロック
    for (size_t i = 0; i < plasticBlocks_.size(); i++) {
        plasticBlocks_[i]->Draw();
    }

    // レンガブロック
    for (size_t i = 0; i < brickBlocks_.size(); i++) {
        brickBlocks_[i]->Draw();
    }

    for (size_t i = 0; i < sQBlocks_.size(); i++) {
        sQBlocks_[i]->Draw();
    }

    pipe_->Draw();

    goal_->Draw();

    mario_->Draw();

}

void GameScene::Draw2d(void)
{
    if (isClear_) sprite_clear->Draw();
}

void GameScene::Finalize(void)
{
}

void GameScene::Col(void)
{
    // 座標修正値は重力値まで加味したほうが良いかも

    for (size_t i = 0; i < grassBlocks_.size(); i++) {
        // y軸 (pの半径 - 下) ~ (上 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
        // 重なりの問題で <= ではなく < を採用
        if (grassBlocks_[i]->cube_->worldCoordinate_.position_.y - (1.0f + Player::Radius_.y) <= mario_->object_->worldCoordinate_.position_.y &&
            mario_->object_->worldCoordinate_.position_.y <= grassBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.y)) {
            // ブロック x軸 左~中心 にプレイヤーがめり込んだ場合
            if (grassBlocks_[i]->cube_->worldCoordinate_.position_.x - 1.0f <= mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x &&
                mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x <= grassBlocks_[i]->cube_->worldCoordinate_.position_.x) {
                mario_->object_->worldCoordinate_.position_.x = grassBlocks_[i]->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x);
            }
            // ブロック x軸 中心~右 にプレイヤーがめり込んだ場合
            if (grassBlocks_[i]->cube_->worldCoordinate_.position_.x <= mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x &&
                mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x <= grassBlocks_[i]->cube_->worldCoordinate_.position_.x + 1.0f) {
                mario_->object_->worldCoordinate_.position_.y = grassBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.x);
            }
        }

        // x軸 (pの半径 - 左) ~ (右 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
        // 重なりの問題で <= ではなく < を採用
        if (grassBlocks_[i]->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x) < mario_->object_->worldCoordinate_.position_.x &&
            mario_->object_->worldCoordinate_.position_.x < grassBlocks_[i]->cube_->worldCoordinate_.position_.x + (1.0f + Player::Radius_.x)) {
            // ブロック y軸 中心~頂点 にプレイヤーがめり込んだ場合
            if (grassBlocks_[i]->cube_->worldCoordinate_.position_.y <= mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y &&
                mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y <= grassBlocks_[i]->cube_->worldCoordinate_.position_.y + 1.0f) {
                mario_->object_->worldCoordinate_.position_.y = grassBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::gravity_ + Player::Radius_.y);
                mario_->SetAirState(false);
            }
            // ブロック y軸 底~中心 にプレイヤーがめり込んだ場合
            if (grassBlocks_[i]->cube_->worldCoordinate_.position_.y - 1.0f <= mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y &&
                mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y <= grassBlocks_[i]->cube_->worldCoordinate_.position_.y) {
                mario_->object_->worldCoordinate_.position_.y = grassBlocks_[i]->cube_->worldCoordinate_.position_.y - (1.0f + Player::gravity_ + Player::Radius_.y);
                mario_->SetAirState(false);
            }
        }
    }

    for (size_t i = 0; i < questionBlocks_.size(); i++) {
        // y軸 (pの半径 - 下) ~ (上 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
        // 重なりの問題で <= ではなく < を採用
        if (questionBlocks_[i]->cube_->worldCoordinate_.position_.y - (1.0f + Player::Radius_.y) < mario_->object_->worldCoordinate_.position_.y &&
            mario_->object_->worldCoordinate_.position_.y < questionBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.y)) {
            // ブロック x軸 左~中心 にプレイヤーがめり込んだ場合
            if (questionBlocks_[i]->cube_->worldCoordinate_.position_.x - 1.0f <= mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x &&
                mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x <= questionBlocks_[i]->cube_->worldCoordinate_.position_.x) {
                mario_->object_->worldCoordinate_.position_.x = questionBlocks_[i]->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x);
            }
            // ブロック x軸 中心~右 にプレイヤーがめり込んだ場合
            if (questionBlocks_[i]->cube_->worldCoordinate_.position_.x <= mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x &&
                mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x <= questionBlocks_[i]->cube_->worldCoordinate_.position_.x + 1.0f) {
                mario_->object_->worldCoordinate_.position_.y = questionBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.x);
            }
        }

        // x軸 (pの半径 - 左) ~ (右 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
        // 重なりの問題で <= ではなく < を採用
        if (questionBlocks_[i]->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x) < mario_->object_->worldCoordinate_.position_.x &&
            mario_->object_->worldCoordinate_.position_.x < questionBlocks_[i]->cube_->worldCoordinate_.position_.x + (1.0f + Player::Radius_.x)) {
            // ブロック y軸 中心~頂点 にプレイヤーがめり込んだ場合
            if (questionBlocks_[i]->cube_->worldCoordinate_.position_.y <= mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y &&
                mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y <= questionBlocks_[i]->cube_->worldCoordinate_.position_.y + 1.0f) {
                mario_->object_->worldCoordinate_.position_.y = questionBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::gravity_ + Player::Radius_.y);
                mario_->SetAirState(false);
            }
            // ブロック y軸 底~中心 にプレイヤーがめり込んだ場合
            if (questionBlocks_[i]->cube_->worldCoordinate_.position_.y - 1.0f <= mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y &&
                mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y <= questionBlocks_[i]->cube_->worldCoordinate_.position_.y) {
                mario_->object_->worldCoordinate_.position_.y = questionBlocks_[i]->cube_->worldCoordinate_.position_.y - (1.0f + Player::gravity_ + Player::Radius_.y + 0.25f);
                mario_->SetAirState(false);
            }
        }
    }

    for (size_t i = 0; i < plasticBlocks_.size(); i++) {
        // y軸 (pの半径 - 下) ~ (上 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
        // 重なりの問題で <= ではなく < を採用
        if (plasticBlocks_[i]->cube_->worldCoordinate_.position_.y - (1.0f + Player::Radius_.y) <= mario_->object_->worldCoordinate_.position_.y &&
            mario_->object_->worldCoordinate_.position_.y <= plasticBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.y)) {
            // ブロック x軸 左~中心 にプレイヤーがめり込んだ場合
            if (plasticBlocks_[i]->cube_->worldCoordinate_.position_.x - 1.0f <= mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x &&
                mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x <= plasticBlocks_[i]->cube_->worldCoordinate_.position_.x) {
                mario_->object_->worldCoordinate_.position_.x = plasticBlocks_[i]->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x);
            }
            // ブロック x軸 中心~右 にプレイヤーがめり込んだ場合
            if (plasticBlocks_[i]->cube_->worldCoordinate_.position_.x <= mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x &&
                mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x <= plasticBlocks_[i]->cube_->worldCoordinate_.position_.x + 1.0f) {
                mario_->object_->worldCoordinate_.position_.y = plasticBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.x);
            }
        }

        // x軸 (pの半径 - 左) ~ (右 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
        // 重なりの問題で <= ではなく < を採用
        if (plasticBlocks_[i]->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x) < mario_->object_->worldCoordinate_.position_.x &&
            mario_->object_->worldCoordinate_.position_.x < plasticBlocks_[i]->cube_->worldCoordinate_.position_.x + (1.0f + Player::Radius_.x)) {
            // ブロック y軸 中心~頂点 にプレイヤーがめり込んだ場合
            if (plasticBlocks_[i]->cube_->worldCoordinate_.position_.y <= mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y &&
                mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y <= plasticBlocks_[i]->cube_->worldCoordinate_.position_.y + 1.0f) {
                mario_->object_->worldCoordinate_.position_.y = plasticBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::gravity_ + Player::Radius_.y);
                mario_->SetAirState(false);
            }
            // ブロック y軸 底~中心 にプレイヤーがめり込んだ場合
            if (plasticBlocks_[i]->cube_->worldCoordinate_.position_.y - 1.0f <= mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y &&
                mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y <= plasticBlocks_[i]->cube_->worldCoordinate_.position_.y) {
                mario_->object_->worldCoordinate_.position_.y = plasticBlocks_[i]->cube_->worldCoordinate_.position_.y - (1.0f + Player::gravity_ + Player::Radius_.y + 0.25f);
                mario_->SetAirState(false);
            }
        }
    }

    for (size_t i = 0; i < brickBlocks_.size(); i++) {
        // y軸 (pの半径 - 下) ~ (上 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
        // 重なりの問題で <= ではなく < を採用
        if (brickBlocks_[i]->cube_->worldCoordinate_.position_.y - (1.0f + Player::Radius_.y) <= mario_->object_->worldCoordinate_.position_.y &&
            mario_->object_->worldCoordinate_.position_.y <= brickBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.y)) {
            // ブロック x軸 左~中心 にプレイヤーがめり込んだ場合
            if (brickBlocks_[i]->cube_->worldCoordinate_.position_.x - 1.0f <= mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x &&
                mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x <= brickBlocks_[i]->cube_->worldCoordinate_.position_.x) {
                mario_->object_->worldCoordinate_.position_.x = brickBlocks_[i]->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x);
            }
            // ブロック x軸 中心~右 にプレイヤーがめり込んだ場合
            if (brickBlocks_[i]->cube_->worldCoordinate_.position_.x <= mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x &&
                mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x <= brickBlocks_[i]->cube_->worldCoordinate_.position_.x + 1.0f) {
                mario_->object_->worldCoordinate_.position_.y = brickBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.x);
            }
        }

        // x軸 (pの半径 - 左) ~ (右 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
        // 重なりの問題で <= ではなく < を採用
        if (brickBlocks_[i]->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x) < mario_->object_->worldCoordinate_.position_.x &&
            mario_->object_->worldCoordinate_.position_.x < brickBlocks_[i]->cube_->worldCoordinate_.position_.x + (1.0f + Player::Radius_.x)) {
            // ブロック y軸 中心~頂点 にプレイヤーがめり込んだ場合
            if (brickBlocks_[i]->cube_->worldCoordinate_.position_.y <= mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y &&
                mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y <= brickBlocks_[i]->cube_->worldCoordinate_.position_.y + 1.0f) {
                mario_->object_->worldCoordinate_.position_.y = brickBlocks_[i]->cube_->worldCoordinate_.position_.y + (1.0f + Player::gravity_ + Player::Radius_.y);
                mario_->SetAirState(false);
            }
            // ブロック y軸 底~中心 にプレイヤーがめり込んだ場合
            if (brickBlocks_[i]->cube_->worldCoordinate_.position_.y - 1.0f <= mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y &&
                mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y <= brickBlocks_[i]->cube_->worldCoordinate_.position_.y) {
                mario_->object_->worldCoordinate_.position_.y = brickBlocks_[i]->cube_->worldCoordinate_.position_.y - (1.0f + Player::gravity_ + Player::Radius_.y + 0.25f);
                mario_->SetAirState(false);
            }
        }
    }

    // y軸 (pの半径 - 下) ~ (上 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
        // 重なりの問題で <= ではなく < を採用
    if (pipe_->cube_->worldCoordinate_.position_.y - (1.0f + Player::Radius_.y) <= mario_->object_->worldCoordinate_.position_.y &&
        mario_->object_->worldCoordinate_.position_.y <= pipe_->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.y)) {
        // ブロック x軸 左~中心 にプレイヤーがめり込んだ場合
        if (pipe_->cube_->worldCoordinate_.position_.x - 1.5f <= mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x &&
            mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x <= pipe_->cube_->worldCoordinate_.position_.x) {
            mario_->object_->worldCoordinate_.position_.x = pipe_->cube_->worldCoordinate_.position_.x - (1.3f + Player::Radius_.x);
        }
        // ブロック x軸 中心~右 にプレイヤーがめり込んだ場合
        if (pipe_->cube_->worldCoordinate_.position_.x <= mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x &&
            mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x <= pipe_->cube_->worldCoordinate_.position_.x + 1.5f) {
            mario_->object_->worldCoordinate_.position_.y = pipe_->cube_->worldCoordinate_.position_.y + (1.5f + Player::Radius_.x);
        }
    }

    // x軸 (pの半径 - 左) ~ (右 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
    // 重なりの問題で <= ではなく < を採用
    if (pipe_->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x) < mario_->object_->worldCoordinate_.position_.x &&
        mario_->object_->worldCoordinate_.position_.x < pipe_->cube_->worldCoordinate_.position_.x + (0.8f + Player::Radius_.x)) {
        // ブロック y軸 中心~頂点 にプレイヤーがめり込んだ場合
        if (pipe_->cube_->worldCoordinate_.position_.y <= mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y &&
            mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y <= pipe_->cube_->worldCoordinate_.position_.y + 1.3f) {
            mario_->object_->worldCoordinate_.position_.y = pipe_->cube_->worldCoordinate_.position_.y + (1.0f + Player::gravity_ + Player::Radius_.y);
            mario_->SetAirState(false);
        }
        // ブロック y軸 底~中心 にプレイヤーがめり込んだ場合
        if (pipe_->cube_->worldCoordinate_.position_.y - 1.3f <= mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y &&
            mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y <= pipe_->cube_->worldCoordinate_.position_.y) {
            mario_->object_->worldCoordinate_.position_.y = pipe_->cube_->worldCoordinate_.position_.y - (1.0f + Player::gravity_ + Player::Radius_.y);
            mario_->SetAirState(false);
        }
    }


    // y軸 (pの半径 - 下) ~ (上 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
    // 重なりの問題で <= ではなく < を採用
    if (goal_->cube_->worldCoordinate_.position_.y - (1.0f + Player::Radius_.y) <= mario_->object_->worldCoordinate_.position_.y &&
        mario_->object_->worldCoordinate_.position_.y <= goal_->cube_->worldCoordinate_.position_.y + (1.0f + Player::Radius_.y)) {
        // ブロック x軸 左~中心 にプレイヤーがめり込んだ場合
        if (goal_->cube_->worldCoordinate_.position_.x - 1.5f <= mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x &&
            mario_->object_->worldCoordinate_.position_.x + Player::Radius_.x <= goal_->cube_->worldCoordinate_.position_.x) {
            mario_->object_->worldCoordinate_.position_.x = goal_->cube_->worldCoordinate_.position_.x - (1.3f + Player::Radius_.x);
        }
        // ブロック x軸 中心~右 にプレイヤーがめり込んだ場合
        if (goal_->cube_->worldCoordinate_.position_.x <= mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x &&
            mario_->object_->worldCoordinate_.position_.x - Player::Radius_.x <= goal_->cube_->worldCoordinate_.position_.x + 1.5f) {
            mario_->object_->worldCoordinate_.position_.y = goal_->cube_->worldCoordinate_.position_.y + (1.5f + Player::Radius_.x);
        }
    }

    // x軸 (pの半径 - 左) ~ (右 + pの半径) | ※ 中央 - (blockの半径 + pの半径) ~ 中央 + (blockの半径 + pの半径)
    // 重なりの問題で <= ではなく < を採用
    if (goal_->cube_->worldCoordinate_.position_.x - (1.0f + Player::Radius_.x) < mario_->object_->worldCoordinate_.position_.x &&
        mario_->object_->worldCoordinate_.position_.x < goal_->cube_->worldCoordinate_.position_.x + (0.8f + Player::Radius_.x)) {
        // ブロック y軸 中心~頂点 にプレイヤーがめり込んだ場合
        if (goal_->cube_->worldCoordinate_.position_.y <= mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y &&
            mario_->object_->worldCoordinate_.position_.y - Player::Radius_.y <= goal_->cube_->worldCoordinate_.position_.y + 1.3f) {
            mario_->object_->worldCoordinate_.position_.y = goal_->cube_->worldCoordinate_.position_.y + (1.0f + Player::gravity_ + Player::Radius_.y);
            mario_->SetAirState(false);
        }
        // ブロック y軸 底~中心 にプレイヤーがめり込んだ場合
        if (goal_->cube_->worldCoordinate_.position_.y - 1.3f <= mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y &&
            mario_->object_->worldCoordinate_.position_.y + Player::Radius_.y <= goal_->cube_->worldCoordinate_.position_.y) {
            isClear_ = true;
        }
    }
}