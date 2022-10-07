#include "mInput.h"
#include <cassert>

// ���̂̐���
IDirectInput8* mInput::Keyboard::directInput = nullptr;
IDirectInputDevice8* mInput::Keyboard::keyboard = nullptr;
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
    // prekyes�֏��ۑ�
    for (size_t i = 0; i < 256; i++) {
        preKeys[i] = keys[i];
    }

    // �L�[�{�[�h���̎擾�J�n
    keyboard->Acquire();

    // �R���e�i�̒��g��S��0�Ŗ��߂�
    keys.fill(0);
    // �S�L�[�̓��͏�Ԃ��擾����
    keyboard->GetDeviceState(static_cast<DWORD>(size(keys)), keys.data());
}