//=================================================
//
// ポリゴンの描画処理 (main.cpp)
// Author: Sohta Kuki
//
//=================================================
#include "main.h"
#include "object.h"
#include "object2D.h"

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// グローバル変数
CRenderer* g_pRenderer = nullptr;

//======================
// メイン関数
//======================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdline, _In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,		
		WindowProc,		
		0,								 
		0,								 
		hInstance,						 
		LoadIcon(NULL,IDI_APPLICATION),	 
		LoadCursor(NULL,IDC_ARROW),		 
		(HBRUSH)(COLOR_WINDOW + 1),		 
		NULL,							 
		"WindowClass",
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	// 画面サイズの構造体

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを生成
	hWnd = CreateWindowEx(0, "WindowClass", "C++環境下でのDirectX基本処理", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, (rect.right - rect.left), (rect.bottom - rect.top), NULL, NULL, hInstance, NULL);

	g_pRenderer = new CRenderer;


	if (FAILED(g_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f));

	//ウィンドウの表示
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
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
		}
		else
		{
			//レンダラー更新
			g_pRenderer->Update();

			//レンダラー描画
			g_pRenderer->Draw();
		}
	}

	//全オブジェクト開放
	CObject::ReleaseAll();

	//レンダラー開放
	delete g_pRenderer;
	g_pRenderer = nullptr;

	UnregisterClass("WindowClass", wcex.hInstance);

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

CRenderer* GetRenderer()
{
	return g_pRenderer;
}
