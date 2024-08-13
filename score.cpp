//=================================================
//
// �A�C�e���̏��� (score.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "score.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "block.h"

int CScore::m_nScore = 0;

//============================
//�R���X�g���N�^
//============================
CScore::CScore(int nPriority) : CObject2D(nPriority)
{
	m_nScore = 0;
	m_nScoreCnt = 0;
	bUpdateTime = false;
}

//============================
//�f�X�g���N�^
//============================
CScore::~CScore()
{

}

//============================
//�A�C�e���̏���������
//============================
HRESULT CScore::Init()
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

	for (int nCntTime = 0; nCntTime < NUM_SCORE; nCntTime++)
	{
		//���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(1000.0f + (nCntTime * TEX_SCORE_INTERVAL), 70.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1030.0f + (nCntTime * TEX_SCORE_INTERVAL), 70.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1000.0f + (nCntTime * TEX_SCORE_INTERVAL), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1030.0f + (nCntTime * TEX_SCORE_INTERVAL), 100.0f, 0.0f);

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
void CScore::Uninit()
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
void CScore::Update()
{
	VERTEX_2D* pVtx;

	int aPosTexU[NUM_SCORE];


	// ���Ԃ̒l���R�s�[
	int CopyTime = m_nScore;

	// �e���̒l���v�Z
	for (int nCntTime = NUM_SCORE - 1; nCntTime >= 0; nCntTime--)
	{
		aPosTexU[nCntTime] = CopyTime % 10;
		CopyTime /= 10;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̍X�V
	for (int nCntTime = 0; nCntTime < NUM_SCORE; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 1.0f);



		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	int nFadeState = CFade::GetFadeState();

	if (nFadeState == CFade::FADE_OUT)
	{
		Uninit();
		m_nScore = 0;
	}

}

//============================
//�A�C�e���̕`�揈��
//============================
void CScore::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTexBuff);

	for (int nCntTime = 0; nCntTime < NUM_SCORE; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//============================
//�A�C�e���̐�������
//============================
CScore* CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CScore* pScore;

	pScore = new CScore;

	pScore->SetType(TYPE::SCORE);
	pScore->m_nPos = pos;
	pScore->m_rot = rot;

	//�A�C�e���̏�����
	pScore->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\SCORE_NUMBER.png", &pTexture);

	pScore->BindTexture(pTexture);

	return pScore;
}

void CScore::AddScore(int nTime)
{
	m_nScore += nTime;
}

//=======================
//�e�N�X�`���̐ݒ�
//=======================
void CScore::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexBuff = pTex;
}

