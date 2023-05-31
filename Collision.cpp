#include "Collision.h"
using namespace DirectX;
#include <cmath>

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter)
{
    // ���W�n�̌��_���狅�̒��S���W�ւ̋���
    XMVECTOR distV = XMVector3Dot(sphere.center_, plane.normal_);
    // ���ʂ̌��_���������Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
    float dist = distV.m128_f32[0] - plane.distance_;
    // �����̐�Βl�����a���傫����Γ������Ă��Ȃ�
    if (std::fabsf(dist) > sphere.radius_) return false;

    // �^�������_���v�Z
    if (inter) {
        // ���ʏ�̍ŋߐړ_���A�^����_�Ƃ���
        *inter = -dist * plane.normal_ + sphere.center_;
    }

    return true;
}
