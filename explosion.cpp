//=================================================
//
// �����̏��� (explosion.cpp)
// Author: Sohta Kuki
//
//=================================================


#include "explosion.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CExplosion::CExplosion()
{
	m_nMove = { 0, 0, 0 };
	m_nPatternAnimExpl = 0;
	m_nCounterAnimExpl = 0;
}

//============================
//�f�X�g���N�^
//============================
CExplosion::~CExplosion()
{

}

//============================
//�����A�j���[�V�����̏���������
//============================
HRESULT CExplosion::Init()
{
	//2D�I�u�W�F�N�g�̏�����
	CObject2D::Init();

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = CObject2D::GetPos().x - EXPL_TEX_SIZE * 0.5f;
	pVtx[0].pos.y = CObject2D::GetPos().y - EXPL_TEX_SIZE * 0.5f;

	pVtx[1].pos.x = CObject2D::GetPos().x + EXPL_TEX_SIZE * 0.5f;
	pVtx[1].pos.y = CObject2D::GetPos().y - EXPL_TEX_SIZE * 0.5f;

	pVtx[2].pos.x = CObject2D::GetPos().x - EXPL_TEX_SIZE * 0.5f;
	pVtx[2].pos.y = CObject2D::GetPos().y + EXPL_TEX_SIZE * 0.5f;

	pVtx[3].pos.x = CObject2D::GetPos().x + EXPL_TEX_SIZE * 0.5f;
	pVtx[3].pos.y = CObject2D::GetPos().y + EXPL_TEX_SIZE * 0.5f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / EXPLOSION_PATTERN_ANIM, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / EXPLOSION_PATTERN_ANIM, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	CObject2D::GetBuff()->Unlock();

	return S_OK;
}

//============================
//�����A�j���[�V�����̏I������
//============================
void CExplosion::Uninit()
{
	//2D�I�u�W�F�N�g�̏I��
	CObject2D::Uninit();
}

//============================
//�����A�j���[�V�����̍X�V����
//============================
void CExplosion::Update()
{

	m_nPatternAnimExpl++;

	if (m_nPatternAnimExpl > UPDATE_TEX)
	{
		m_nCounterAnimExpl++;

		if (m_nCounterAnimExpl > EXPLOSION_PATTERN_ANIM)
		{
			CObject2D::Uninit();
			return;
		}

		m_nPatternAnimExpl = 0;
	}

	VERTEX_2D* pVtx;

	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((1.0f / EXPLOSION_PATTERN_ANIM) * m_nCounterAnimExpl - (1.0f / EXPLOSION_PATTERN_ANIM), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / EXPLOSION_PATTERN_ANIM) * m_nCounterAnimExpl, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / EXPLOSION_PATTERN_ANIM) * m_nCounterAnimExpl - (1.0f / EXPLOSION_PATTERN_ANIM), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / EXPLOSION_PATTERN_ANIM) * m_nCounterAnimExpl, 1.0f);


	CObject2D::GetBuff()->Unlock();
}

//============================
//�����A�j���[�V�����̕`�揈��
//============================
void CExplosion::Draw()
{
	//2D�I�u�W�F�N�g�̕`��
	CObject2D::Draw();
}

//============================
//�����A�j���[�V�����̐�������
//============================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* pExplosion;

	pExplosion = new CExplosion;

	pExplosion->CObject2D::GetPos() = pos;

	//�����̏�����
	pExplosion->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),"data\\TEXTURE\\explosion000.png",&pTexture);

	pExplosion->BindTexture(pTexture);

	return pExplosion;
}