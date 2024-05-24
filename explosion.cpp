//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "explosion.h"
#include "bullet.h"

//======================
// �R���X�g���N�^
//======================
CExplosion::CExplosion()
{
	m_PolygonMoveSpeed = 1.0f;
	m_PolygonPosX = 500.0f;
	m_PolygonPosY = 200.0f;
	m_FrameDuration = 0.5f;
	m_Frametimer = 0.5f;
	m_CurrentFrame = 0;           // ���݂̃t���[��
	m_Numframes = 8;        // �A�j���[�V�����̑��t���[����
}
//======================
// �f�X�g���N�^
//======================
CExplosion::~CExplosion()
{

}

//======================
// ����������
//======================
HRESULT CExplosion::Init()
{
	//������
	CObject2D::Init();

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos.x = m_PolygonPosX + sinf(m_rotExplosion.z - D3DX_PI * 0.75) * m_fLengthExplosion;
	pVtx[0].pos.y = m_PolygonPosY + cosf(m_rotExplosion.z - D3DX_PI * 0.75f) * m_fLengthExplosion;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_PolygonPosX + sinf(m_rotExplosion.z + D3DX_PI * 0.75f) * m_fLengthExplosion;
	pVtx[1].pos.y = m_PolygonPosY + cosf(m_rotExplosion.z + D3DX_PI * 0.75f) * m_fLengthExplosion;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_PolygonPosX + sinf(m_rotExplosion.z - D3DX_PI * 0.75f) * m_fLengthExplosion;
	pVtx[2].pos.y = m_PolygonPosY + cosf(m_rotExplosion.z - D3DX_PI * 0.75f) * m_fLengthExplosion;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_PolygonPosX + sinf(m_rotExplosion.z + D3DX_PI * 0.25f) * m_fLengthExplosion;
	pVtx[3].pos.y = m_PolygonPosY + cosf(m_rotExplosion.z + D3DX_PI * 0.25f) * m_fLengthExplosion;
	pVtx[3].pos.z = 0.0f;

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
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//======================
// �X�V����
//======================
void CExplosion::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_nExplosionPos.x - m_nExplosionSize.x, m_nExplosionPos.y - m_nExplosionSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nExplosionPos.x + m_nExplosionSize.x, m_nExplosionPos.y - m_nExplosionSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nExplosionPos.x - m_nExplosionSize.x, m_nExplosionPos.y + m_nExplosionSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nExplosionPos.x + m_nExplosionSize.x, m_nExplosionPos.y + m_nExplosionSize.y, 0.0f);

	// �A�j���[�V�����t���[���̍X�V
	m_Frametimer += m_FrameDuration;

	if (m_Frametimer >= m_FrameDuration)
	{
		// ���̃t���[���ɐi�߂�
		m_CurrentFrame = (m_CurrentFrame + 1) % m_Numframes;

		// �t���[���̌o�ߎ��Ԃ����Z�b�g
		m_Frametimer = 0.0f;

		// �e�N�X�`�����W�̍X�V
		VERTEX_2D* pVtx;
		CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 1.0f);

		CObject2D::GetBuff()->Unlock();
	}

	m_nExplosionPos.x += m_moveExplosion.x;
	m_nExplosionPos.y += m_moveExplosion.y;


	//�ړ��ʂ��X�V
	m_moveExplosion.x += (Length_value2 - m_moveExplosion.x) * Attenuation_value;
	m_moveExplosion.y += (Length_value2 - m_moveExplosion.y) * Attenuation_value;



}

//======================
// �`�揈��
//======================
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//======================
// �I�u�W�F�N�g��������
//======================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* explosion = new CExplosion;

	explosion->m_nExplosionPos = pos;

	explosion->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\explosion000.png", &pTexture);

	explosion->BindTexture(pTexture);

	return explosion;
}
