//=================================================
//
// �e�̏��� (bullet.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "bullet.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "explosion.h"

//============================
//�R���X�g���N�^
//============================
CBullet::CBullet()
{
	m_Life = 0;
}

//============================
//�f�X�g���N�^
//============================
CBullet::~CBullet()
{

}

//============================
//�e�̏���������
//============================
HRESULT CBullet::Init()
{
	//������
	CObject2D::Init();

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos.x = CPlayer::GetPlayerPos().x - 35 * 0.5f;
	pVtx[0].pos.y = CPlayer::GetPlayerPos().y - 35 * 0.5f;
											 
	pVtx[1].pos.x = CPlayer::GetPlayerPos().x + 35 * 0.5f;
	pVtx[1].pos.y = CPlayer::GetPlayerPos().y - 35 * 0.5f;
											 
	pVtx[2].pos.x = CPlayer::GetPlayerPos().x - 35 * 0.5f;
	pVtx[2].pos.y = CPlayer::GetPlayerPos().y + 35 * 0.5f;
											 
	pVtx[3].pos.x = CPlayer::GetPlayerPos().x + 35 * 0.5f;
	pVtx[3].pos.y = CPlayer::GetPlayerPos().y + 35 * 0.5f;

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//x.y
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	CObject2D::GetBuff()->Unlock();

	return S_OK;
}

//============================
//�e�̏���������
//============================
void CBullet::Uninit()
{
	//������
	CObject2D::Uninit();
}

//============================
//�e�̍X�V����
//============================
void CBullet::Update()
{
	CPlayer::GetPlayerPos() += m_nMove;

	m_Life--;

	if (m_Life <= 0)
	{
		CExplosion::Create(CPlayer::GetPlayerPos());
		CObject2D::Uninit();
		CObject::Release();
		return;
	}

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos.x = CPlayer::GetPlayerPos().x - 35 * 0.5f;
	pVtx[0].pos.y = CPlayer::GetPlayerPos().y - 35 * 0.5f;

	pVtx[1].pos.x = CPlayer::GetPlayerPos().x + 35 * 0.5f;
 	pVtx[1].pos.y = CPlayer::GetPlayerPos().y - 35 * 0.5f;

	pVtx[2].pos.x = CPlayer::GetPlayerPos().x - 35 * 0.5f;
	pVtx[2].pos.y = CPlayer::GetPlayerPos().y + 35 * 0.5f;

	pVtx[3].pos.x = CPlayer::GetPlayerPos().x + 35 * 0.5f;
	pVtx[3].pos.y = CPlayer::GetPlayerPos().y + 35 * 0.5f;

	//���_�o�b�t�@���A�����b�N����
	CObject2D::GetBuff()->Unlock();
}

//============================
//�e�̕`�揈��
//============================
void CBullet::Draw()
{
	CObject2D::Draw();
}

//============================
//�e�̐�������
//============================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBullet* pBullet;

	pBullet = new CBullet;

	pBullet->CPlayer::GetPlayerPos() = pos;
	pBullet->m_rot = rot;
	pBullet->m_Life = BULLET_LIFE;

	//�ړ��ʂ�ݒ�

	pBullet->m_nMove.x = sinf(D3DX_PI * (pBullet->m_rot.z / D3DX_PI) - D3DX_PI * 0.5f) * 5.0f;
	pBullet->m_nMove.y = cosf(D3DX_PI * (pBullet->m_rot.z / D3DX_PI) - D3DX_PI * 0.5f) * 5.0f;

	pBullet->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),"data\\TEXTURE\\bullet_yellow.png",&pTexture);

	//�e�N�X�`���̐ݒ�
	pBullet->BindTexture(pTexture);

	return pBullet;
}