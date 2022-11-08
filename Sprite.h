#pragma once
#include <array>
#include <DirectXMath.h>
#include <wrl.h>
#include "ConstBuffer.h"
#include <string>
#include "Window.h"
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
    struct Vertex_st
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

public: // �֐�
    Sprite(const std::string& relativePath, const std::string& fileName);
    Sprite(const std::string& pathAndFileName_or_Id, CMode mode);
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
#pragma endregion
#pragma region getter
    // ���W���擾
    const DirectX::XMFLOAT2& GetPosition(void) const { return position_; }

    // ��]�p���擾
    float_t GetRotation(void) const { return rotation_; }

    // �\���T�C�Y�i�s�N�Z���j���擾
    const DirectX::XMFLOAT2& GetSize(void) const { return size_; }
#pragma endregion
private: // �֐�
    void TransferVertex(void);
    void TransferMatrix(void);

    void SetCBTransform(void); // CBTrans
    void SetCommandsBeforeDraw(void); // ���ʐݒ�̃R�}���h���X�g�ςݍ���

private: // �ϐ�
    // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

    // �e�N�X�`�����̈����o���n���h��
    D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandleCopy_{};

#pragma region ���_
    std::array<Vertex_st, 4> vertices_{}; // ���_�f�[�^
    ComPtr<ID3D12Resource> vertBuff_{ nullptr }; // ���_�o�b�t�@�̐���
    D3D12_VERTEX_BUFFER_VIEW vbView_{}; // ���_�o�b�t�@�r���[�̍쐬
#pragma endregion

    ComPtr<ID3D12RootSignature> rootSignature_; // ���[�g�V�O�l�`��
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc_; // �O���t�B�b�N�X�p�C�v���C���ݒ�
    ComPtr<ID3D12PipelineState> pipelineState_; // �p�C�v�����X�e�[�g�̐���

    // �萔�o�b�t�@
    ConstBuffer<CBDataMaterial_st> cbMaterial_{};
    ConstBuffer<CBDataTransform_st> cbTransform_{};

    // �e
    Sprite* parent_{ nullptr };

    // �s��
    DirectX::XMMATRIX matWorld_{ DirectX::XMMatrixIdentity() }; // ���[���h�ϊ�
    float_t nearZ_{ 0.0f };
    float_t farZ_{ 1.0f };
    DirectX::XMMATRIX matProjection_{ DirectX::XMMatrixOrthographicOffCenterLH(0.0f,static_cast<float_t>(Window::width_),static_cast<float_t>(Window::height_),0.0f,nearZ_,farZ_) }; // ���s���e

    // Sprite�ɑ΂�����
    DirectX::XMFLOAT2 position_{ 0.0f, 0.0f }; // ���W
    float_t rotation_{ 0.0f }; // ��]�p
    DirectX::XMFLOAT2 size_{ 100.0f,100.0f }; //�\���T�C�Y�i�s�N�Z���j
};