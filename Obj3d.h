#pragma once
#include "Model.h"
#include "WorldCoordinate.h"
#include "Camera.h"

class Obj3d
{
private: // 定義
    using fsPath = std::experimental::filesystem::path;

public: // 静的関数
    static void PreDraw(void);

public: // 関数
    Obj3d(const fsPath& pathAndObjName);
    void Update(void);
    void Draw(void);


public: // 変数
    Camera* pCamera_{ nullptr };

    WorldCoordinate worldCoordinate_{ pCamera_ };

private: // 変数
    Model model_{};

    D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandleCopy_;
};