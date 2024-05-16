//=================================================
//
// ポリゴンの描画処理 (main.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "main.h"


// マクロ定義
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "DirectXの基本処理"

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL; 
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;



//===============================
// メイン関数
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

    //画像サイズの構造体
    RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

    //ウインドウクラスの登録
    RegisterClassEx(&wcex);

    //クライアント領域を指定のサイズに調整
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    //ウインドウを作成
    hWnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,(rect.right - rect.left), (rect.bottom - rect.top), NULL, NULL, hInstance, NULL);

    //初期化処理
    if (FAILED(process.Init(hInstance, hWnd, TRUE)))
    {
        return -1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    //メッセージループ
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
                //メッセージの設定
                TranslateMessage(&msg); //仮想キーメッセージを文字メッセージへ変換
                DispatchMessage(&msg); //ウィンドウプロシージャへ送出
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
//ウィンドウプロシージャ
//===============================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int nID;

    switch (uMsg)
    {

    //ウィンドウ破壊
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    //キーが入力された時の場合
    case WM_KEYDOWN:
        switch (wParam)
        {
         //ESCキー入力時処理
        case VK_ESCAPE:
            nID = MessageBox(hWnd, "終了しますか？", "終了確認", MB_YESNO | MB_ICONQUESTION);
            if (nID == IDYES)
            {
                DestroyWindow(hWnd);
            }
        }


    //ウィンドウ上（×ボタン）入力時
    case WM_CLOSE:
        nID = MessageBox(hWnd, "終了しますか？", "終了確認", MB_YESNO | MB_ICONQUESTION);
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
//初期化処理
//===============================
HRESULT CProcess::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
    D3DDISPLAYMODE d3ddm;
    D3DPRESENT_PARAMETERS d3dpp;

    //Direct3Dオブジェクトの生成
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (g_pD3D == NULL)
    {
        return E_FAIL;
    }

    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        return E_FAIL;
    }

    //デバイスのプレゼンテーションパラメーターの設定

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

    //ポリゴンの初期化処理
    m_apPolygon->InitPolygon();

    return S_OK;
}

//===============================
//コンストラクタ
//===============================
CProcess::CProcess()
{

}

//===============================
//デストラクタ
//===============================
CProcess::~CProcess()
{

}

//===============================
//ポリゴンの初期化処理
//===============================
void CPolygon::InitPolygon()
{
    //頂点情報の設定
    m_aVertex[0].pos = D3DXVECTOR3(300.0f, 620.0f,0.0f);
    m_aVertex[1].pos = D3DXVECTOR3(300.0f, 100.0f, 0.0f);
    m_aVertex[2].pos = D3DXVECTOR3(1000.0f, 620.0f, 0.0f);
    m_aVertex[3].pos = D3DXVECTOR3(1000.0f, 100.0f, 0.0f);

    //rhwの設定
    m_aVertex[0].rhw = 1.0f;
    m_aVertex[1].rhw = 1.0f;
    m_aVertex[2].rhw = 1.0f;
    m_aVertex[3].rhw = 1.0f;

    //頂点カラーの設定
    m_aVertex[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_aVertex[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_aVertex[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_aVertex[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//===============================
//終了処理
//===============================
void CProcess::Uninit()
{
    //ポリゴンの終了処理
    m_apPolygon->UninitPolygon();

    //各種オブジェクトの終了処理

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
//ポリゴンの終了処理
//===============================
void CPolygon::UninitPolygon()
{

}

//===============================
//更新処理
//===============================
void CProcess::Update()
{
    m_apPolygon->UpdatePolygon();
}

//===============================
//描画処理
//===============================
void CProcess::Draw()
{
    //画面クリア
    g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

    //描画開始
    if (SUCCEEDED(g_pD3DDevice->BeginScene()))
    {
        //各種オブジェクトの描画処理
        m_apPolygon->DrawPolygon();

         //描画終了
        g_pD3DDevice->EndScene();
    }

    g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===============================
//ポリゴンの描画
//===============================
void CPolygon::DrawPolygon()
{
    //頂点フォーマット
    g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

    //ポリゴンの描画
    g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,&m_aVertex[0], sizeof(VERTEX_2D));

}

//===============================
//ポリゴンの更新
//===============================
void CPolygon::UpdatePolygon()
{

}

//===============================
//コンストラクタ
//===============================
CPolygon::CPolygon()
{

}

//===============================
//デストラクタ
//===============================
CPolygon::~CPolygon()
{

}
