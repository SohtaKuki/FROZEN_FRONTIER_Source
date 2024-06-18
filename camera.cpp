//=================================================
//
// �J�������� (camera.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "camera.h"
#include "manager.h"
#include "object.h"
#include "3dplayer.h"


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
	m_posV = D3DXVECTOR3(0.0f, 800.0f, -460.0f);
	m_posR = D3DXVECTOR3(0.0f ,-600.0f, 200.0f);
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
	CObject* pObj = CObject::GetObj(3, 1);

	if (pObj != nullptr)
	{
		CObject::TYPE type = pObj->GetType();

		C3dplayer* p3dPlayer = (C3dplayer*)pObj;

		//D3DXVECTOR3 PlayerPos = p3dPlayer->GetPos();

		m_posV.x = p3dPlayer->GetPos().x;
		m_posR.x = p3dPlayer->GetPos().x;
		m_posV.z = p3dPlayer->GetPos().z + 200.0f;
		m_posR.z = p3dPlayer->GetPos().z + 200.0f;
	}

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

	if (CManager::GetKeyboard()->GetPress(DIK_E))
	{
		m_rot.y += 0.03f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_Q))
	{
		m_rot.y -= 0.03f;
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

	if (CManager::GetKeyboard()->GetPress(DIK_P))
	{
		SetShake(60,10.0f);
	}

	m_posV.x = m_posR.x - sinf(m_rot.y) * 600;
	m_posV.z = m_posR.z - cosf(m_rot.y) * 600;
}

void CCamera::SetShake(int shakeframe, float shake)
{
	m_nShakeframe = shakeframe;
	m_fShake = shake;
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
	//D3DXMatrixOrthoLH(&m_mtxProjection, (float)SCREEN_WIDTH ,(float)SCREEN_HEIGHT, 10.0f, 1800.0f);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(30.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1800.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 adjust = D3DXVECTOR3(0, 0, 0);

	D3DXVECTOR3 PosV = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 PosR = D3DXVECTOR3(0, 0, 0);

	if (m_nShakeframe > 0)
	{
		m_nShakeframe--;
		adjust = D3DXVECTOR3(rand() & (int)m_fShake,rand() & (int)m_fShake, rand() & (int)m_fShake);
	}

	PosV = m_posV + adjust;
	PosR = m_posR + adjust;

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &PosV, &PosR, &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}


