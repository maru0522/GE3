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
public: // �֐�
    Camera(void);
    void Update(void);

    void SetProjection(CameraProjection projectionType);

    const DirectX::XMMATRIX& GetProjection(void) const { return matProjection_; }
    const DirectX::XMMATRIX& GetView(void) const { return matView_; }
    const bool GetProjectionState(void) const { return projectionState_; }

public: // �ϐ�
    DirectX::XMFLOAT3 eye_{ 0.0f, 0.0f, -100.0f };       // ���_���W
    DirectX::XMFLOAT3 target_{ 0.0f, 0.0f, 0.0f };       // �����_���W
    DirectX::XMFLOAT3 up_{ 0.0f, 1.0f, 0.0f };           // ������x�N�g��
private: // �ϐ�
        // �G�C���A�X�e���v���[�g
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

    // �������e
    float_t nearZ_{ 0.1f }; // �O�[
    float_t farZ_{ 500.0f }; // ���[
    DirectX::XMMATRIX matProjection_{ DirectX::XMMatrixPerspectiveFovLH(Util::Convert::DegToRad(45.0f), (float)Window::width_ / Window::height_, nearZ_, farZ_) };

    // �r���[�ϊ��s��
    DirectX::XMMATRIX matView_{ DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eye_), DirectX::XMLoadFloat3(&target_), DirectX::XMLoadFloat3(&up_)) };

    bool projectionState_{ static_cast<bool>(CameraProjection::PERSPECTIVE) };
};