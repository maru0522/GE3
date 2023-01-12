#pragma once
#include <memory>
#include "Camera.h"
#include "Obj3d.h"
#include "BaseScene.h"
#include "Block.h"
#include "Player.h"

using std::unique_ptr;

constexpr uint32_t cameraSpeed_{ 2 };

class GameScene : public BaseScene
{
public: // ä÷êî
    void Initialize(SceneManager* sceneManager) override;
    void Update(void) override;
    void Draw3d(void) override;
    void Draw2d(void) override;
    void Finalize(void) override;

private:
    void Col(void);

private:
    unique_ptr<Camera> perspectiveCamera_{};
    //std::array<unique_ptr<Block>, 100> dirtBlocks2d_{};
    std::array<unique_ptr<Block>, 65> dirtBlocks_{};
    std::array<unique_ptr<Block>, 65> grassBlocks_{};
    std::array<unique_ptr<Block>, 65> grassSurfaceBlocks_{};
    std::array<unique_ptr<Block>, 65> grassSurfaceBlocks2_{};
    std::array<unique_ptr<Block>, 65> grassSurfaceBlocks3_{};
    std::array<unique_ptr<Block>, 10> questionBlocks_{};
    std::array<unique_ptr<Block>, 15> plasticBlocks_{};
    std::array<unique_ptr<Block>, 10> brickBlocks_{};


    std::array<unique_ptr<Block>, 10> sQBlocks_{};

    std::unique_ptr<Block> pipe_{};

    std::unique_ptr<Block> goal_{};

    std::unique_ptr<Sprite> sprite_clear{ std::make_unique<Sprite>("chapter1_clear",CMode::ID) };

    unique_ptr<Player> mario_{};

    bool isClear_{ false };
};

