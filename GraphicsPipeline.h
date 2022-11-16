#pragma once
#include <wrl.h>
#include <d3d12.h>

#pragma comment(lib,"d3d12.lib")

class GraphicsPipeline
{
public: // ��`
    enum class GPType
    {
        SPRITE,
        MODEL
    };

private: // ��`
    // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �֐�
    GraphicsPipeline(GPType type);

#pragma region getter
    ID3D12RootSignature* GetRootSignature(void) { return rootSignature_.Get(); }
    ID3D12PipelineState* GetPipelineState(void) { return pipelineState_.Get(); }
#pragma endregion

private: // �ϐ�
    ComPtr<ID3D12RootSignature> rootSignature_{}; // ���[�g�V�O�l�`��
    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc_{}; // �O���t�B�b�N�X�p�C�v���C���ݒ�
    ComPtr<ID3D12PipelineState> pipelineState_{}; // �p�C�v�����X�e�[�g�̐���
};

