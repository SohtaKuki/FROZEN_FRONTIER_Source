#include "manager.h"
#include "renderer.h"
#include "object2D.h"

CRenderer* CManager::m_pRenderer = nullptr;

CManager::CManager()
{

}

CManager::~CManager()
{

}

HRESULT CManager::Init(HWND hWnd,BOOL bWindow)
{
	m_pRenderer = new CRenderer;

	m_pRenderer->Init(hWnd, bWindow);

	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	return S_OK;
}

void CManager::Uninit()
{
	CObject::ReleaseAll();

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

void CManager::Update()
{
	m_pRenderer->Update();
}

void CManager::Draw()
{
	m_pRenderer->Draw();
}

CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

