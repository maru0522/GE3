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

class Billborad
{
private: // ��`
    // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // �ϐ�
    // �e�N�X�`�����̈����o���n���h��
    D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandleCopy_{};
    DirectX::XMFLOAT2 originalSize_{}; // �e�N�X�`���̑S�̃T�C�Y

#pragma region ���_
    //std::array<VertexSprite_st, 4> vertices_{}; // ���_�f�[�^
    ComPtr<ID3D12Resource> vertBuff_{ nullptr }; // ���_�o�b�t�@�̐���
    D3D12_VERTEX_BUFFER_VIEW vbView_{}; // ���_�o�b�t�@�r���[�̍쐬
#pragma endregion
};

