//===================================
//
// �|�[�Y���� [pause.cpp]
// Author: Sohta Kuki
//
//===================================

#include "pause.h"
#include "input.h"
#include "scene.h"
#include "startcallui.h"
#include "endcallui.h"

int CPauseSelect::m_nPauseSelect = 0;
bool CPauseSelect::m_bUse = false;

//==========================
//�R���X�g���N�^
//==========================
CPauseSelect::CPauseSelect(int nPriority) : CObject2D(nPriority)
{
	m_nPauseSelect = 0;
	m_bUse = false;
}

//==========================
//�f�X�g���N�^
//==========================
CPauseSelect::~CPauseSelect()
{

}

//=============================
//�|�[�Y��ʂ̏���������
//=============================

HRESULT CPauseSelect::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause000.png", &m_pTexturePauseSelect[PAUSE_SELECT_1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause001.png", &m_pTexturePauseSelect[PAUSE_SELECT_2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause002.png", &m_pTexturePauseSelect[PAUSE_SELECT_3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPauseSelect,
		NULL);
	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffPauseSelect->Unlock();

	return S_OK;
}

//=============================
//�|�[�Y��ʂ̏I������
//=============================

void CPauseSelect::Uninit(void)
{
	for (int nCnt = 0; nCnt < PAUSE_SELECT_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexturePauseSelect[nCnt] != NULL)
		{
			m_pTexturePauseSelect[nCnt]->Release();
			m_pTexturePauseSelect[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffPauseSelect != NULL)
	{
		m_pVtxBuffPauseSelect->Release();
		m_pVtxBuffPauseSelect = NULL;
	}
}

//=============================
//�|�[�Y��ʂ̍X�V����
//=============================
void CPauseSelect::Update(void)
{
	if (CStartCallUI::GetStartStat() == true && CEndCallUI::GetEndStat() == true)
	{
		int nFadeState = CFade::GetFadeState();

		if (nFadeState == CFade::FADE_OUT)
		{
			CPauseSelect::Uninit();
			return;
		}

		VERTEX_2D* pVtx;	//���_���̃|�C���^

		//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
		m_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

		//�|�[�Y��ʂ�\��������ꍇ
		if (CManager::GetKeyboard()->GetTrigger(DIK_P) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_START))
		{
			m_bUse = m_bUse ? false : true;
		}

		if (m_bUse == false)
		{
			CScene::UpdateSwitch(1);
		}

		if (m_bUse == true)
		{
			CScene::UpdateSwitch(0);
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_W) && m_bUse == true)
		{
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			if (m_nPauseSelect > 0)
			{
				m_nPauseSelect--;
			}

			else if (m_nPauseSelect <= 0)
			{
				m_nPauseSelect = PAUSE_SELECT_3;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_UP) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_UP) && m_bUse == true)
		{
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			if (m_nPauseSelect > 0)
			{
				m_nPauseSelect--;
			}
			else if (m_nPauseSelect <= 0)
			{
				m_nPauseSelect = PAUSE_SELECT_3;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_S) && m_bUse == true)
		{
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			if (m_nPauseSelect < 2)
			{
				m_nPauseSelect++;
			}
			else if (m_nPauseSelect >= 2)
			{
				m_nPauseSelect = PAUSE_SELECT_1;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_DOWN) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_DOWN) && m_bUse == true)
		{
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

			if (m_nPauseSelect < 2)
			{
				m_nPauseSelect++;
			}
			else if (m_nPauseSelect >= 2)
			{
				m_nPauseSelect = PAUSE_SELECT_1;
			}
		}
		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuffPauseSelect->Unlock();
	}

}
//=============================
//�|�[�Y��ʂ̕`�揈��
//=============================

void CPauseSelect::Draw(void)
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffPauseSelect, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (m_bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexturePauseSelect[m_nPauseSelect]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4);
	}
}

//=============================
//�|�[�Y��ʂ̎擾����
//=============================
int CPauseSelect::GetPauseSelect(void)
{
	return m_nPauseSelect;
}

//============================
//�^�C�g���̐�������
//============================
CPauseSelect* CPauseSelect::Create()
{
	CPauseSelect* pPauseSelect;

	pPauseSelect = new CPauseSelect;

	if (FAILED(pPauseSelect->Init()))
	{
		delete pPauseSelect;
		return nullptr;
	}

	return pPauseSelect;
}

bool CPauseSelect::bUseSwitch(int nType)
{
	if (nType == 0)
	{
		m_bUse = false;
	}

	if (nType == 1)
	{
		m_bUse = true;
	}

	return nType;
}