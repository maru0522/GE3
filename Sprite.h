#pragma once
#include <array>
#include <DirectXMath.h>
#include <wrl.h>
#include "ConstBuffer.h"
#include <string>
#include "Window.h"
#include <d3d12.h>

#pragma comment(lib,"d3d12.lib")

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

enum class CMode // ConstructorMode
{
    PATH,   // 1.path��file�̖��O
    ID      // 2.�ݒ肵��id
};

class Sprite
{
public: // �֐�
    Sprite(const std::string& relativePath, const std::string& fileName);
    Sprite(const std::string& pathAndFileName_or_Id, CMode mode);
    void Update(void);
    void Draw(void);

    // RGBA�l�w��ŐF�ύX 0~255�Ŏw��
    void SetColor(DirectX::XMFLOAT4 rgba = { 255.0f,255.0f,255.0f,255.0f });
    void SetColor(float_t r = 255.0f, float_t g = 255.0f, float_t b = 255.0f, float_t a = 255.0f);

    void SetParent(Sprite* parent);

private: // �֐�
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
    DirectX::XMFLOAT3 position_{ 0,0,0 };
    float_t rotate_{ 0.0f };
};