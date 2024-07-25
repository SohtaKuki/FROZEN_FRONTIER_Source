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

int CTimer::m_nTime = 0;

//============================
//�R���X�g���N�^
//============================
CTimer::CTimer(int nPriority) : CObject2D(nPriority)
{
	m_nTime = 0;
	m_nTimerCnt = 0;
	bUpdateTime = false;
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
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_OBJECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}


	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================
//�A�C�e���̏���������
//============================
void CTimer::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexBuff != nullptr)
	{
		m_pTexBuff->Release();
		m_pTexBuff = nullptr;
	}

	CObject::Release();
}

//============================
//�A�C�e���̍X�V����
//============================
void CTimer::Update()
{

	VERTEX_2D* pVtx;

	int aPosTexU[NUM_TIME];

	if (bUpdateTime == false)
	{
	m_nTimerCnt++;

		if (m_nTimerCnt == MAX_TIMESPEED)
		{
			m_nTime--; //���Ԃ�1�b���炷
			m_nTimerCnt = 0; //�t���[���J�E���g���Z�b�g
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_F1))
	{

		if (bUpdateTime == false)
		{
			bUpdateTime = true;
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_F2))
	{
		if (bUpdateTime == true)
		{
			bUpdateTime = false;
		}
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
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 1.0f);
						  

		if (m_nTime < 20)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	int nFadeState = CFade::GetFadeState();

	if (nFadeState == CFade::FADE_OUT)
	{
		Uninit();
		m_nTime = 0;
	}

	if (m_nTime < 0)
	{
		Uninit();
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
		m_nTime = 0;
	}


	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		Uninit();
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
		m_nTime = 0;
	}

}

//============================
//�A�C�e���̕`�揈��
//============================
void CTimer::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTexBuff);

	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//============================
//�A�C�e���̐�������
//============================
CTimer* CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTimer* pTimer;

	pTimer = new CTimer;

	pTimer->SetType(TYPE::TIMER);
	pTimer->m_nPos = pos;
	pTimer->m_rot = rot;

	//�A�C�e���̏�����
	pTimer->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\SCORE_NUMBER.png", &pTexture);

	pTimer->BindTexture(pTexture);

	return pTimer;
}

void CTimer::AddTimer(int nTime)
{
	m_nTime += nTime;
}

//=======================
//�e�N�X�`���̐ݒ�
//=======================
void CTimer::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexBuff = pTex;
}

