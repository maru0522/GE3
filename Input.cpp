#include "Input.h"
#include <cassert>

// ���̂̐���
Microsoft::WRL::ComPtr<IDirectInput8> Input::Keyboard::directInput_ = nullptr;
Microsoft::WRL::ComPtr<IDirectInputDevice8> Input::Keyboard::keyboard_ = nullptr;
std::array<BYTE, 256> Input::Keyboard::keysPre_ = { 0 };
std::array<BYTE, 256> Input::Keyboard::keys_ = { 0 };

void Input::Keyboard::Initialize()
{
    // �E�B���h�E�̃C���X�^���X�擾
    Window* wnd_ = Window::GetInstance();

    // DirectInput�̏�����
    HRESULT r = DirectInput8Create(
        wnd_->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, nullptr);
#ifdef _DEBUG
	assert(SUCCEEDED(r));
#endif // _DEBUG

    // �L�[�{�[�h�f�o�C�X�̐���
    r = directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
#ifdef _DEBUG
    assert(SUCCEEDED(r));
#endif // _DEBUG

    // ���̓f�[�^�`���̃Z�b�g
    r = keyboard_->SetDataFormat(&c_dfDIKeyboard); // �W���`��
#ifdef _DEBUG
    assert(SUCCEEDED(r));
#endif // _DEBUG

    // �r�����䃌�x���̃Z�b�g
    r = keyboard_->SetCooperativeLevel(
        wnd_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
#ifdef _DEBUG
    assert(SUCCEEDED(r));
#endif // _DEBUG
}

void Input::Keyboard::Update()
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