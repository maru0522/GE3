#pragma once
#include "Obj3d.h"
#include <memory>
#include "Camera.h"
#include <DirectXMath.h>

class Player
{
public: // íËêî
    static constexpr float accel_{ 0.1f };
    static constexpr float maxSpeed_{ 0.3f };
    static constexpr float jumpDeceleration_{ 0.11f };
    static constexpr float gravity_{ 1.0f };
    static constexpr DirectX::XMFLOAT3 Radius_{ 1.0f,1.0f,1.0f };

public: // ä÷êî
    Player(Camera* pcamera);

    void Update(void);
    void Draw(void);

    inline void SetAirState(bool isAir) { isAir_ = isAir; }

private:
    void Move(void);
    void Jump(void);

    inline void ResetJumpTotal(void) { jumpTotal_y_ = 2.3f; }

public: // ïœêî
    std::unique_ptr<Obj3d> object_{};

    float jumpTotal_y_{ 2.3f };
    DirectX::XMFLOAT3 moveValue_{ };

    bool isJump_{ false };
    bool isAir_{ false };
};