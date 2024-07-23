//=================================================
//
// �t�F�[�h���� (fade.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "fade.h"
#include "manager.h"
#include "object.h"

CScene::MODE CFade::m_Mode = CScene::MODE_TITLE;			
CFade::FADE CFade::m_FadeState = CFade::FADE_NONE;
bool CFade::m_bEndFade = false;

//============================
//�R���X�g���N�^
//============================
CFade::CFade()
{
    m_pVtxBuff = nullptr;			
    m_Mode = CScene::MODE_TITLE;	
    m_bEndFade = true;				
    m_FadeState = CFade::FADE_NONE;	

}

//============================
//�f�X�g���N�^
//============================
CFade::~CFade()
{

}

//============================
//����������
//============================
HRESULT CFade::Init()
{
    m_nAlpha = 0;

    LPDIRECT3DDEVICE9 pDevice;

    pDevice = CManager::GetRenderer()->GetDevice();

    pDevice->CreateVertexBuffer(sizeof(CObject::VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

    CObject::VERTEX_2D* pVtx;

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


    pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
    pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
    pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
    pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

    m_pVtxBuff->Unlock();

    //�������
    SetFade(CScene::MODE::MODE_TITLE);

    return S_OK;
}

//============================
//�I������
//============================
void CFade::Uninit()
{
    if (m_pVtxBuff != nullptr)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = nullptr;
    }

}

//============================
//�X�V����
//============================
void CFade::Update()
{


    if (!m_bEndFade)
    {
        switch (m_FadeState)
        {
        case FADE_NONE:
            break;

        case FADE_OUT:

            if (m_nAlpha < 255)
            {
                m_nAlpha += 15;

                SetAlpha(m_nAlpha);

                if (m_nAlpha >= 255)
                {
                    m_nAlpha = 255;

                    CManager::SetMode(m_Mode);

                    m_FadeState = FADE_IN;
                }
            }

            break;

        case FADE_IN:

            if (m_nAlpha > 0)
            {
                m_nAlpha -= 15;

                SetAlpha(m_nAlpha);

                if (m_nAlpha <= 0)
                {
                    m_nAlpha = 0;

                    m_FadeState = FADE_NONE;
                    m_bEndFade = true;
                }
            }
            break;
        }
    }
}

//============================
//�A���t�@�l�̐ݒ�
//============================
void CFade::SetAlpha(int nAlpha)
{
    CObject::VERTEX_2D* pVtx; 

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //�A���t�@�l��ϓ�������
    for (int nCount = 0; nCount < 4; nCount++)
    {
        pVtx[nCount].col = D3DCOLOR_RGBA(0, 0, 0, nAlpha);
    }

    m_pVtxBuff->Unlock();
}

//============================
//�`�揈��
//============================
void CFade::Draw()
{
    LPDIRECT3DDEVICE9 pDevice;

    pDevice = CManager::GetRenderer()->GetDevice();

    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject::VERTEX_2D));

    pDevice->SetFVF(FVF_VERTEX_2D);

    pDevice->SetTexture(0, NULL);

    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//============================
// �t�F�[�h�̐ݒ菈��
//============================
void CFade::SetFade(CScene::MODE mode)
{
    m_bEndFade = false;
    m_FadeState = FADE_OUT;

    m_Mode = mode;
}
