#include "Block.h"

Block::Block(Type blockType, const DirectX::XMFLOAT3& scale, Camera* pcamera)
{
    switch (blockType) {
    case Type::GRASS:
        cube_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", pcamera);
        cube_->SetTextureById("chapter1_grass");
        break;
    case Type::GRASS_SURFACE:
        cube_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", pcamera);
        cube_->SetTextureById("chapter1_grassSurface");
        break;
    case Type::DIRT:
        cube_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", pcamera);
        cube_->SetTextureById("chapter1_dirt");
        break;
    case Type::BRICK:
        cube_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", pcamera);
        cube_->SetTextureById("chapter1_brick");
        break;
    case Type::QUESTION:
        cube_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", pcamera);
        cube_->SetTextureById("chapter1_question");
        break;
    case Type::EMPTY:
        cube_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", pcamera);
        cube_->SetTextureById("chapter1_empty");
        break;
    case Type::PLASTIC:
        cube_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", pcamera);
        cube_->SetTextureById("chapter1_plastic");
        break;
    case Type::PIPE:
        cube_ = std::make_unique<Obj3d>("Resources/3dModels/greenPipe/GreenPipe.obj", pcamera);
        break;
    case Type::GOAL:
        cube_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", pcamera);
        cube_->SetTextureById("chapter1_goal");
        break;
    }

    cube_->worldCoordinate_.scale_ = { scale.x, scale.y, scale.z };
}

void Block::Update(void)
{
    cube_->Update();
}

void Block::Draw(void)
{
    cube_->Draw();
}
