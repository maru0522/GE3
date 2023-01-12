#include "Player.h"
#include "Input.h"

Player::Player(Camera* pcamera)
{
    object_ = std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", pcamera);
    object_->SetTextureById("main");
    object_->worldCoordinate_.rotation_.z = Util::Convert::DegToRad(90);
    object_->worldCoordinate_.scale_.z = 0.001f;
}

void Player::Update(void)
{
    Move();

    if (moveValue_.x > 0) {
        object_->SetTextureById("main");
    }
    else if (moveValue_.x < 0) {
        object_->SetTextureById("main2");
    }

    object_->Update();
}

void Player::Draw(void)
{
    object_->Draw();
}

void Player::Move(void)
{
    if (KEYS::IsDown(DIK_A) || KEYS::IsDown(DIK_D)) {
        if (std::abs(moveValue_.x) < maxSpeed_) moveValue_.x += (KEYS::IsDown(DIK_D) - KEYS::IsDown(DIK_A)) * accel_;
    }
    else {
        if (moveValue_.x > 0) {
            moveValue_.x -= accel_;
            if (moveValue_.x < 0) moveValue_.x = 0;
        }
        else {
            moveValue_.x += accel_;
            if (moveValue_.x > 0) moveValue_.x = 0;
        }
    }

    if (moveValue_.y < 0) moveValue_.y = 0;
    moveValue_.y -= gravity_;


    object_->worldCoordinate_.position_.x += moveValue_.x;
    object_->worldCoordinate_.position_.y += moveValue_.y;
    object_->worldCoordinate_.position_.z += moveValue_.z;

    Jump();

#ifdef _DEBUG
    if (KEYS::IsDown(DIK_NUMPAD8)) {
        object_->worldCoordinate_.position_.y += 0.2f;
    }
    if (KEYS::IsDown(DIK_NUMPAD2)) {
        object_->worldCoordinate_.position_.y -= 0.2f;
    }
#endif
}

void Player::Jump(void)
{
    if (KEYS::IsTrigger(DIK_SPACE) && isJump_ == false && isAir_ == false) {
        isJump_ = true;
        isAir_ = true;
    }

    if (isJump_) {
        object_->worldCoordinate_.position_.y += jumpTotal_y_;

        if (jumpTotal_y_ < 0) {
            isJump_ = false;
            ResetJumpTotal();
        }
        else {
            jumpTotal_y_ -= jumpDeceleration_;
        }
    }
}
