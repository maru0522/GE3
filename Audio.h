#pragma once
#include <fstream>
#include <wrl.h>
#include <xaudio2.h>

#pragma comment(lib,"xaudio2.lib")

class XAudio
{
private: // ��`
    // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �֐�
    static void Initialize(void);

private: // �ϐ�
    ComPtr<IXAudio2> xAudio2_;
    IXAudio2MasteringVoice* masterVoice_;
};