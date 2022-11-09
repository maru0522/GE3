#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<math.h>
using namespace DirectX;
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include<vector>
#include<string>
#include<DirectXTex.h>
#include<wrl.h>

#include "Window.h"
#include "Input.h"
#include "InitDirectX.h"
#include "Texture.h"
#include "Sprite.h"

using namespace Microsoft::WRL;

// 定数バッファ用データ構造体（3D変換行列）
struct ConstBufferDataTransform {
    XMMATRIX mat;		// 3D変換行列
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

#pragma region WindowsAPI初期化

    Window* wnd = Window::GetInstance();

#pragma endregion

#pragma region DirectX初期化

    InitDirectX* iDX = InitDirectX::GetInstance();
    iDX->Initialize();

#pragma region DirectInput初期化

    KEYS::Initialize();

#pragma endregion
#pragma endregion

#pragma region 描画初期化処理
#pragma region テクスチャ読み込み

    Texture::Initialize();
    Texture::Load("Resources/reimu.png");

#pragma endregion
#pragma endregion

#pragma region 変数宣言

    Sprite test{ "Resources/reimu.png" , CMode::PATH };

#pragma endregion

    // ゲームループ
    while (true) {

#pragma region ウィンドウメッセージ処理

        if (!wnd->GetKeepWindow()) {
            break;
        }

#pragma endregion

#pragma region DirextX毎フレーム処理
        // DirectX毎フレーム処理　ここから

#pragma region キーボード情報の取得

        KEYS::Update();

#pragma endregion


        test.Update();

        // DirectX毎フレーム処理　ここまで
#pragma endregion

#pragma region 描画前処理

        iDX->PreDraw();

#pragma endregion

#pragma region Draw()

        test.Draw();

#pragma endregion

#pragma region 描画後処理

        iDX->PostDraw();

#pragma endregion
    }

    // ウィンドウクラスを登録解除
    wnd->DelWindow();

    return 0;
}