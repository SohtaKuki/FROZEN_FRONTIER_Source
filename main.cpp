//=================================================
//
// �|���S���̕`�揈�� (main.cpp)
// Author: Sohta Kuki
//
//=================================================
#include "main.h"
#include "object.h"
#include "object2D.h"

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �O���[�o���ϐ�
CRenderer* g_pRenderer = nullptr;

//======================
// ���C���֐�
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

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	// ��ʃT�C�Y�̍\����

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0, "WindowClass", "C++�����ł�DirectX��{����", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, (rect.right - rect.left), (rect.bottom - rect.top), NULL, NULL, hInstance, NULL);

	g_pRenderer = new CRenderer;


	if (FAILED(g_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f));

	//�E�B���h�E�̕\��
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
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
		}
		else
		{
			//�����_���[�X�V
			g_pRenderer->Update();

			//�����_���[�`��
			g_pRenderer->Draw();
		}
	}

	//�S�I�u�W�F�N�g�J��
	CObject::ReleaseAll();

	//�����_���[�J��
	delete g_pRenderer;
	g_pRenderer = nullptr;

	UnregisterClass("WindowClass", wcex.hInstance);

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

CRenderer* GetRenderer()
{
	return g_pRenderer;
}
