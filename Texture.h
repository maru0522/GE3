#pragma once
#include <string>
#include <wrl.h>
#include <d3d12.h>
#include <array>
#include <map>
#include <tuple>

class Texture
{
public: // �ÓI�֐�
    // map�̌��ƒl
    using MAP_KEY = std::string;
    using MAP_VALUE = std::tuple < Microsoft::WRL::ComPtr<ID3D12Resource>, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE >;

    // srv�̏�����
    static void Initialize(void);

    // �Ǎ�
    static void Load(const std::string& relativePath, const std::string& fileName);
    static void Load(const std::string& pathAndFileName);

    // �Ǎ��ς̃e�N�X�`�����������Ԃ�
    static const Texture& GetTexture(const std::string& relativePath, const std::string& fileName);
    static const Texture& GetTexture(const std::string& pathAndFileName);

    // �Ǎ��ς̃e�N�X�`���̏�񂾂��Ԃ�
    static const MAP_VALUE& GetTextureInfo(const std::string& relativePath, const std::string& fileName);
    static const MAP_VALUE& GetTextureInfo(const std::string& pathAndFileName);

    static const D3D12_GPU_DESCRIPTOR_HANDLE& GetTexSRVGpuH(const std::string& pathAndFileName);

    // private�ϐ�: srvHeap ���擾
    static ID3D12DescriptorHeap* GetSRVHeap(void) { return srvHeap_.Get(); }

private: // �ÓI�ϐ�
    // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

    static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;

    static constexpr size_t maxSRVDesc_{ 256 }; // �e�N�X�`���̍ő�Ǎ���

    static std::map<MAP_KEY, MAP_VALUE> textures_; // SRV�����Ă���
    static uint32_t indexNextDescHeap_; // ���ɏ�������DescHeap�̔ԍ����w������

private: // �ϐ�
    // ���O
    MAP_KEY name_{};
    MAP_VALUE info_{};

    //================= MAP_VALUE =================//
    // ComPtr<ID3D12Resource> buffer_;             //
    // D3D12_CPU_DESCRIPTOR_HANDLE srvCPUHandle_;  //
    // D3D12_GPU_DESCRIPTOR_HANDLE srvGPUHandle_;  //
    //=============================================//

private: // �֐�
    void SetMapKey(std::string keyName);
};