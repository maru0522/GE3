#pragma once
#include <memory>
#include "Camera.h"
#include "Sprite.h"
#include "Obj3d.h"
#include "BaseScene.h"

using std::unique_ptr;

class TitleScene : public BaseScene
{
public: // �֐�
    void Initialize(SceneManager* pSceneManager) override;
    void Update(void) override;
    void Draw3d(void) override;
    void Draw2d(void) override;
    void Finalize(void) override;

private:
    unique_ptr<Camera> cameraT_{};
    std::array<unique_ptr<Sprite>, 6> sprite_titleBackGrounds_{}; // �w�i�G
    std::array<unique_ptr<Sprite>, 6> sprite_titleBackPieces_{}; // �w�i�A�C�e��
    std::array<unique_ptr<Sprite>, 20> sprite_titleBlocks_{}; // �w�i�A�C�e��
    unique_ptr<Sprite> sprite_titleTree_{ std::make_unique<Sprite>("title_atlas", CMode::ID) };
    unique_ptr<Sprite> sprite_titleLogo_{ std::make_unique<Sprite>("title_atlas", CMode::ID) };
    unique_ptr<Sprite> sprite_titleFrame_{ std::make_unique<Sprite>("titleFrame", CMode::ID) };
};

