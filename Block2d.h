#pragma once
#include "AbstractBlock.h"
#include <DirectXMath.h>

class Block2d : public AbstractBlock
{
public: // ä÷êî
    Block2d(Type blockType, const DirectX::XMFLOAT2& length);
    Block2d(Type blockType) : Block2d(blockType, { AbstractBlock::lengthX_, AbstractBlock::lengthY_ }) {
        switch (blockType) {
        case Type::GRASS:
            square_ = std::make_unique<Sprite>("chapter1_grass", CMode::ID);
            break;
        case Type::DIRT:
            square_ = std::make_unique<Sprite>("chapter1_dirt", CMode::ID);
            break;
        }

        square_->SetSize({ AbstractBlock::lengthX_, AbstractBlock::lengthY_ });
    };

    void Update(void) override;
    void Draw(void) override;

    void SetSize(const DirectX::XMFLOAT2& length) { length_ = length; }

    // ïœêî
    std::unique_ptr<Sprite> square_;
    DirectX::XMFLOAT2 length_{};
};