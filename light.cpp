//=================================================
//
// ���C�g���� (light.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "light.h"
#include "main.h"
#include "object.h"


CLight::CLight()
{
	//���C�g�̏����N���A����
	ZeroMemory(&m_alight, sizeof(D3DLIGHT9));
}

CLight::~CLight()
{

}

//======================
// ����������
//======================
HRESULT CLight::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];

	m_alight->Type = D3DLIGHT_DIRECTIONAL;

	m_alight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			//���C�g�̕�����ݒ�
			vecDir[nCnt] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
			break;
		case 1:
			//���C�g�̕�����ݒ�
			vecDir[nCnt] = D3DXVECTOR3(0.5f, 0.6f, 0.7f);
			break;
		case 2:
			//���C�g�̕�����ݒ�
			vecDir[nCnt] = D3DXVECTOR3(1.3f, 0.5f, 2.6f);
			break;
		case 3:
			//���C�g�̕�����ݒ�
			vecDir[nCnt] = D3DXVECTOR3(-1.5f, 0.5f, 1.6f);
			break;
		}
	}

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		m_alight->Direction = vecDir[nCnt];

		//���C�g��ݒ�
		pDevice->SetLight(nCnt, m_alight);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//======================
// �I������
//======================
void CLight::Uninit()
{

}

//======================
// �X�V����
//======================
void CLight::Update()
{

}