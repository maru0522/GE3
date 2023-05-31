#pragma once
#include <memory>
#include "Camera.h"
#include "Sprite.h"
#include "Obj3d.h"
#include "BaseScene.h"
#include "CollisionPrimitive.h"

using std::unique_ptr;

class GameScene : public BaseScene
{
public: // �֐�
    void Initialize(SceneManager* sceneManager) override;
    void Update(void) override;
    void Draw3d(void) override;
    void Draw2d(void) override;
    void Finalize(void) override;

private:
    std::unique_ptr<Camera> camera_{ std::make_unique<Camera>() };

    // �����蔻�� ��
    Sphere sphere_;
    // �����蔻�� ����
    Plane plane_;

    // ���̃I�u�W�F�N�g
    std::unique_ptr<Obj3d> sphereObj_{ std::make_unique<Obj3d>("Resources/3dModels/sphere/sphere.obj", camera_.get()) };
    // ���ʂ̃I�u�W�F�N�g
    std::unique_ptr<Obj3d> planeObj_{ std::make_unique<Obj3d>("Resources/3dModels/cube/cube.obj", camera_.get()) };

    float degree_{ 0 };
};

