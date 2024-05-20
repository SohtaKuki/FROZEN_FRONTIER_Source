#include "renderer.h"
#include "object.h"

CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
}

CRenderer::~CRenderer()
{

}

HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);


	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
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

	
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp,&m_pD3DDevice)))
	{

	}

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

void CRenderer::Uninit()
{
	 
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

void CRenderer::Update()
{

	CObject::UpdateAll();
}

void CRenderer::Draw()
{
	
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	 
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �S�ĕ`��
		CObject::DrawAll();

		m_pD3DDevice->EndScene();
	}

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}