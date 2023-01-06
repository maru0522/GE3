#include "Block2d.h"

Block2d::Block2d(Type blockType, const DirectX::XMFLOAT2& length)
{
    switch (blockType) {
    case Type::GRASS:
        square_ = std::make_unique<Sprite>("chapter1_grass", CMode::ID);
        break;
    case Type::DIRT:
        square_ = std::make_unique<Sprite>("chapter1_dirt", CMode::ID);
        break;
    }

    square_->SetSize(length);
}

void Block2d::Update(void)
{
    square_->Update();
}

void Block2d::Draw(void)
{
    square_->Draw();
}
