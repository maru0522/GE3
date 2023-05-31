#include "GameScene.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"
#include <imgui.h>
#include "Collision.h"

void GameScene::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);

    // 球の初期値を設定
    sphere_.center_ = DirectX::XMVectorSet(0, 2, 0, 1); // 中心点座標
    sphere_.radius_ = 1.f;

    // 平面の初期値を設定
    plane_.normal_ = DirectX::XMVectorSet(0, 1, 0, 0); // 法線ベクトル
    plane_.distance_ = 0.f; // 原点(0,0,0)からの距離

    camera_->eye_ = { 0,0,-20 };

    planeObj_->worldCoordinate_.scale_ = { 10,0.01f,3 };
    planeObj_->worldCoordinate_.position_ = { 0.f,0.f,0.f };

    sphereObj_->worldCoordinate_.position_ = { sphere_.center_.m128_f32[0],sphere_.center_.m128_f32[1],sphere_.center_.m128_f32[2] };
}

void GameScene::Update(void)
{
    // 球移動
    {
        //DirectX::XMVECTOR moveY{ DirectX::XMVectorSet(0.f,0.01f,0.f,0.f) };
        //if (KEYS::IsDown(DIK_NUMPAD8))
        //{
        //    sphere_.center_.m128_f32[0] += moveY.m128_f32[0];
        //    sphere_.center_.m128_f32[1] += moveY.m128_f32[1];
        //    sphere_.center_.m128_f32[2] += moveY.m128_f32[2];
        //    sphere_.center_.m128_f32[3] += moveY.m128_f32[3];
        //}
        //else if (KEYS::IsDown(DIK_NUMPAD2))
        //{
        //    sphere_.center_.m128_f32[0] -= moveY.m128_f32[0];
        //    sphere_.center_.m128_f32[1] -= moveY.m128_f32[1];
        //    sphere_.center_.m128_f32[2] -= moveY.m128_f32[2];
        //    sphere_.center_.m128_f32[3] -= moveY.m128_f32[3];
        //}
    }
    sphere_.center_.m128_f32[1] = std::sinf(Util::Convert::ToRadian(degree_)) * 2.f;

    ImGui::Begin("TitleScene");
    ImGui::Text("sphere : %f,%f,%f", sphere_.center_.m128_f32[0], sphere_.center_.m128_f32[1], sphere_.center_.m128_f32[2]);

    bool hit{ Collision::CheckSphere2Plane(sphere_,plane_) };
    ImGui::Text("Hit : %d", hit);
    ImGui::End();

    camera_->Update();

    sphereObj_->worldCoordinate_.position_ = { sphere_.center_.m128_f32[0],sphere_.center_.m128_f32[1],sphere_.center_.m128_f32[2] };

    if (hit) {
        sphereObj_->SetColor({ 1,0,0,1 });
    }
    else {
        sphereObj_->SetColor({ 1,1,1,1 });
    }

    sphereObj_->Update();
    planeObj_->Update();

    //if (KEYS::IsTrigger(DIK_RETURN)) {
    //    sceneManager_->RequestChangeScene(SceneFactory::Type::PLAYGAME);
    //}

    if (degree_ < 360) degree_++;
    else degree_ = 1;
}

void GameScene::Draw3d(void)
{
    sphereObj_->Draw();
    planeObj_->Draw();
}

void GameScene::Draw2d(void)
{
}

void GameScene::Finalize(void)
{
}
