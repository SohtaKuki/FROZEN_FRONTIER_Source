//=================================================
//
// ���̕`�揈�� (floor.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "floor.h"

LPDIRECT3DTEXTURE9 CFloor::m_pTexBuff = nullptr;

//======================
// �R���X�g���N�^
//======================
CFloor::CFloor(int nPriority) : CModel(nPriority)
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

	pVtx[0].pos = D3DXVECTOR3((m_nPos.x - m_nSize.x), m_nPos.y, (m_nPos.z + m_nSize.z));
	pVtx[1].pos = D3DXVECTOR3((m_nPos.x + m_nSize.x), m_nPos.y, (m_nPos.z + m_nSize.z));
	pVtx[2].pos = D3DXVECTOR3((m_nPos.x - m_nSize.x), m_nPos.y, (m_nPos.z -m_nSize.z));
	pVtx[3].pos = D3DXVECTOR3((m_nPos.x + m_nSize.x), m_nPos.y, (m_nPos.z -m_nSize.z));

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

	D3DXVECTOR3 Pos = CObject3D::GetPos();

	Pos = m_nPos;

	int nFadeState = CFade::GetFadeState();

	if (nFadeState == CFade::FADE_OUT)
	{
		CFloor::Uninit();
	}
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

	//�������ɐ��������ꍇ
	if (SUCCEEDED(Floor->Init()))
	{
		Floor->SetType(TYPE::FLOOR);

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

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\icetexture000.png", &m_pTexBuff)))
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

//===========================
// ���̓����蔻��
//===========================
bool CFloor::Collision3DFloor(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
	bool bLanding = false; // �d�͂�K�������ꍇ�̂ݎg�p

	D3DXVECTOR3 Pos = CObject3D::GetPos();

	// �E�������蔻��
	if (pPos->x - fWidth <= Pos.x + m_nSize.x && pPosOld->x - fWidth >= Pos.x + m_nSize.x && pPos->z - fHeight < Pos.z + m_nSize.z && pPos->z > Pos.z - m_nSize.z && pPos->y < Pos.y+ m_nSize.y && pPos->y > Pos.y- m_nSize.y)
	{
		pPos->x = Pos.x + m_nSize.x + fWidth;
	}
	// ���������蔻��
	else if (pPos->x + fWidth >= Pos.x - m_nSize.x && pPosOld->x + fWidth <= Pos.x - m_nSize.x && pPos->z - fHeight < Pos.z + m_nSize.z && pPos->z > Pos.z - m_nSize.z && pPos->y < Pos.y+ m_nSize.y && pPos->y > Pos.y- m_nSize.y)
	{
		pPos->x = Pos.x - m_nSize.x - fWidth;
	}
	// �O�������蔻��
	if (pPos->x - fWidth < Pos.x + m_nSize.x && pPos->x + fWidth > Pos.x - m_nSize.x && pPos->z - fHeight <= Pos.z + m_nSize.z && pPosOld->z - fHeight >= Pos.z + m_nSize.z && pPos->y < Pos.y+ m_nSize.y && pPos->y > Pos.y- m_nSize.y)
	{
		pPos->z = Pos.z + m_nSize.z + fHeight;
	}
	// �㑤�����蔻��
	else if (pPos->x - fWidth < Pos.x + m_nSize.x && pPos->x + fWidth > Pos.x - m_nSize.x && pPos->z >= Pos.z - m_nSize.z && pPosOld->z <= Pos.z - m_nSize.z && pPos->y < Pos.y+ m_nSize.y && pPos->y > Pos.y- m_nSize.y)
	{
		pPos->z = Pos.z - m_nSize.z - fHeight;

	}

	// y���W�㑤�����蔻��
	if (pPos->x - fWidth < Pos.x + m_nSize.x && pPos->x + fWidth > Pos.x - m_nSize.x && pPos->y - fHeight <= Pos.y+ m_nSize.y && pPosOld->y - fHeight >= Pos.y+ m_nSize.y && pPos->z < Pos.z + m_nSize.z && pPos->z > Pos.z - m_nSize.z)
	{
		pPos->y = Pos.y+ m_nSize.y + fHeight;
		bLanding = true;
	}

	return bLanding;
}
