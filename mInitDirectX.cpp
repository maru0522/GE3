#include "mInitDirectX.h"
#include <cassert>
#include <vector>
#include "mWindow.h"

void mInitDirectX::Device(void)
{
#pragma region �A�_�v�^�̗�
	// DXGI�t�@�N�g���[�̐���
	HRESULT r = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory_));

#ifdef _DEBUG
	assert(SUCCEEDED(r));
#endif // _DEBUG

	// �A�_�v�^�[�̗񋓗p
	std::vector<ComPtr<IDXGIAdapter4>> adapters;

	// �����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	ComPtr<IDXGIAdapter4> tmpAdapter = nullptr;

	// �p�t�H�[�}���X���������̂��珇�ɁA�S�ẴA�_�v�^�[��񋓂���
	for (UINT i = 0;
		dxgiFactory_->EnumAdapterByGpuPreference( // �����̈�����UINT�̂��� i �̌^��size_t�łȂ�
			i,
			DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++) {

		// ���I�z��ɒǉ�����
		adapters.push_back(tmpAdapter);
	}
#pragma endregion

#pragma region �A�_�v�^�̑I��
	// �Ó��ȃA�_�v�^��I�ʂ���
	for (size_t i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC3 adapterDesc;

		// �A�_�v�^�[�̏����擾����
		adapters[i]->GetDesc3(&adapterDesc);

		// �\�t�g�E�F�A�f�o�C�X�����
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			// �f�o�C�X���̗p���ă��[�v�𔲂���
			tmpAdapter = adapters.at(i);

			break;
		}
	}
#pragma endregion

#pragma region �f�o�C�X�̐���
	// �Ή����x���̔z��
	std::vector<D3D_FEATURE_LEVEL> levels{
	 D3D_FEATURE_LEVEL_12_1,
	 D3D_FEATURE_LEVEL_12_0,
	 D3D_FEATURE_LEVEL_11_1,
	 D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;
	for (size_t i = 0; i < levels.size(); i++) {
		// �̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		r = D3D12CreateDevice(tmpAdapter.Get(), levels.at(i),
			IID_PPV_ARGS(&device_));

		if (r == S_OK) {
			// �f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
			featureLevel = levels.at(i);
			break;
		}
	}
#pragma endregion
}

void mInitDirectX::Command(void)
{
#pragma region �R�}���h�A���P�[�^
	// �R�}���h�A���P�[�^�𐶐�
 	HRESULT r = device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator_));

#ifdef _DEBUG
	assert(SUCCEEDED(r));
#endif // _DEBUG
#pragma endregion

#pragma region �R�}���h���X�g�̐���
	// �R�}���h���X�g�𐶐�
	r = device_->CreateCommandList(0,D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator_.Get(), nullptr, IID_PPV_ARGS(&commandList_));

#ifdef _DEBUG
	assert(SUCCEEDED(r));
#endif // _DEBUG
#pragma endregion

#pragma region �R�}���h�L���[�̐���
	//�R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	//�R�}���h�L���[�𐶐�
	r = device_->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue_));

#ifdef _DEBUG
	assert(SUCCEEDED(r));
#endif // _DEBUG
#pragma endregion
}

void mInitDirectX::SwapChain(void)
{
	mWindow* wnd = mWindow::GetInstance();

#pragma region �X���b�v�`�F�[���̐���
	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = 1280;
	swapChainDesc.Height = 720;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �F���̏���
	swapChainDesc.SampleDesc.Count = 1; // �}���`�T���v�����Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER; // �o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2; // �o�b�t�@�����Q�ɐݒ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // �t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// IDXGISwapChain1��tmp
	ComPtr<IDXGISwapChain1> swapChain1Tmp;

	// �X���b�v�`�F�[���̐���
	HRESULT r = dxgiFactory_->CreateSwapChainForHwnd(commandQueue_.Get(), wnd->GetHwnd(), &swapChainDesc, nullptr, nullptr, &swapChain1Tmp);

#ifdef _DEBUG
	assert(SUCCEEDED(r));
#endif // _DEBUG

	// ��������IDXGISwapChain1�̃I�u�W�F�N�g��IDXGISwapChain4�ɕϊ�����
	swapChain1Tmp.As(&swapChain_);
#pragma endregion
}