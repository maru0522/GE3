#include "Sprite.h"
#include "InitDirectX.h"
#include <string>
#include "Texture.h"
#include "Window.h"
#include "Util.h"
#include "GraphicsPipeline.h"
#include<d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

// �ÓI�ϐ��̎���
GraphicsPipeline* Sprite::graphicsPipeline_{ GraphicsPipeline::GetGraphicsPipeLine2d() };

void Sprite::PreDraw(void)
{
    InitDirectX* iDX = InitDirectX::GetInstance();

# pragma region ����
    // �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
    iDX->GetCommandList()->SetPipelineState(graphicsPipeline_->GetPipelineState());
    iDX->GetCommandList()->SetGraphicsRootSignature(graphicsPipeline_->GetRootSignature());
    // �v���~�e�B�u�`��̐ݒ�R�}���h
    iDX->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // �O�p�`���X�g

    ID3D12DescriptorHeap* ppHeaps[] = { Texture::GetSRVHeap() };
    // SRV�q�[�v�̐ݒ�R�}���h
    iDX->GetCommandList()->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
#pragma endregion
}

Sprite::Sprite(const fsPath& relativePath, const fsPath& fileName)
{
    Sprite{ relativePath / fileName, CMode::PATH };
}

Sprite::Sprite(const fsPath& pathAndFileName_or_Id, CMode mode)
{
#pragma region gpuHandle�̎󂯎��
    if (!static_cast<int>(CMode::PATH)) {
        // �R���X�g���N�^���[�h��PATH�̏ꍇ
        srvGpuHandleCopy_ = Texture::GetTextureInfo(pathAndFileName_or_Id)->srvGpuHandle_;
    }
    else {
        // �R���X�g���N�^���[�h��ID�̏ꍇ
        srvGpuHandleCopy_ = Texture::GetTextureInfoById(pathAndFileName_or_Id.string())->srvGpuHandle_;
    }
#pragma endregion

#pragma region ���_��񏈗�
    // ���_�f�[�^�̐ݒ�
    vertices_.at(0) = { {   0.0f, 100.0f, 0.0f }, {0.0f, 1.0f} };    // ����
    vertices_.at(1) = { {   0.0f,   0.0f, 0.0f }, {0.0f, 0.0f} };    // ����
    vertices_.at(2) = { { 100.0f, 100.0f, 0.0f }, {1.0f, 1.0f} };    // �E��
    vertices_.at(3) = { { 100.0f,   0.0f, 0.0f }, {1.0f, 0.0f} };    // �E��

    // ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
    uint32_t sizeVB = static_cast<UINT>(sizeof(vertices_[0]) * vertices_.size());

    // ���_�o�b�t�@�̐ݒ�
    D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
    heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p

    // ���\�[�X�ݒ�
    D3D12_RESOURCE_DESC resDesc{};
    resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
    resDesc.Height = 1;
    resDesc.DepthOrArraySize = 1;
    resDesc.MipLevels = 1;
    resDesc.SampleDesc.Count = 1;
    resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    // �C���X�^���X�擾
    InitDirectX* iDX = InitDirectX::GetInstance();

    // ���_�o�b�t�@�̐���
    HRESULT r = iDX->GetDevice()->CreateCommittedResource(
        &heapProp, // �q�[�v�ݒ�
        D3D12_HEAP_FLAG_NONE,
        &resDesc, // ���\�[�X�ݒ�
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&vertBuff_));
#ifdef _DEBUG
    assert(SUCCEEDED(r));
#endif // _DEBUG

    // GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
    VertexSprite_st* vertMap{ nullptr };
    r = vertBuff_->Map(0, nullptr, (void**)&vertMap);
#ifdef _DEBUG
    assert(SUCCEEDED(r));
#endif // _DEBUG
    // �S���_�ɑ΂���
    for (int i = 0; i < vertices_.size(); i++)
    {
        vertMap[i] = vertices_[i]; // ���W���R�s�[
    }

    // �q���������
    vertBuff_->Unmap(0, nullptr);
#pragma endregion

#pragma region ���_�o�b�t�@�̃r���[�ݒ�
    // vbview
    // GPU���z�A�h���X
    vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
    // ���_�o�b�t�@�̃T�C�Y
    vbView_.SizeInBytes = sizeVB;
    // ���_1���̃f�[�^�T�C�Y
    vbView_.StrideInBytes = sizeof(vertices_[0]);
#pragma endregion

#pragma region cbTransform
    SetCBTransform();
#pragma endregion

    SetColor({ 1.0f,1.0f,1.0f,1.0f });
}

void Sprite::Update(void)
{
    TransferVertex();

    // ���[���h�s��̏�����
    matWorld_ = DirectX::XMMatrixIdentity();

    // ��]�s��̐錾�Ə�����
    DirectX::XMMATRIX matRot{ DirectX::XMMatrixIdentity() };
    matRot *= DirectX::XMMatrixRotationZ(rotation_); // z�x��]
    matWorld_ *= matRot; // ���[���h�s��ɉ�]�𔽉f

    // ���s�ړ��s��̐錾�Ə�����
    DirectX::XMMATRIX matTrans{ DirectX::XMMatrixIdentity() };
    matTrans = DirectX::XMMatrixTranslation(position_.x, position_.y, 0.0f); // ���s�ړ�
    matWorld_ *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

    // �e��ݒ肵�Ă���ꍇ�͐e�̃��[���h�s�������
    if (parent_) {
        matWorld_ *= parent_->matWorld_;
    } // ��̐ݒ�̓��[���h�s��̂��̂ł͂Ȃ����[�J���s��ׂ̈̐ݒ�ƂȂ�

    // �萔�o�b�t�@�֓]��
    TransferMatrix();
}

void Sprite::Draw(void)
{
    if (isInvisible_) {
        return;
    }

    InitDirectX* iDX = InitDirectX::GetInstance();

#pragma region ���_�o�b�t�@
    // ���_�o�b�t�@�r���[�̐ݒ�R�}���h
    iDX->GetCommandList()->IASetVertexBuffers(0, 1, &vbView_);
#pragma endregion

#pragma region ConstBuffer
    // �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
    iDX->GetCommandList()->SetGraphicsRootConstantBufferView(0, cbMaterial_.GetBuffer()->GetGPUVirtualAddress());
    iDX->GetCommandList()->SetGraphicsRootConstantBufferView(2, cbTransform_.GetBuffer()->GetGPUVirtualAddress());
#pragma endregion

#pragma region SRV
    // SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
    iDX->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandleCopy_);
#pragma endregion

    // �`��R�}���h
    iDX->GetCommandList()->DrawInstanced(static_cast<uint32_t>(vertices_.size()), 1, 0, 0); // �S�Ă̒��_���g���ĕ`��
}

void Sprite::SetColor(DirectX::XMFLOAT4 rgba)
{
    // �l��0.0f��菬������0.0f�ɂ���
    rgba.x = (std::max)(rgba.x, 0.0f);
    rgba.y = (std::max)(rgba.y, 0.0f);
    rgba.z = (std::max)(rgba.z, 0.0f);
    rgba.w = (std::max)(rgba.w, 0.0f);

    // �l��1.0f���傫����1.0f�ɂ���
    rgba.x = (std::min)(1.0f, rgba.x);
    rgba.y = (std::min)(1.0f, rgba.y);
    rgba.z = (std::min)(1.0f, rgba.z);
    rgba.w = (std::min)(1.0f, rgba.w);

    // �l���������ނƎ����I�ɓ]�������
    cbMaterial_.GetConstBuffMap()->color_ = rgba;
}

void Sprite::SetColor(float_t r, float_t g, float_t b, float_t a)
{
    // �l��0.0f��菬������0.0f�ɂ���
    r = (std::max)(r, 0.0f);
    g = (std::max)(g, 0.0f);
    b = (std::max)(b, 0.0f);
    a = (std::max)(a, 0.0f);

    // �l��1.0f���傫����1.0f�ɂ���
    r = (std::min)(1.0f, r);
    g = (std::min)(1.0f, g);
    b = (std::min)(1.0f, b);
    a = (std::min)(1.0f, a);

    // �l���������ނƎ����I�ɓ]�������
    cbMaterial_.GetConstBuffMap()->color_ = { r,g,b,a };
}

void Sprite::SetColor255(DirectX::XMFLOAT4 rgba)
{
    // �l��0.0f��菬������0.0f�ɂ���
    rgba.x = (std::max)(rgba.x, 0.0f);
    rgba.y = (std::max)(rgba.y, 0.0f);
    rgba.z = (std::max)(rgba.z, 0.0f);
    rgba.w = (std::max)(rgba.w, 0.0f);

    // �l��255.0f���傫����255.0f�ɂ���
    rgba.x = (std::min)(255.0f, rgba.x);
    rgba.y = (std::min)(255.0f, rgba.y);
    rgba.z = (std::min)(255.0f, rgba.z);
    rgba.w = (std::min)(255.0f, rgba.w);

    // ���K��
    rgba = {
        static_cast<float>(rgba.x / 255.0f),
        static_cast<float>(rgba.y / 255.0f),
        static_cast<float>(rgba.z / 255.0f),
        static_cast<float>(rgba.w / 255.0f)
    };

    // �l���������ނƎ����I�ɓ]�������
    cbMaterial_.GetConstBuffMap()->color_ = rgba;
}

void Sprite::SetColor255(float_t r, float_t g, float_t b, float_t a)
{
    // �l��0.0f��菬������0.0f�ɂ���
    r = (std::max)(r, 0.0f);
    g = (std::max)(g, 0.0f);
    b = (std::max)(b, 0.0f);
    a = (std::max)(a, 0.0f);

    // �l��255.0f���傫����255.0f�ɂ���
    r = (std::min)(255.0f, r);
    g = (std::min)(255.0f, g);
    b = (std::min)(255.0f, b);
    a = (std::min)(255.0f, a);

    // ���K��
    DirectX::XMFLOAT4 rgba{
        static_cast<float>(r / 255.0f),
        static_cast<float>(g / 255.0f),
        static_cast<float>(b / 255.0f),
        static_cast<float>(a / 255.0f)
    };

    // �l���������ނƎ����I�ɓ]�������
    cbMaterial_.GetConstBuffMap()->color_ = rgba;
}

void Sprite::SetParent(Sprite* parent)
{
    parent_ = parent;
}

void Sprite::TransferVertex(void)
{
#pragma region �A���J�[�|�C���g�̕ύX
    float_t left{ (0.0f - anchorPoint_.x) * size_.x };
    float_t right{ (1.0f - anchorPoint_.x) * size_.x };
    float_t top{ (0.0f - anchorPoint_.y) * size_.y };
    float_t bottom{ (1.0f - anchorPoint_.y) * size_.y };
#pragma endregion

#pragma region �t���b�v�̕ύX
    // �O���t�B�b�N�X�p�C�v���C���̔w�ʃJ�����O���I�t�ɂ��Ă��Ȃ��ƕ`�悳��Ȃ��Ȃ�

    // ���E�t���b�v
    if (isFlipX_) {
        left = -left; // ��
        right = -right; // �E
    }

    // �㉺�t���b�v
    if (isFlipY_) {
        top = -top; // ��
        bottom = -bottom; // ��
    }
#pragma endregion

#pragma region ���_���W�̕ύX
    vertices_.at(static_cast<int>(VertNum::LeftBottom)).pos_ = { left, bottom, 0.0f };      // ����
    vertices_.at(static_cast<int>(VertNum::LeftTop)).pos_ = { left, top, 0.0f };            // ����
    vertices_.at(static_cast<int>(VertNum::RightBottom)).pos_ = { right, bottom, 0.0f };    // �E��
    vertices_.at(static_cast<int>(VertNum::RightTop)).pos_ = { right, top, 0.0f };          // �E��
#pragma endregion

#pragma region ���_�o�b�t�@�r���[
    vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress(); // GPU���Q�Ƃ���A�h���X��n��
    vbView_.SizeInBytes = static_cast<UINT>(sizeof(vertices_[0]) * vertices_.size()); // ���_�o�b�t�@�̃T�C�Y = ���_�f�[�^�S�̂̃T�C�Y
    vbView_.StrideInBytes = sizeof(vertices_[0]); // ���_1���̃f�[�^�T�C�Y
#pragma endregion

#pragma region ���W�̍X�V
    // GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
    VertexSprite_st* vertMap{ nullptr };
    // �}�b�s���O
    HRESULT r = vertBuff_->Map(0, nullptr, (void**)&vertMap);
#ifdef _DEBUG
    assert(SUCCEEDED(r));
#endif // _DEBUG

    // ���W�̃R�s�[
    std::copy(vertices_.begin(), vertices_.end(), vertMap);

    // �}�b�s���O����
    vertBuff_->Unmap(0, nullptr);
#pragma endregion
}

void Sprite::TransferMatrix(void)
{
    cbTransform_.GetConstBuffMap()->mat_ = matWorld_ * matProjection_;
}

void Sprite::SetCBTransform(void)
{
#pragma region cbTransform
    cbTransform_.GetConstBuffMap()->mat_ = DirectX::XMMatrixIdentity();
    cbTransform_.GetConstBuffMap()->mat_.r[0].m128_f32[0] = 2.0f / Window::width_;
    cbTransform_.GetConstBuffMap()->mat_.r[1].m128_f32[1] = -2.0f / Window::height_;
    cbTransform_.GetConstBuffMap()->mat_.r[3].m128_f32[0] = -1.0f;
    cbTransform_.GetConstBuffMap()->mat_.r[3].m128_f32[1] = 1.0f;
#pragma endregion
}
