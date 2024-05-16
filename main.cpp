//=================================================
//
// �|���S���̕`�揈�� (main.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "main.h"


// �}�N����`
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "DirectX�̊�{����"

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL; 
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;



//===============================
// ���C���֐�
//===============================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    CProcess process;

    WNDCLASSEX wcex = 
    {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        WindowProc,
        0,
        0,
        hInstance,
        LoadIcon(NULL, IDI_APPLICATION),
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        NULL,
        CLASS_NAME,
        LoadIcon(NULL, IDI_APPLICATION),
    };

    HWND hWnd;
    MSG msg;

    //�摜�T�C�Y�̍\����
    RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

    //�E�C���h�E�N���X�̓o�^
    RegisterClassEx(&wcex);

    //�N���C�A���g�̈���w��̃T�C�Y�ɒ���
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    //�E�C���h�E���쐬
    hWnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,(rect.right - rect.left), (rect.bottom - rect.top), NULL, NULL, hInstance, NULL);

    //����������
    if (FAILED(process.Init(hInstance, hWnd, TRUE)))
    {
        return -1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    //���b�Z�[�W���[�v
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                //���b�Z�[�W�̐ݒ�
                TranslateMessage(&msg); //���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
                DispatchMessage(&msg); //�E�B���h�E�v���V�[�W���֑��o
            }
        }
        else
        {
            process.Update();

            process.Draw();
        }
    }

    process.Uninit();

    UnregisterClass(CLASS_NAME, wcex.hInstance);

    return (int)msg.wParam;
}

//===============================
//�E�B���h�E�v���V�[�W��
//===============================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int nID;

    switch (uMsg)
    {

    //�E�B���h�E�j��
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    //�L�[�����͂��ꂽ���̏ꍇ
    case WM_KEYDOWN:
        switch (wParam)
        {
         //ESC�L�[���͎�����
        case VK_ESCAPE:
            nID = MessageBox(hWnd, "�I�����܂����H", "�I���m�F", MB_YESNO | MB_ICONQUESTION);
            if (nID == IDYES)
            {
                DestroyWindow(hWnd);
            }
        }


    //�E�B���h�E��i�~�{�^���j���͎�
    case WM_CLOSE:
        nID = MessageBox(hWnd, "�I�����܂����H", "�I���m�F", MB_YESNO | MB_ICONQUESTION);
        if (nID == IDYES)
        {
            DestroyWindow(hWnd);
        }
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

//===============================
//����������
//===============================
HRESULT CProcess::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
    D3DDISPLAYMODE d3ddm;
    D3DPRESENT_PARAMETERS d3dpp;

    //Direct3D�I�u�W�F�N�g�̐���
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (g_pD3D == NULL)
    {
        return E_FAIL;
    }

    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    //�f�o�C�X�̃v���[���e�[�V�����p�����[�^�[�̐ݒ�

    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.BackBufferWidth = SCREEN_WIDTH;

    d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    d3dpp.BackBufferFormat = d3ddm.Format;
    d3dpp.BackBufferCount = 1;

    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.EnableAutoDepthStencil = TRUE;

    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.Windowed = bWindow;
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;


    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
    {
        if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
        {
            if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
            {
                return E_FAIL;
            }
        }

    }

    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

    g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

    g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    //�|���S���̏���������
    m_apPolygon->InitPolygon();

    return S_OK;
}

//===============================
//�R���X�g���N�^
//===============================
CProcess::CProcess()
{

}

//===============================
//�f�X�g���N�^
//===============================
CProcess::~CProcess()
{

}

//===============================
//�|���S���̏���������
//===============================
void CPolygon::InitPolygon()
{
    //���_���̐ݒ�
    m_aVertex[0].pos = D3DXVECTOR3(300.0f, 620.0f,0.0f);
    m_aVertex[1].pos = D3DXVECTOR3(300.0f, 100.0f, 0.0f);
    m_aVertex[2].pos = D3DXVECTOR3(1000.0f, 620.0f, 0.0f);
    m_aVertex[3].pos = D3DXVECTOR3(1000.0f, 100.0f, 0.0f);

    //rhw�̐ݒ�
    m_aVertex[0].rhw = 1.0f;
    m_aVertex[1].rhw = 1.0f;
    m_aVertex[2].rhw = 1.0f;
    m_aVertex[3].rhw = 1.0f;

    //���_�J���[�̐ݒ�
    m_aVertex[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_aVertex[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_aVertex[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_aVertex[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//===============================
//�I������
//===============================
void CProcess::Uninit()
{
    //�|���S���̏I������
    m_apPolygon->UninitPolygon();

    //�e��I�u�W�F�N�g�̏I������

    if (g_pD3DDevice != NULL)
    {
        g_pD3DDevice->Release();
        g_pD3DDevice = NULL;
    }

    if(g_pD3D != NULL)
    {
        g_pD3D->Release();
        g_pD3D = NULL;
    }
}

//===============================
//�|���S���̏I������
//===============================
void CPolygon::UninitPolygon()
{

}

//===============================
//�X�V����
//===============================
void CProcess::Update()
{
    m_apPolygon->UpdatePolygon();
}

//===============================
//�`�揈��
//===============================
void CProcess::Draw()
{
    //��ʃN���A
    g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

    //�`��J�n
    if (SUCCEEDED(g_pD3DDevice->BeginScene()))
    {
        //�e��I�u�W�F�N�g�̕`�揈��
        m_apPolygon->DrawPolygon();

         //�`��I��
        g_pD3DDevice->EndScene();
    }

    g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===============================
//�|���S���̕`��
//===============================
void CPolygon::DrawPolygon()
{
    //���_�t�H�[�}�b�g
    g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

    //�|���S���̕`��
    g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,&m_aVertex[0], sizeof(VERTEX_2D));

}

//===============================
//�|���S���̍X�V
//===============================
void CPolygon::UpdatePolygon()
{

}

//===============================
//�R���X�g���N�^
//===============================
CPolygon::CPolygon()
{

}

//===============================
//�f�X�g���N�^
//===============================
CPolygon::~CPolygon()
{

}
