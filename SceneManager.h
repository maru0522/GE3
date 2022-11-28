#pragma once
class SceneAB
{
public: //�@�֐�
    virtual void Initialize(void) = 0;
    virtual void Update(void) = 0;
    virtual void Draw(void) = 0;
};

class SceneManager
{
public: // �ÓI�֐�
    template<class Scene> static void Transition(void);
};