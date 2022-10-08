#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include "mWindow.h"
#include <array>
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <wrl.h>

namespace mInput {
    class Keyboard
    {
    public: // �֐�
        static void Initialize();
        static void Update();

        // �������u��
        static bool IsTrigger(UINT8 key) { return !preKeys[key] && keys[key]; }

        // ������Ă���Ƃ�
        static bool IsDown(UINT8 key) { return keys[key]; }

        // �����ꂽ�u��
        static bool IsReleased(UINT8 key) { return preKeys[key] && !keys[key]; }

    private: // �ϐ�
        // �G�C���A�X�e���v���[�g
        template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

        static ComPtr<IDirectInput8> directInput; // DirectInput����
        static ComPtr<IDirectInputDevice8> keyboard; // �L�[�{�[�h�f�o�C�X����
        static std::array<BYTE, 256> preKeys;
        static std::array<BYTE, 256> keys;
    };
};

#ifndef NON_NAMESPACE_mInput

using namespace mInput;

#endif // ����mInput��namespace������Ȃ�