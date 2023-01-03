#include "Camera.h"

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
        matProjection_ = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, Window::width_, Window::height_, 0.0f, 0.0f, 1.0f);
        projectionState_ = false; // ORTHOGRAPHIC
    }
    else {
        // ìßéãìäâe
        matProjection_ = DirectX::XMMatrixPerspectiveFovLH(Util::Convert::DegToRad(45.0f), (float)Window::width_ / Window::height_, nearZ_, farZ_);
        projectionState_ = true; // PERSPECTIVE
    }
}
