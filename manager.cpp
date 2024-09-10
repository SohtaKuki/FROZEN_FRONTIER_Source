//=================================================
//
// �|���S���`��̃}�l�[�W���[�Ǘ� (manager.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "object3D.h"
#include "objbg.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "block.h"
#include "item.h"
#include "camera.h"
#include "light.h"

CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pKeyboard = nullptr;
CInputJoypad* CManager::m_pJoypad = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CScene* CManager::m_pScene = nullptr;
CFade* CManager::m_pFade = nullptr;
CSound* CManager::m_pSound = nullptr;


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
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd,BOOL bWindow)
{
	m_pRenderer = new CRenderer;

	m_pKeyboard = new CInputKeyboard;

	m_pRenderer->Init(hWnd, bWindow);

	m_pSound = new CSound;

	m_pSound->Init(hWnd);

	m_pKeyboard->Init(hInstance, hWnd);

	m_pJoypad = new CInputJoypad();

	if (FAILED(m_pJoypad->Init()))
	{
		return E_FAIL;
	}

	m_pCamera = new CCamera();

	m_pCamera->Init();

	m_pLight = new CLight();

	m_pLight->Init();

	m_pScene = new CScene();

	m_pScene->Init();

	m_pFade = new CFade();
	
	m_pFade->Init();
	
	//SetMode(CScene::MODE::MODE_TITLE);

	//m_pFade->SetFade(CScene::MODE::MODE_TITLE);

	//CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f));


	//��2D�|���S�������̎c�[



	//CBlock::Create(D3DXVECTOR3(340.0f, 700.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),(CBlock::BLOCKTYPE::NORMAL));
	//CBlock::Create(D3DXVECTOR3(390.0f, 700.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),( CBlock::BLOCKTYPE::NORMAL));
	//CBlock::Create(D3DXVECTOR3(640.0f, 700.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), (CBlock::BLOCKTYPE::NORMAL));
	//CBlock::Create(D3DXVECTOR3(1000.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),(CBlock::BLOCKTYPE::NORMAL));
	//CBlock::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), (CBlock::BLOCKTYPE::NORMAL));

	//CItem::Create(D3DXVECTOR3(570.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//CPlayer::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//CEnemy::Create(D3DXVECTOR3(690.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));


	return S_OK;
}

//======================
// �I������
//======================
void CManager::Uninit()
{
	CObject::ReleaseAll();

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (m_pJoypad != nullptr)
	{
		m_pJoypad->Uninit();
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}

//======================
// �X�V����
//======================
void CManager::Update()
{
	m_pRenderer->Update();

	m_pKeyboard->Update();

	m_pJoypad->Update();

	m_pLight->Update();

	m_pCamera->Update();

	m_pScene->Update();

	m_pFade->Update();

}

//======================
// �`�揈��
//======================
void CManager::Draw()
{
	m_pRenderer->Draw();

	m_pFade->Draw();
}

//======================
// ���[�h�𐶐�
//======================
void CManager::SetMode(CScene::MODE mode)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	m_pScene = CScene::Create(mode);
}


//======================
// �����_���[�N���X�|�C���^�擾����
//======================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//======================
// �L�[�{�[�h�N���X�|�C���^�擾����
//======================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//============================
//�R���g���[���[�̎擾
//============================
CInputJoypad* CManager::GetJoypad()
{
	return m_pJoypad;
}

//======================
// �J�����N���X�|�C���^�擾����
//======================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//======================
// ���C�g�N���X�|�C���^�擾����
//======================
CLight* CManager::GetLight()
{
	return m_pLight;
}

//======================
// ���C�g�N���X�|�C���^�擾����
//======================
CFade* CManager::GetFade()
{
	return m_pFade;
}

CSound* CManager::GetSound()
{
	return m_pSound;
}



