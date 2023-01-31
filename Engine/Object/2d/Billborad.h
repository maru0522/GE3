#pragma once
#include <array>
#include <DirectXMath.h>
#include <wrl.h>
#include "ConstBuffer.h"
#include <string>
#include "Window.h"
#if _MSC_VER > 1922 && !defined(_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif
#include <experimental/filesystem>
#include "GraphicsPipeline.h"
#include <d3d12.h>

#pragma comment(lib,"d3d12.lib")

class Billborad
{
private: // 定義
    // エイリアステンプレート
    template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // 変数
    // テクスチャ情報の引き出しハンドル
    D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandleCopy_{};
    DirectX::XMFLOAT2 originalSize_{}; // テクスチャの全体サイズ

#pragma region 頂点
    //std::array<VertexSprite_st, 4> vertices_{}; // 頂点データ
    ComPtr<ID3D12Resource> vertBuff_{ nullptr }; // 頂点バッファの生成
    D3D12_VERTEX_BUFFER_VIEW vbView_{}; // 頂点バッファビューの作成
#pragma endregion
};

