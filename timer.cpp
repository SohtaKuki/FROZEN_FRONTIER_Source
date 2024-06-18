//=================================================
//
// �A�C�e���̏��� (timer.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "timer.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "block.h"

//============================
//�R���X�g���N�^
//============================
CTimer::CTimer(int nPriority) : CObject2D(nPriority)
{
	m_nTime = 10;
	m_nTimerCnt = 0;
}

//============================
//�f�X�g���N�^
//============================
CTimer::~CTimer()
{

}

//============================
//�A�C�e���̏���������
//============================
HRESULT CTimer::Init()
{
	//for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	//{
		//������
		CObject2D::Init();
	//}

	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(620.0f + (nCntTime * TEX_TIME_INTERVAL), 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(670.0f + (nCntTime * TEX_TIME_INTERVAL), 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(620.0f + (nCntTime * TEX_TIME_INTERVAL), 90.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(670.0f + (nCntTime * TEX_TIME_INTERVAL), 90.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	CObject2D::GetBuff()->Unlock();

	return S_OK;
}

//============================
//�A�C�e���̏���������
//============================
void CTimer::Uninit()
{
	//������
	CObject2D::Uninit();
}

//============================
//�A�C�e���̍X�V����
//============================
void CTimer::Update()
{

	VERTEX_2D* pVtx;

	int aPosTexU[NUM_TIME];

	m_nTimerCnt++;

	if (m_nTimerCnt == MAX_TIMESPEED)
	{
		m_nTime--; //���Ԃ�1�b���炷
		m_nTimerCnt = 0; //�t���[���J�E���g���Z�b�g
	}

	// ���Ԃ̒l���R�s�[
	int CopyTime = m_nTime;

	// �e���̒l���v�Z
	for (int nCntTime = NUM_TIME - 1; nCntTime >= 0; nCntTime--)
	{
		aPosTexU[nCntTime] = CopyTime % 10;
		CopyTime /= 10;
	}



	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 1.0f);

		if (m_nTime > 80)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 252, 219, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 252, 219, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 252, 219, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 252, 219, 255);
		}

		else if (m_nTime > 20 < 80)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (m_nTime < 20)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	CObject2D::GetBuff()->Unlock();

	if (m_nTime < 0)
	{
		m_nTime = 0;
		Uninit();
		CManager::SetMode(CScene::MODE_TITLE);
	}

}

//============================
//�A�C�e���̕`�揈��
//============================
void CTimer::Draw()

{	//�e�N�X�`�����W�̍X�V
	CObject2D::Draw();
}

//============================
//�A�C�e���̐�������
//============================
CTimer* CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTimer* pTimer;

	pTimer = new CTimer;

	pTimer->SetType(TYPE::TIMER);
	pTimer->CObject2D::SetPos(pos);
	pTimer->m_rot = rot;

	//�A�C�e���̏�����
	pTimer->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\SCORE_NUMBER.png", &pTexture);

	//�e�N�X�`���̐ݒ�
	pTimer->BindTexture(pTexture);

	return pTimer;
}