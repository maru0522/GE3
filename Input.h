#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include "Window.h"
#include <array>
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <wrl.h>

namespace Input {
    class Keyboard
    {
    public: // �֐�
        static void Initialize();
        static void Update();

        // �������u��
        static bool IsTrigger(UINT8 key) { return !keysPre_[key] && keys_[key]; }

        // ������Ă���Ƃ�
        static bool IsDown(UINT8 key) { return keys_[key]; }

        // �����ꂽ�u��
        static bool IsReleased(UINT8 key) { return keysPre_[key] && !keys_[key]; }

    private: // �ϐ�
        // �G�C���A�X�e���v���[�g
        template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

        static ComPtr<IDirectInput8> directInput_; // DirectInput����
        static ComPtr<IDirectInputDevice8> keyboard_; // �L�[�{�[�h�f�o�C�X����
        static std::array<BYTE, 256> keysPre_;
        static std::array<BYTE, 256> keys_;
    };
};

#ifndef NON_NAMESPACE_Input

using KEY = Input::Keyboard;

#endif // ����Input��namespace������Ȃ�