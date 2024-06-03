//=================================================
//
// �A�C�e���̏��� (item.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "item.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "block.h"

//============================
//�R���X�g���N�^
//============================
CItem::CItem(int nPriority) : CPlayer(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CItem::~CItem()
{

}

//============================
//�A�C�e���̏���������
//============================
HRESULT CItem::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//============================
//�A�C�e���̏���������
//============================
void CItem::Uninit()
{
	//������
	CObject2D::Uninit();
}

//============================
//�A�C�e���̍X�V����
//============================
void CItem::Update()
{
	//�e�̈ړ�����
	CObject2D::GetPos() += m_nMove;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
	pVtx[0].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

	pVtx[1].pos.x = CObject2D::GetPos().x + 50 * 0.5f;
	pVtx[1].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

	pVtx[2].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
	pVtx[2].pos.y = CObject2D::GetPos().y + 50 * 0.5f;

	pVtx[3].pos.x = CObject2D::GetPos().x + 50 * 0.5f;
	pVtx[3].pos.y = CObject2D::GetPos().y + 50 * 0.5f;

	//���_�o�b�t�@���A�����b�N����
	CObject2D::GetBuff()->Unlock();

	//�A�C�e���̓����蔻��
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject* pObj = CObject::GetObj(3, nCntObj);

		if (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();

			CPlayer* pPlayer = (CPlayer*)pObj;

			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

			if (type == CObject::TYPE::PLAYER)
			{
				if (CObject2D::GetPos().x >= PlayerPos.x - PLAYER_HITPOINT
					&& CObject2D::GetPos().x <= PlayerPos.x + PLAYER_HITPOINT
					&& CObject2D::GetPos().y >= PlayerPos.y - PLAYER_HITPOINT
					&& CObject2D::GetPos().y <= PlayerPos.y + PLAYER_HITPOINT)
				{
					CObject2D::Uninit();
					return;
				}
			}

		}
	}
}

//============================
//�A�C�e���̕`�揈��
//============================
void CItem::Draw()
{
	CObject2D::Draw();
}

//============================
//�A�C�e���̐�������
//============================
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CItem* pItem;

	pItem = new CItem;

	pItem->SetType(TYPE::ITEM);
	pItem->CObject2D::SetPos(pos);
	pItem->m_rot = rot;


	//�A�C�e���̏�����
	pItem->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\item001.png", &pTexture);

	//�e�N�X�`���̐ݒ�
	pItem->BindTexture(pTexture);

	return pItem;
}