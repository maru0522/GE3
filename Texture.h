#pragma once
#include <string>
#include <wrl.h>
#include <d3d12.h>
#include <array>
#include <map>
#include <stdexcept>

class Texture
{
public: // �ÓI�֐�
    // map�̌��ƒl
    using MAP_KEY = std::string;
    struct MAP_VALUE
    {
        Microsoft::WRL::ComPtr<ID3D12Resource> buff_{ nullptr };
        D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle_{};
        D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle_{};
    };
    // map�̌���ID
    using MAP_ID = std::string;

    // srv�̏�����
    static void Initialize(void);

    // �Ǎ� 
    static void Load(const std::string& relativePath, const std::string& fileName);
    static void Load(const std::string& pathAndFileName);
    static void Load(const std::string& relativePath, const std::string& fileName, const std::string& id);
    static void LoadWithId(const std::string& pathAndFileName, const std::string& id); // �֐����ς������Ȃ��������ǉ���Ďv�������΂񂩂����B

    // �Ǎ��ς̃e�N�X�`�����������Ԃ�
    static const Texture GetTexture(const std::string& relativePath, const std::string& fileName);
    static const Texture GetTexture(const std::string& pathAndFileName);
    static const Texture GetTextureById(const std::string& id); // �֐����ς������Ȃ��������ǉ���Ďv�������΂񂩂����B

    // �Ǎ��ς̃e�N�X�`���̏�񂾂��Ԃ�
    static const MAP_VALUE GetTextureInfo(const std::string& relativePath, const std::string& fileName);
    static const MAP_VALUE GetTextureInfo(const std::string& pathAndFileName);
    static const MAP_VALUE GetTextureInfoById(const std::string& id); // �֐����ς������Ȃ��������ǉ���Ďv�������΂񂩂����B

    // �e�N�X�`���̃p�X�ɖ��̂�ݒ肵�ČĂяo�����ȗ����B���������t���Ă�邭�炢�̊��o�ł���
    static void CreateIdForTexPath(const std::string& relativePath, const std::string& fileName, const std::string& id);
    static void CreateIdForTexPath(const std::string& pathAndFileName, const std::string& id);

    // �ݒ肵��ID����MAP_KEY���擾����Bpublic�ɂ��Ă͂��邪��{�֐����Ŏg��
    static const MAP_KEY GetTextureKey(const std::string& id);

    // private�ϐ�: srvHeap ���擾
    static ID3D12DescriptorHeap* GetSRVHeap(void) { return srvHeap_.Get(); }

private: // �ÓI�ϐ�
    // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

    static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;

    static constexpr size_t maxSRVDesc_{ 256 }; // �e�N�X�`���̍ő�Ǎ���

    static std::map<MAP_KEY, MAP_VALUE> textures_; // SRVDesc��MAP_KEY�����Ă���
    static std::map<MAP_ID, MAP_KEY> mapKeys_; // MAP_KEY��ID��R�Â��ē���Ă���
    static uint32_t indexNextDescHeap_; // ���ɏ�������DescHeap�̔ԍ����w������

private: // �ϐ�
    // ���O
    MAP_KEY name_{};
    MAP_VALUE info_{};

    //================= MAP_VALUE ================//
    // ComPtr<ID3D12Resource> buffer_;            //
    // D3D12_CPU_DESCRIPTOR_HANDLE srvCPUHandle_; //
    // D3D12_GPU_DESCRIPTOR_HANDLE srvGPUHandle_; //
    //============================================//

private: // �֐�
    void SetMapKey(std::string keyName);
    void CheckPath(const std::string& relativePath, const std::string& fileName);
};