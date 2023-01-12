#pragma once
#include "AbstractBlock.h"
#include <DirectXMath.h>
#include "Camera.h"

class Block : public AbstractBlock
{
public: // ä÷êî
    Block(void) {};
    Block(Type blockType, const DirectX::XMFLOAT3& scale, Camera* pcamera);

    void Update(void) override;
    void Draw(void) override;

    void SetSize(const DirectX::XMFLOAT3& length) { length_ = length; }

    // ïœêî
    std::unique_ptr<Obj3d> cube_;
    DirectX::XMFLOAT3 length_{};
};