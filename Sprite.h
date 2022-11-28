#pragma once
#include <array>
#include <DirectXMath.h>
#include <wrl.h>
#include "ConstBuffer.h"
#include <string>
#include "Window.h"
#if _MSC_VER > 1922 && !defined(_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif
#include <experimental/filesystem>
#include "GraphicsPipeline.h"
#include <d3d12.h>

#pragma comment(lib,"d3d12.lib")

enum class CMode // ConstructorMode
{
    PATH,   // 1.path��file�̖��O
    ID      // 2.�ݒ肵��id
};

class Sprite
{
private: // ��`
#pragma region �萔�o�b�t�@�p�\���̒�`
// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
    struct CBDataMaterial_st {
        DirectX::XMFLOAT4 color_; // �F�iRGBA�j
    };

    // �萔�o�b�t�@�p�f�[�^�\���́i3D�ϊ��s��j
    struct CBDataTransform_st {
        DirectX::XMMATRIX mat_;  // 3D�ϊ��s��
    };
#pragma endregion

    // ���_�f�[�^�\����
    struct VertexSprite_st
    {
        DirectX::XMFLOAT3 pos_;       // xyz���W
        //DirectX::XMFLOAT3 normal;    // �@���x�N�g��
        DirectX::XMFLOAT2 uv_;        // uv���W
    };

    enum class VertNum
    {
        LeftBottom,     // ����
        LeftTop,        // ����
        RightBottom,    // �E��
        RightTop        // �E��
    };

    using fsPath = std::experimental::filesystem::path;

public: // �ÓI�֐�
    static void PreDraw(void);

private: // �ÓI�ϐ�
    static GraphicsPipeline* graphicsPipeline_;

public: // �֐�
    Sprite(const fsPath& relativePath, const fsPath& fileName);
    Sprite(const fsPath& pathAndFileName_or_Id, CMode mode);
    void Update(void);
    void Draw(void);

#pragma region Setter
    void SetColor(DirectX::XMFLOAT4 rgba = { 1.0f,1.0f,1.0f,1.0f });
    void SetColor(float_t r = 1.0f, float_t g = 1.0f, float_t b = 1.0f, float_t a = 1.0f);

    // RGBA�l�w��ŐF�ύX 0~255�Ŏw��
    void SetColor255(DirectX::XMFLOAT4 rgba = { 255.0f,255.0f,255.0f,255.0f });
    void SetColor255(float_t r = 255.0f, float_t g = 255.0f, float_t b = 255.0f, float_t a = 255.0f);

    // �e��ݒ�
    void SetParent(Sprite* parent);

    // ���W��ݒ�
    void SetPosition(const DirectX::XMFLOAT2& position) { position_ = position; }

    // ��]�p��ݒ�
    void SetRotation(float_t fRadians) { rotation_ = fRadians; }

    // �\���T�C�Y�i�s�N�Z���j��ݒ�
    void SetSize(const DirectX::XMFLOAT2& size) { size_ = size; }

    // �A���J�[�|�C���g��ݒ�
    void SetAnchorPoint(const DirectX::XMFLOAT2& anchorPoint) { anchorPoint_ = anchorPoint; }

    // �؂�o�����̎n�_��ݒ�
    void SetCutStartPoint(const DirectX::XMFLOAT2& cutStartPoint) { cutStartPoint_ = cutStartPoint; }
    // �؂�o�����̏I�_��ݒ�i�T�C�Y�Ƃǂ��炩�ŗǂ�)
    void SetCutEndPoint(const DirectX::XMFLOAT2& cutEndPoint) { cutEndPoint_ = cutEndPoint; }
    // �؂�o�����̃T�C�Y��ݒ�i�I�_�Ƃǂ��炩�ŗǂ��j
    void SetCutLength(const DirectX::XMFLOAT2& cutLength) { cutLength_ = cutLength; }

    // �t���b�v��ݒ�
    void SetFlipX(bool isFlipX) { isFlipX_ = isFlipX; } // ���E�t���b�v
    void SetFlipY(bool isFlipY) { isFlipY_ = isFlipY; } // �㉺�t���b�v
    void SetFlip(bool isFlipX, bool isFlipY) { isFlipX_ = isFlipX, isFlipY_ = isFlipY; } // �ꊇ�t���b�v

    // ��\���̗L����ݒ�
    void SetInvisible(bool isInvisible) { isInvisible_ = isInvisible; }
#pragma endregion

#pragma region getter
    // ���W���擾
    const DirectX::XMFLOAT2& GetPosition(void) const { return position_; }

    // ��]�p���擾
    float_t GetRotation(void) const { return rotation_; }

    // �\���T�C�Y�i�s�N�Z���j���擾
    const DirectX::XMFLOAT2& GetSize(void) const { return size_; }

    // �A���J�[�|�C���g���擾
    const DirectX::XMFLOAT2& GetAnchorPoint(void) const { return anchorPoint_; }

    // �؂�o�����̎n�_���擾
    const DirectX::XMFLOAT2& GetCutStartPoint(void) const { return cutStartPoint_; }
    // �؂�o�����̏I�_���擾
    const DirectX::XMFLOAT2& GetCutEndPoint(void) const { return cutEndPoint_; }
    // �؂�o�����̃T�C�Y���擾
    const DirectX::XMFLOAT2& GetCutLength(void) const { return cutLength_; }

    // �t���b�v���擾
    bool GetFlipX(void) { return isFlipX_; } // ���E�t���b�v
    bool GetFlipY(void) { return isFlipY_; } // �㉺�t���b�v

    // ��\���̗L�����擾
    bool GetInvisible(void) { return isInvisible_; }
#pragma endregion
private: // �֐�
    void ConstructorCommon(void);

    void TransferVertex(void);
    void TransferMatrix(void);

    void SetOriginalSize(const fsPath& path, CMode mode);
    void AdjustTextureSize(void);
    void SetCBTransform(void); // CBTrans

private: // �ϐ�
    // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

    // �e�N�X�`�����̈����o���n���h��
    D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandleCopy_{};
    DirectX::XMFLOAT2 originalSize_{}; // �e�N�X�`���̑S�̃T�C�Y

#pragma region ���_
    std::array<VertexSprite_st, 4> vertices_{}; // ���_�f�[�^
    ComPtr<ID3D12Resource> vertBuff_{ nullptr }; // ���_�o�b�t�@�̐���
    D3D12_VERTEX_BUFFER_VIEW vbView_{}; // ���_�o�b�t�@�r���[�̍쐬
#pragma endregion

    // �萔�o�b�t�@
    ConstBuffer<CBDataMaterial_st> cbMaterial_{};
    ConstBuffer<CBDataTransform_st> cbTransform_{};

    // �s��
    DirectX::XMMATRIX matWorld_{ DirectX::XMMatrixIdentity() }; // ���[���h�ϊ�
    float_t nearZ_{ 0.0f };
    float_t farZ_{ 1.0f };
    DirectX::XMMATRIX matProjection_{ DirectX::XMMatrixOrthographicOffCenterLH(0.0f,static_cast<float_t>(Window::width_),static_cast<float_t>(Window::height_),0.0f,nearZ_,farZ_) }; // ���s���e

    // Sprite�̂����
    DirectX::XMFLOAT2 position_{ 0.0f, 0.0f }; // ���W
    float_t rotation_{ 0.0f }; // ��]�p
    DirectX::XMFLOAT2 size_{ 0.0f, 0.0f }; //�\���T�C�Y�i�s�N�Z���j
    DirectX::XMFLOAT2 anchorPoint_{ 0.0f, 0.0f }; // �A���J�[�|�C���g
    DirectX::XMFLOAT2 cutStartPoint_{ 0.0f, 0.0f }; // �؂�o�����̌��_�i����j
    DirectX::XMFLOAT2 cutEndPoint_{ 0.0f, 0.0f }; // �؂�o�����̌��_�i�E��)
    DirectX::XMFLOAT2 cutLength_{ 0.0f, 0.0f }; // �؂�o�����̃T�C�Y

    bool isFlipX_{ false }; // ���E�t���b�v
    bool isFlipY_{ false }; // �㉺�t���b�v
    bool isInvisible_{ false }; //��\���̗L��

    // �e�I�u�W�F�N�g�ւ̃|�C���^
    Sprite* parent_{ nullptr };
};