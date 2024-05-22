//=================================================
//
// �|���S���`��̃}�l�[�W���[�Ǘ� (manager.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "objbg.h"
#include "player.h"

CRenderer* CManager::m_pRenderer = nullptr;

//======================
// �R���X�g���N�^
//======================
CManager::CManager()
{

}

//======================
// �f�X�g���N�^
//======================
CManager::~CManager()
{

}

//======================
// ����������
//======================
HRESULT CManager::Init(HWND hWnd,BOOL bWindow)
{
	m_pRenderer = new CRenderer;

	m_pRenderer->Init(hWnd, bWindow);

	CObjectBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	CObject2D::Create(D3DXVECTOR3(840.0f, 360.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	CPlayer::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	return S_OK;
}

//======================
// �I������
//======================
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

//======================
// �X�V����
//======================
void CManager::Update()
{
	m_pRenderer->Update();
}

//======================
// �`�揈��
//======================
void CManager::Draw()
{
	m_pRenderer->Draw();
}

//======================
// �����_���[�N���X�|�C���^�擾����
//======================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

