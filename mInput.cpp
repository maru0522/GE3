#include "mInput.h"
#include <cassert>

// ���̂̐���
Microsoft::WRL::ComPtr<IDirectInput8> mInput::Keyboard::directInput_ = nullptr;
Microsoft::WRL::ComPtr<IDirectInputDevice8> mInput::Keyboard::keyboard_ = nullptr;
std::array<BYTE, 256> mInput::Keyboard::keysPre_ = { 0 };
std::array<BYTE, 256> mInput::Keyboard::keys_ = { 0 };

void mInput::Keyboard::Initialize()
{
    HRESULT result = S_FALSE;

    // �E�B���h�E�̃C���X�^���X�擾
    mWindow* wnd_ = mWindow::GetInstance();

    // DirectInput�̏�����
    result = DirectInput8Create(
        wnd_->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, nullptr);
    assert(SUCCEEDED(result));

    // �L�[�{�[�h�f�o�C�X�̐���
    result = directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
    assert(SUCCEEDED(result));

    // ���̓f�[�^�`���̃Z�b�g
    result = keyboard_->SetDataFormat(&c_dfDIKeyboard); // �W���`��
    assert(SUCCEEDED(result));

    // �r�����䃌�x���̃Z�b�g
    result = keyboard_->SetCooperativeLevel(
        wnd_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void mInput::Keyboard::Update()
{
    // preKeys�֏��ۑ�
    memcpy(keysPre_.data(), keys_.data(), sizeof(keys_));

    // �L�[�{�[�h���̎擾
    keyboard_->Acquire();

    // �L�[�̓��͏�Ԃ̏�����
    keys_.fill(0);

    // �L�[�S�Ă̓��͏�Ԃ̎擾
    keyboard_->GetDeviceState(static_cast<DWORD>(size(keys_)), keys_.data());
}