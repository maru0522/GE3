#pragma once
#include <fstream>
#include <wrl.h>
#if _MSC_VER > 1922 && !defined(_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif
#include <experimental/filesystem>
#include <map>
#include <xaudio2.h>

#pragma comment(lib,"xaudio2.lib")

class XAudio
{
public: // ��`
    using AUDIO_KEY = std::experimental::filesystem::path;
    struct AUDIO_VALUE {
        WAVEFORMATEX wfex;
        uint8_t* pBuffer;
        uint32_t bufferSize;
    };

    struct SoundData
    {
        WAVEFORMATEX wfex;
        uint8_t* pBuffer;
        uint32_t bufferSize;
    };

private: // ��`
    // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

    using fsPath = std::experimental::filesystem::path;

    struct ChunckHeader
    {
        char id[4];
        int32_t size;
    };

    struct RiffHeader
    {
        ChunckHeader chunk;
        char type[4];
    };

    struct FormatChunk
    {
        ChunckHeader chunk;
        WAVEFORMATEX fmt;
    };

public: // �ÓI�֐�
    static void Initialize(void);
    static void Load(const fsPath& pathAndFileName);
    static void UnLoad(SoundData* soundData);
    static void PlayWave(IXAudio2* xAudio2, const SoundData& soundData);
    static void Finalize(void);

private:
    static void LoadWave(const fsPath& pathAndFileName);

    // fstream�̓ǂݍ��݈ʒu�������������ʎq�̒��O�ɂ���
    static void SearchHeader(std::ifstream& file, const char* chunkId);

private: // �ÓI�ϐ�
    static ComPtr<IXAudio2> xAudio2_;
    static IXAudio2MasteringVoice* masterVoice_;
    static std::map<AUDIO_KEY, AUDIO_VALUE> audios_;
};