#pragma once
#include "Model.h"
#include "WorldCoordinate.h"
#include "Camera.h"
#include "GraphicsPipeline.h"

class Obj3d
{
private: // ��`
    using fsPath = std::experimental::filesystem::path;

public: // �ÓI�֐�
    static void PreDraw(void);

public: // �ÓI�ϐ�
    static GraphicsPipeline* graphicsPipeline_;

public: // �֐�
    Obj3d(void); // �z��p
    Obj3d(const fsPath& pathAndObjName);
    Obj3d(const fsPath& pathAndObjName, Camera* pCamera);
    void Update(void);
    void Draw(void);

    void SetCamera(Camera* pCamera) { worldCoordinate_.SetCamera(pCamera); }
public: // �ϐ�
    WorldCoordinate worldCoordinate_{};

private: // �ϐ�
    Model model_{};

    D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandleCopy_;
};