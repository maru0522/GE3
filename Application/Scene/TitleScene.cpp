#include "TitleScene.h"
#include "Texture.h"
#include "Model.h"
#include "Input.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Collision.h"
#include <sstream>
#include <iomanip>
#include <imgui.h>

void TitleScene::Initialize(SceneManager* pSceneManager)
{
    BaseScene::Initialize(pSceneManager);
}

void TitleScene::Update(void)
{
    if (KEYS::IsTrigger(DIK_RETURN)) {
        sceneManager_->RequestChangeScene(SceneFactory::Type::PLAYGAME);
    }
    a_->Update();
}

void TitleScene::Draw3d(void)
{
}

void TitleScene::Draw2d(void)
{
    a_->Draw();
}

void TitleScene::Finalize(void)
{
}
