//=================================================
//
// �J�������� (camera.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "camera.h"
#include "manager.h"


//======================
// �R���X�g���N�^
//======================
CCamera::CCamera()
{

}

//======================
// �f�X�g���N�^
//======================
CCamera::~CCamera()
{

}

//======================
// ����������
//======================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 110.0f, -700.0f);
	m_posR = D3DXVECTOR3(0.0f ,0.0f, 300.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = sqrtf((0.0f * 0.0f * 100.0f) + (m_posV.z * m_posV.z));

	return S_OK;
}

//======================
// �I������
//======================
void CCamera::Uninit()
{

}

//======================
// �X�V����
//======================
void CCamera::Update()
{
	if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
	{
		m_posV.x += 2.0f;
		m_posR.x += 2.0f;

	}

	if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
	{
		m_posV.x -= 2.0f;
		m_posR.x -= 2.0f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_UP))
	{
		m_posV.y += 2.0f;
		m_posR.y += 2.0f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_DOWN))
	{
		m_posV.y -= 2.0f;
		m_posR.y -= 2.0f;
	}


	if (CManager::GetKeyboard()->GetPress(DIK_F))
	{
		m_posV.z -= 6.0f;
		m_posR.z -= 6.0f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_R))
	{
		m_posV.z += 6.0f;
		m_posR.z += 6.0f;
	}
}

//======================
// �J�����̐ݒ菈��
//======================
void CCamera::SetCamera()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(50.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1800.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

