#pragma once
#include <DirectXMath.h>

struct Sphere
{
    // 中心座標
    DirectX::XMVECTOR center_{ 0,0,0,1 };
    // 半径
    float radius_{ 1.f };
};

struct Plane
{
    // 法線ベクトル
    DirectX::XMVECTOR normal_{ 0,1,0,0 };
    // 原点(0,0,0)空の距離
    float distance_{ 0.f };
};

class CollisionPrimitive
{
};

