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

	D3DXVECTOR4 vecDir[MAX_LIGHT];

	m_alight->Type = D3DLIGHT_DIRECTIONAL;

	m_alight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			// ���C�g�̕�����ݒ�
			vecDir[nCnt] = D3DXVECTOR4(0.2f, -0.8f, -0.4f, 0.0f); 
			break;
		case 1:
			// ���C�g�̕�����ݒ�
			vecDir[nCnt] = D3DXVECTOR4(0.5f, 0.6f, 0.7f, 0.0f);
			break;
		case 2:
			// ���C�g�̕�����ݒ�
			vecDir[nCnt] = D3DXVECTOR4(0.9f, 0.5f, 0.6f, 0.0f);
			break;
		case 3:
			// ���C�g�̕�����ݒ�
			vecDir[nCnt] = D3DXVECTOR4(-0.9f, 0.5f, 0.5f, 0.0f); 
			break;
		}
	}

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		// ���C�g�̕����x�N�g���𐳋K��
		D3DXVECTOR3 normalizedDir(vecDir[nCnt].x, vecDir[nCnt].y, vecDir[nCnt].z); // D3DXVECTOR3�ɕϊ����Đ��K��
		D3DXVec3Normalize(&normalizedDir, &normalizedDir);

		// ���K�����ꂽ�x�N�g����D3DXVECTOR4�ɖ߂�
		vecDir[nCnt] = D3DXVECTOR4(normalizedDir.x, normalizedDir.y, normalizedDir.z, 0.0f); // �ēxD3DXVECTOR4�Ɋi�[

		// ���C�g�̕�����ݒ�
		m_alight->Direction = D3DXVECTOR3(vecDir[nCnt].x, vecDir[nCnt].y, vecDir[nCnt].z);

		// ���C�g��ݒ�
		pDevice->SetLight(nCnt, m_alight);

		// ���C�g��L���ɂ���
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
