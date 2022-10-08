#include "mInput.h"
#include <cassert>

// ���̂̐���
Microsoft::WRL::ComPtr<IDirectInput8> mInput::Keyboard::directInput = nullptr;
Microsoft::WRL::ComPtr<IDirectInputDevice8> mInput::Keyboard::keyboard = nullptr;
std::array<BYTE, 256> mInput::Keyboard::preKeys = { 0 };
std::array<BYTE, 256> mInput::Keyboard::keys = { 0 };

void mInput::Keyboard::Initialize()
{
    HRESULT result = S_FALSE;

    // �E�B���h�E�̃C���X�^���X�擾
    mWindow* wnd_ = mWindow::GetInstance();

    // DirectInput�̏�����
    result = DirectInput8Create(
        wnd_->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // �L�[�{�[�h�f�o�C�X�̐���
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    assert(SUCCEEDED(result));

    // ���̓f�[�^�`���̃Z�b�g
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
    assert(SUCCEEDED(result));

    // �r�����䃌�x���̃Z�b�g
    result = keyboard->SetCooperativeLevel(
        wnd_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void mInput::Keyboard::Update()
{
    // preKeys�֏��ۑ�
    memcpy(preKeys.data(), keys.data(), sizeof(keys));

    // �L�[�{�[�h���̎擾
    keyboard->Acquire();

    // �L�[�̓��͏�Ԃ̏�����
    keys.fill(0);

    // �L�[�S�Ă̓��͏�Ԃ̎擾
    keyboard->GetDeviceState(static_cast<DWORD>(size(keys)), keys.data());
}