//=================================================
//
// 3D�|���S���̕`�揈�� (object3D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "floor.h"

LPDIRECT3DTEXTURE9 CFloor::m_pTexBuff = nullptr;

//======================
// �R���X�g���N�^
//======================
CFloor::CFloor(int nPriority) : CObject3D(nPriority)
{

}

//======================
// �f�X�g���N�^
//======================
CFloor::~CFloor()
{

}

//======================
// ����������
//======================
HRESULT CFloor::Init()
{
	//������
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
// �I������
//======================
void CFloor::Uninit()
{
	CObject3D::Uninit();
}

//======================
// �X�V����
//======================
void CFloor::Update()
{
	VERTEX_3D* pVtx;

	CObject3D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-FIELD_SIZE, 0.0f, FIELD_SIZE);
	pVtx[1].pos = D3DXVECTOR3(FIELD_SIZE, 0.0f, FIELD_SIZE);
	pVtx[2].pos = D3DXVECTOR3(-FIELD_SIZE, 0.0f, -FIELD_SIZE);
	pVtx[3].pos = D3DXVECTOR3(FIELD_SIZE, 0.0f, -FIELD_SIZE);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	CObject3D::GetBuff()->Unlock();
}

//======================
// �`�揈��
//======================
void CFloor::Draw()
{
	CObject3D::Draw();
}

//======================
// �I�u�W�F�N�g��������
//======================
CFloor* CFloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CFloor* Floor = nullptr;

	Floor = new CFloor;

	if (SUCCEEDED(Floor->Init()))
	{
		Floor->Load();

		Floor->m_nPos = pos;

		Floor->m_nSize = size;

		Floor->Init();

		//�e�N�X�`���̐ݒ�
		Floor->BindTexture(m_pTexBuff);
	}

	return Floor;
}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT CFloor::Load()
{
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\samplepos.png", &m_pTexBuff)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
// �e�N�X�`���A�����[�h(�I��)����
//======================
void CFloor::Unload()
{
	if (m_pTexBuff != nullptr)
	{
		m_pTexBuff->Release();
		m_pTexBuff = nullptr;
	}
}