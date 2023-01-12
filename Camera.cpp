#include "Camera.h"
namespace {
    constexpr float __ZERO = 0.0f;
}

Camera::Camera(void)
{
}

void Camera::Update(void)
{
    matView_ = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eye_), DirectX::XMLoadFloat3(&target_), DirectX::XMLoadFloat3(&up_));
}

void Camera::SetProjection(CameraProjection projectionType)
{
    if (projectionType == CameraProjection::ORTHOGRAPHIC) {
        // ïΩçsìäâe
        //nearZ_ = 1.0f;
        matProjection_ = DirectX::XMMatrixOrthographicOffCenterLH(__ZERO, float{ Window::width_ }, __ZERO - 250.0f, float{ Window::height_ + 50.0f }, nearZ_, farZ_);
        projectionState_ = false; // ORTHOGRAPHIC
    }
    else {
        // ìßéãìäâe
        //nearZ_ = 0.1f;
        matProjection_ = DirectX::XMMatrixPerspectiveFovLH(Util::Convert::DegToRad(45.0f), (float)Window::width_ / Window::height_, nearZ_, farZ_);
        projectionState_ = true; // PERSPECTIVE
    }
}
