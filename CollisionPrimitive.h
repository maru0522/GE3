#pragma once
#include <DirectXMath.h>

struct Sphere
{
    // ���S���W
    DirectX::XMVECTOR center_{ 0,0,0,1 };
    // ���a
    float radius_{ 1.f };
};

struct Plane
{
    // �@���x�N�g��
    DirectX::XMVECTOR normal_{ 0,1,0,0 };
    // ���_(0,0,0)��̋���
    float distance_{ 0.f };
};

class CollisionPrimitive
{
};

