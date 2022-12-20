#include "GameSystem.h"
#include "Obj3d.h"
#include "Sprite.h"
#include "GameScene.h"
#include "TitleScene.h"

GameSystem::GameSystem(void)
{
}

void GameSystem::Initialize(void)
{
    BasicFrame::Initialize();

    scene_ = std::make_unique<TitleScene>();
    scene_->Initialize();
}

void GameSystem::Update(void)
{
    BasicFrame::Update();
    scene_->Update();
}

void GameSystem::Draw(void)
{
    iDX_->PreDraw();

    // -----3D�I�u�W�F�N�g�̕`��----- //
    Obj3d::PreDraw();
    scene_->Draw3d();
    // -----3D�I�u�W�F�N�g�̕`��----- //

    // ---------2DUI�̕`��---------
    Sprite::PreDraw();
    scene_->Draw2d();

    // ---------2DUI�̕`��---------

    iDX_->PostDraw();
}

void GameSystem::Finalize(void)
{
    scene_->Finalize();
    scene_.reset();

    BasicFrame::Finalize();
}
