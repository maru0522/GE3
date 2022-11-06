#pragma once
#include <array>
#include <DirectXMath.h>
#include <wrl.h>
#include "ConstBuffer.h"
#include <d3d12.h>

#pragma comment(lib,"d3d12.lib")

// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
struct CBDataMaterial_st {
    DirectX::XMFLOAT4 color_; // �F�iRGBA�j
};

// ���_�f�[�^�\����
struct Vertex_st
{
    DirectX::XMFLOAT3 pos_;       // xyz���W
    //DirectX::XMFLOAT3 normal;    // �@���x�N�g��
    DirectX::XMFLOAT2 uv_;        // uv���W
};

class Sprite
{
public: // �֐�
    Sprite(void);
    void Draw(void);

    // RGBA�l�w��ŐF�ύX 0~255�Ŏw��
    void SetColor(DirectX::XMFLOAT4 rgba = {255.0f,255.0f,255.0f,255.0f});
    void SetColor(float_t r = 255.0f, float_t g = 255.0f, float_t b = 255.0f, float_t a = 255.0f);

private: // �֐�
    void SetCommandsBeforeDraw(void); // ���ʐݒ�̃R�}���h���X�g�ςݍ���

private: // �ϐ�
    // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

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
};