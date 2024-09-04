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

int CCamera::m_nShakeframe = 0;
float CCamera::m_fShake = 0.0f;

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
	m_posV = D3DXVECTOR3(0.0f, 700.0f, -460.0f);
	m_posR = D3DXVECTOR3(0.0f ,-600.0f, 200.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = sqrtf((0.0f * 0.0f * 100.0f) + (m_posV.z * m_posV.z));
	m_fStartPos = 10.0f;
	m_fEndPos = 10000.0f;
	m_fFogDisity = 0.00075f;
	m_fBlizCnt = 0.00075f;
	m_bBlizSwitch = false;

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
		m_posV.z = p3dPlayer->GetPos().z + 250.0f;
		m_posR.z = p3dPlayer->GetPos().z + 250.0f;
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

	//if (m_fFogDisity > 0.001f)
	//{
	//	m_bBlizSwitch = true;
	//}

	//if (m_fFogDisity < 0.00075f)
	//{
	//	m_bBlizSwitch = false;
	//}
	//
	//if (m_bBlizSwitch == false)
	//{
	//	m_fBlizCnt += 0.000005f;
	//}

	//if (m_bBlizSwitch == true)
	//{
	//	m_fBlizCnt -= 0.000005f;
	//}

	//m_fFogDisity += m_fBlizCnt;

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

	//�t�H�O�֌W�̏���
	pDevice->SetRenderState(D3DRS_FOGENABLE,TRUE);

	pDevice->SetRenderState(D3DRS_FOGCOLOR, 0x00FFFFFF);

	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);

	pDevice->SetRenderState(D3DRS_FOGDENSITY,*(DWORD*)(&m_fBlizCnt));

	pDevice->SetRenderState(D3DRS_SHADEMODE, 2);

	pDevice->SetRenderState(D3DRS_DEPTHBIAS, 1);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	//pDevice->SetRenderState(D3DRS_FOGSTART,*(DWORD*)(&m_fStartPos));
	//pDevice->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&m_fEndPos));


}


