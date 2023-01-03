#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include "Window.h"
#include "Util.h"
#include <d3d12.h>

#pragma comment(lib,"d3d12.lib")

enum class CameraProjection {
    ORTHOGRAPHIC,
    PERSPECTIVE
};

class Camera
{
public: // 関数
    Camera(void);
    void Update(void);

    void SetProjection(CameraProjection projectionType);

    const DirectX::XMMATRIX& GetProjection(void) const { return matProjection_; }
    const DirectX::XMMATRIX& GetView(void) const { return matView_; }
    const bool GetProjectionState(void) const { return projectionState_; }

public: // 変数
    DirectX::XMFLOAT3 eye_{ 0.0f, 0.0f, -100.0f };       // 視点座標
    DirectX::XMFLOAT3 target_{ 0.0f, 0.0f, 0.0f };       // 注視点座標
    DirectX::XMFLOAT3 up_{ 0.0f, 1.0f, 0.0f };           // 上方向ベクトル
private: // 変数
        // エイリアステンプレート
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

    // 透視投影
    float_t nearZ_{ 0.1f }; // 前端
    float_t farZ_{ 1000.0f }; // 奥端
    DirectX::XMMATRIX matProjection_{ DirectX::XMMatrixPerspectiveFovLH(Util::Convert::DegToRad(45.0f), (float)Window::width_ / Window::height_, nearZ_, farZ_) };

    // ビュー変換行列
    DirectX::XMMATRIX matView_{ DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eye_), DirectX::XMLoadFloat3(&target_), DirectX::XMLoadFloat3(&up_)) };

    bool projectionState_{ static_cast<bool>(CameraProjection::PERSPECTIVE) };
};