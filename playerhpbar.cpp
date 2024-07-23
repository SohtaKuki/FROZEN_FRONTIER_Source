//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "playerhpbar.h"
#include "manager.h"
#include "3dplayer.h"

//======================
// �R���X�g���N�^
//======================
CPlayerHpBar::CPlayerHpBar(int nPriority) : CObject2D(nPriority)
{

}

//======================
// �f�X�g���N�^
//======================
CPlayerHpBar::~CPlayerHpBar()
{

}

//======================
// ����������
//======================
HRESULT CPlayerHpBar::Init()
{
	CObject2D::Init();

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nSize.x, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, m_nSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nSize.x, m_nSize.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	CObject2D::GetBuff()->Unlock();

	return S_OK;
}

//======================
// �I������
//======================
void CPlayerHpBar::Uninit()
{
	CObject2D::Uninit();
}

//======================
// �X�V����
//======================
void CPlayerHpBar::Update()
{

	VERTEX_2D* pVtx;


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
	pVtx[0].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

	pVtx[1].pos.x = (m_nSize.x + CObject2D::GetPos().x) + 50 * 0.5f * (C3dplayer::GetPlayerLife() * 0.5);
	pVtx[1].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

	pVtx[2].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
	pVtx[2].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;

	pVtx[3].pos.x = (m_nSize.x + CObject2D::GetPos().x) + 50 * 0.5f * (C3dplayer::GetPlayerLife() * 0.5);
	pVtx[3].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;



	//���_�o�b�t�@���A�����b�N����
	CObject2D::GetBuff()->Unlock();

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CPlayerHpBar::Uninit();
	}
}

//======================
// �`�揈��
//======================
void CPlayerHpBar::Draw()
{
	CObject2D::Draw();
}

//======================
// �I�u�W�F�N�g��������
//======================
CPlayerHpBar* CPlayerHpBar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayerHpBar* PlayerHpBar = new CPlayerHpBar;

	PlayerHpBar->CObject2D::SetPos(pos);

	PlayerHpBar->m_nSize = size;

	PlayerHpBar->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\hpbar.png", &pTexture);

	PlayerHpBar->BindTexture(pTexture);

	return PlayerHpBar;
}