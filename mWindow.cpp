﻿#include "mWindow.h"
#include <string>
#include "mUtil.h"

static mWindow wnd;
mWindow* mWindow::GetInstance()
{
    return &wnd;
}

LRESULT mWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    // メッセージに応じてゲーム固有の処理を行う
    switch (msg) {
        // ウィンドウが破棄された
        case WM_DESTROY:
            // OSに対して、アプリの終了を伝える
            PostQuitMessage(0);
            return 0;
    }

    // 標準のメッセージ処理を行う
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

const wchar_t mWindow::windowClassName_[] = L"maruyamaEngine";

mWindow::mWindow()
{
    // ウィンドウクラスの設定
    w_.cbSize = sizeof(WNDCLASSEX);
    w_.lpfnWndProc = static_cast<WNDPROC>(WindowProc);   // ウィンドウプロシージャを設定
    w_.lpszClassName = windowClassName_;                  // ウィンドウクラス名
    w_.hInstance = GetModuleHandle(nullptr);             // ウィンドウハンドル
    w_.hCursor = LoadCursor(NULL, IDC_ARROW);            // カーソル指定

    // ウィンドウクラスをOSに登録する
    RegisterClassEx(&w_);

    // ウィンドウサイズ{ X座標 Y座標 横幅 縦幅 }
    RECT wrc = { 0, 0, width_, height_ };
    // 自動でサイズを補正する
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

    // ウィンドウオブジェクトの生成
    hwnd_ = CreateWindow(
        w_.lpszClassName,     // クラス名
        windowClassName_,     // タイトルバーの文字
        WS_OVERLAPPEDWINDOW,  // 標準的なウィンドウスタイル
        CW_USEDEFAULT,        // 表示X座標（OSに任せる）
        CW_USEDEFAULT,        // 表示Y座標（OSに任せる）
        wrc.right - wrc.left, // ウィンドウ横幅
        wrc.bottom - wrc.top, // ウィンドウ縦幅
        nullptr,              // 親ウィンドウハンドル
        nullptr,              // メニューハンドル
        w_.hInstance,         // 呼び出しアプリケーションハンドル
        nullptr               // オプション
    );

    // ウィンドウを表示状態にする
    ShowWindow(hwnd_, SW_SHOW);
}

mWindow::mWindow(const char* title)
{
    // ウィンドウクラスの設定
    w_.cbSize = sizeof(WNDCLASSEX);
    w_.lpfnWndProc = static_cast<WNDPROC>(WindowProc);   // ウィンドウプロシージャを設定
    w_.lpszClassName = windowClassName_;                  // ウィンドウクラス名
    w_.hInstance = GetModuleHandle(nullptr);             // ウィンドウハンドル
    w_.hCursor = LoadCursor(NULL, IDC_ARROW);            // カーソル指定

    // ウィンドウクラスをOSに登録する
    RegisterClassEx(&w_);

    // ウィンドウサイズ{ X座標 Y座標 横幅 縦幅 }
    RECT wrc = { 0, 0, width_, height_ };
    // 自動でサイズを補正する
    AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

    // ウィンドウタイトルをwstring(wchar_t)に変換
    std::wstring wstrTitle = Convert::CharToWString(title);

    // ウィンドウオブジェクトの生成
    hwnd_ = CreateWindow(
        w_.lpszClassName,     // クラス名
        wstrTitle.c_str(),    // タイトルバーの文字
        WS_OVERLAPPEDWINDOW,  // 標準的なウィンドウスタイル
        CW_USEDEFAULT,        // 表示X座標 (OSに任せる)
        CW_USEDEFAULT,        // 表示Y座標 (OSに任せる)
        wrc.right - wrc.left, // ウィンドウ横幅
        wrc.bottom - wrc.top, // ウィンドウ縦幅
        nullptr,              // 親ウィンドウハンドル
        nullptr,              // メニューハンドル
        w_.hInstance,          // 呼び出しアプリケーションハンドル
        nullptr               // オプション
    );

    // ウィンドウを表示状態にする
    ShowWindow(hwnd_, SW_SHOW);
}

void mWindow::DelWindow()
{
    UnregisterClass(w_.lpszClassName, w_.hInstance);
}

void mWindow::SetDisplay(int nCmdShow)
{
    ShowWindow(hwnd_, nCmdShow);
}

bool mWindow::GetKeepWindow()
{
    // メッセージ
    MSG msg{};

    // メッセージがある？
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);     // キー入力メッセージの処理
        DispatchMessage(&msg);      // プロシージャにメッセージを送る
    }

    // ✖ボタンで終了メッセージが来たらゲームループを抜ける
    return msg.message != WM_QUIT;
}
