#pragma once
#include <Windows.h>

class mWindow
{
public: // �ÓI�֐�
    static mWindow* GetInstance(); // �C���X�^���X���擾
    static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // �ÓI�ϐ�
    // �E�B���h�E�T�C�Y
    static const size_t width = 1280;
    static const size_t height = 720;

    // �E�B���h�E�N���X��
    static const wchar_t windowClassName[];

public: // �֐�
    mWindow();
    mWindow(const char* title);
    void DelWindow();

    // �E�B���h�E�̕\����Ԃ�ύX����֐�
    // �f�t�H���g:nCmdShow = SW_SHOW
    void SetDisplay(int nCmdShow);

    // �E�B���h�E�Œ�p�̃��b�Z�[�W���[�v����
    // WM_QUIT�Ȃ�FALSE��Ԃ�
    bool IsKeep();

    // �E�B���h�E�n���h���̎擾
    // const: �����n�����郁���o�ϐ��̃����o�֐������ɂ�����ύX�̋֎~
    HWND GetHwnd() const { return hwnd; }

    HINSTANCE GetHInstance() const { return w.hInstance; }

private: // �ϐ�
    // �E�B���h�E�N���X�̐���
    WNDCLASSEX w{};

    // �E�B���h�E�n���h���̐���
    HWND hwnd;
};