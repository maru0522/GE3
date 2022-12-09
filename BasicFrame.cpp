#include "BasicFrame.h"
#include "Input.h"
#include "Texture.h"
#include "GraphicsPipeline.h"

void BasicFrame::Run(void)
{
    Initialize();

    while (true)
    {
        Update();

        if (EndRequest()) {
            break;
        }

        Draw();
    }

    Finalize();
}

void BasicFrame::Initialize(void)
{
    // WinAPI������
    wnd_ = Window::GetInstance();

    // DirectX������
    iDX_ = InitDirectX::GetInstance();
    iDX_->Initialize();

    // Input������
    KEYS::Initialize();
    DPAD::Initialize();
    XPAD::Initialize();

    // graphicsPipeline������
    GraphicsPipeline::Initialize();

    imGuiController_ = std::make_unique<ImGuiController>();

    // �e�N�X�`��������
    Texture::Initialize();
}

void BasicFrame::Update(void)
{
    // �L�[�{�[�h���̎擾
    KEYS::Update();
    DPAD::Update();
    XPAD::Update();
}

void BasicFrame::Draw(void)
{
}

void BasicFrame::Finalize(void)
{
    // �E�B���h�E�N���X��o�^����
    wnd_->DelWindow();
}

bool BasicFrame::EndRequest(void)
{
    return !wnd_->GetKeepWindow();
}
