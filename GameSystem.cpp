#include "GameSystem.h"
#include "Obj3d.h"
#include "Sprite.h"

GameSystem::GameSystem(void)
{
}

void GameSystem::Initialize(void)
{
    BasicFrame::Initialize();
}

void GameSystem::Update(void)
{
    BasicFrame::Update();
}

void GameSystem::Draw(void)
{
    iDX_->PreDraw();

    // -----3D�I�u�W�F�N�g�̕`��----- //
    Obj3d::PreDraw();

    // -----3D�I�u�W�F�N�g�̕`��----- //

    // ---------2DUI�̕`��---------
    Sprite::PreDraw();

    // ---------2DUI�̕`��---------

    iDX_->PostDraw();
}

void GameSystem::Finalize(void)
{
    BasicFrame::Finalize();
}
