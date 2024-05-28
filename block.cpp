//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "block.h"
#include "bullet.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CBlock::m_pTexTemp = nullptr;

//======================
// �R���X�g���N�^
//======================
CBlock::CBlock(int nPriority) : CObject2D(nPriority)
{
	m_nLife = 4;
	m_PolygonMoveSpeed = 1.0f;

}
//======================
// �f�X�g���N�^
//======================
CBlock::~CBlock()
{

}

//======================
// ����������
//======================
HRESULT CBlock::Init()
{
	//������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
// �I������
//======================
void CBlock::Uninit()
{
	Unload();
	CObject2D::Uninit();
}

//======================
// �X�V����
//======================
void CBlock::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_nBlockPos.x - m_nBlockSize.x, m_nBlockPos.y - m_nBlockSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nBlockPos.x + m_nBlockSize.x, m_nBlockPos.y - m_nBlockSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nBlockPos.x - m_nBlockSize.x, m_nBlockPos.y + m_nBlockSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nBlockPos.x + m_nBlockSize.x, m_nBlockPos.y + m_nBlockSize.y, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_nBlockPos.x += m_moveBlock.x;
	m_nBlockPos.y += m_moveBlock.y;

	//�ړ��ʂ��X�V
	m_moveBlock.x += (Length_value2 - m_moveBlock.x) * Attenuation_value;
	m_moveBlock.y += (Length_value2 - m_moveBlock.y) * Attenuation_value;

}

//======================
// �`�揈��
//======================
void CBlock::Draw()
{
	CObject2D::Draw();
}

//======================
// �I�u�W�F�N�g��������
//======================
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBlock* enemy = nullptr;

	enemy = new CBlock;

	if (SUCCEEDED(enemy->Init()))
	{
		enemy->SetType(TYPE::BLOCK);

		enemy->Load();

		enemy->m_nBlockPos = pos;

		enemy->m_nBlockSize = size;

		//�e�N�X�`���̐ݒ�
		enemy->BindTexture(m_pTexTemp);
	}

	return enemy;
}

//======================
// �_���[�W����
//======================
void CBlock::Damage()
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject* pObj = CObject::GetObj(3, nCntObj);

		if (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::ENEMY)
			{
				m_nLife -= 1;

				VERTEX_2D* pVtx;

				CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				pVtx += 4;

				CObject2D::GetBuff()->Unlock();
			}

			if (m_nLife == 0)
			{
				CObject2D::Uninit();
				CObject::Release();
			}
		}
	}
}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT CBlock::Load()
{
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block003.png", &m_pTexTemp)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
// �e�N�X�`���A�����[�h(�I��)����
//======================
void CBlock::Unload()
{
	if (m_pTexTemp != nullptr)
	{
		m_pTexTemp->Release();
		m_pTexTemp = nullptr;
	}
}

void CBlock::SetPos(D3DXVECTOR3 pos)
{
	CBlock* enemy = nullptr;
}
