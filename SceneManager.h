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
public: // ��`
private: // singleton
    SceneManager(void) = default;
    ~SceneManager(void) = default;
    SceneManager(const SceneManager& ins) = delete;
    SceneManager& operator=(const SceneManager& ins) = delete;
};