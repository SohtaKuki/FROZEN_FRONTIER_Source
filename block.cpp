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

	D3DXVECTOR3 BlockPos = CObject2D::GetPos();

	pVtx[0].pos = D3DXVECTOR3(BlockPos.x - m_nBlockSize.x, BlockPos.y - m_nBlockSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BlockPos.x + m_nBlockSize.x, BlockPos.y - m_nBlockSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BlockPos.x - m_nBlockSize.x, BlockPos.y + m_nBlockSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BlockPos.x + m_nBlockSize.x, BlockPos.y + m_nBlockSize.y, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	BlockPos.x += m_moveBlock.x;
	BlockPos.y += m_moveBlock.y;

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
	CBlock* block = nullptr;

	block = new CBlock;

	if (SUCCEEDED(block->Init()))
	{
		block->SetType(TYPE::BLOCK);

		block->Load();

		block->CObject2D::SetPos(pos);

		block->m_nBlockSize = size;

		//�e�N�X�`���̐ݒ�
		block->BindTexture(m_pTexTemp);
	}

	return block;
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
	CBlock* block = nullptr;
}

//===============================
// �u���b�N�̏Փ˔���
//===============================
bool CBlock::CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
	//int g_JumpCnt;

	//g_JumpCnt = GetJumpCnt();

	//g_LavaPosY = GetLavaPos();

	//g_LavaPosX = GetLavaPosX();

	//g_nJmpCnt = GetJumpCnt();

	//if ((pPosOld->y < g_LavaPosY * BLOCK_COLIDTC_Y && pPos->y > g_LavaPosY * BLOCK_COLIDTC_Y) && g_LavaPosX * BLOCK_COLIDTC_X - (BLOCK_SIZE / 2) < pPos->x && pPos->x < (g_LavaPosX + 1) * BLOCK_COLIDTC_X + (BLOCK_SIZE / 2))
	//{
	//	MoveResult = true;
	//}

	float fBlockWidth = 0.0f;  //�u���b�N�̉���
	float fBlockHeight = 0.0f; //�u���b�N�̍���

	bool bLanding = false;	// ���n���Ă��邩�ǂ���

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			CObject* pObj = CObject::GetObj(nCntPriority, nCntBlock);

			if (pObj != nullptr)
			{
				CObject::TYPE type = pObj->GetType();

				if (type == CObject::TYPE::BLOCK)
				{
					CBlock* pBlock = (CBlock*)pObj;

					D3DXVECTOR3 BlockPos = pBlock->GetPos();      //���݂̈ʒu���擾

					//�u���b�N�㑤����
					if (pPos->x - fWidth <= BlockPos.x + fBlockWidth &&pPosOld->x - fWidth >= BlockPos.x + fBlockWidth &&pPos->y - fHeight < BlockPos.y + fBlockHeight &&pPos->y  > BlockPos.y - fBlockHeight)
					{//�E���Ƃ̓����蔻��
						pPos->x = BlockPos.x + fBlockWidth + fWidth;
					}
					else if (pPos->x + fWidth >= BlockPos.x - fBlockWidth &&pPosOld->x + fWidth <= BlockPos.x - fBlockWidth &&pPos->y - fHeight < BlockPos.y + fBlockHeight &&	pPos->y > BlockPos.y - fBlockHeight)
					{//�����Ƃ̓����蔻��
						pPos->x = BlockPos.x - fBlockWidth - fWidth;
					}
					//else if (pPos->x - fWidth < BlockPos.x + fBlockWidth &&pPos->x + fWidth > BlockPos.x - fBlockWidth &&	pPos->y - fHeight <= BlockPos.y + fBlockHeight &&pPosOld->y - fHeight >= BlockPos.y + fBlockHeight)
					//{//�����Ƃ̓����蔻��
					//	pPos->y = BlockPos.y + fBlockHeight + fHeight;

					//}
					else if (pPos->x - fWidth < BlockPos.x + fBlockWidth &&pPos->x + fWidth > BlockPos.x - fBlockWidth &&pPos->y >= BlockPos.y - fBlockHeight &&pPosOld->y <= BlockPos.y - fBlockHeight)
					{//�㑤�Ƃ̒��n����
						pPos->y = BlockPos.y - fBlockHeight;
						//bLanding = true;
					}
				}
				//}
			}
		}
	}
	return bLanding;
}