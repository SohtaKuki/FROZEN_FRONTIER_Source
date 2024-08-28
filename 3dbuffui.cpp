//=================================================
//
// �^�C�g����ʔw�i�̏��� (titlebg.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dbuffui.h"

bool CBuffUI::m_bUse[NUM_ICON] = {};

//============================
//�R���X�g���N�^
//============================
CBuffUI::CBuffUI(int nPriority) : CObject2D(nPriority)
{
    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        m_bUse[nCntBG] = false;
    }

    m_nAlphaCnt = 255;
    m_bAlphaSwitch = false;
}

//============================
//�f�X�g���N�^
//============================
CBuffUI::~CBuffUI()
{

}

//=====================
// �w�i����������
//======================
HRESULT CBuffUI::Init()
{

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    int nCntBG;

    //�e�N�X�`�����W�̊J�n�ʒu�iV�l�j�̏�����
    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        m_aPosTexV[nCntBG] = 0.0f;
    }

    if (FAILED(pDevice->CreateVertexBuffer(
        sizeof(VERTEX_2D) * 4 * NUM_ICON,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_MANAGED,
        &m_pVtxBuff,
        nullptr)))
    {
        return E_FAIL;
    }

    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@���b�N
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        switch (nCntBG)
        {
        case 0:
            //���_���W�̐ݒ�
            pVtx[0].pos = D3DXVECTOR3(m_nPos[nCntBG].x - m_nSize[nCntBG].x, m_nPos[nCntBG].y, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_nPos[nCntBG].x + m_nSize[nCntBG].x, m_nPos[nCntBG].y, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_nPos[nCntBG].x - m_nSize[nCntBG].x, m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_nPos[nCntBG].x + m_nSize[nCntBG].x, m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);

            //rhw�̐ݒ�
            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            //���_�J���[
            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            //�e�N�X�`�����W�̐ݒ�
            pVtx[0].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG]);
            pVtx[1].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG]);
            pVtx[2].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG] + 1.0f);
            pVtx[3].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG] + 1.0f);

            pVtx += 4;
            break;
        case 1:
            //���_���W�̐ݒ�
            pVtx[0].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x) + 100.0f, m_nPos[nCntBG].y, 0.0f);
            pVtx[1].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x) + 100.0f, m_nPos[nCntBG].y, 0.0f);
            pVtx[2].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x) + 100.0f, m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);
            pVtx[3].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x) + 100.0f, m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);

            //rhw�̐ݒ�
            pVtx[0].rhw = 1.0f;
            pVtx[1].rhw = 1.0f;
            pVtx[2].rhw = 1.0f;
            pVtx[3].rhw = 1.0f;

            //���_�J���[
            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

            //�e�N�X�`�����W�̐ݒ�
            pVtx[0].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG]);
            pVtx[1].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG]);
            pVtx[2].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG] + 1.0f);
            pVtx[3].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG] + 1.0f);

            pVtx += 4;
            break;
        }

    }

    //���_�o�b�t�@�A�����b�N
    m_pVtxBuff->Unlock();

    return S_OK;
}

//=================================
// �w�i�I������
//=================================
void CBuffUI::Uninit()
{
    //�e�N�X�`���̔j��
    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        if (m_pTexBuff[nCntBG] != NULL)
        {
            m_pTexBuff[nCntBG]->Release();
            m_pTexBuff[nCntBG] = NULL;
        }
    }

    //���_�o�b�t�@�̔j��
    if (m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }

    CObject::Release();
}

//=========================
// �w�i�X�V����
//=========================
void CBuffUI::Update()
{
    int nCntBG;
    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@���b�N
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    if (m_bAlphaSwitch == false)
    {
        m_nAlphaCnt--;
    }

    if (m_bAlphaSwitch == true)
    {
        m_nAlphaCnt++;
    }

    if (m_nAlphaCnt == 205)
    {
        m_bAlphaSwitch = true;
    }

    if (m_nAlphaCnt == 255)
    {
        m_bAlphaSwitch = false;
    }

    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {

        //if (nCntBG == 0)
        //{
        //    m_aPosTexV[nCntBG] -= 0.00f;
        //}
        //else if (nCntBG == 1)
        //{
        //    m_aPosTexV[nCntBG] -= 0.003f;
        //}
        //else if (nCntBG == 2)
        //{
        //    m_aPosTexV[nCntBG] -= 0.0020f;
        //}

        ////�e�N�X�`�����W�̐ݒ�
        //pVtx[0].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG]);
        //pVtx[1].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG]);
        //pVtx[2].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG] + 1.0f);
        //pVtx[3].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG] + 1.0f);



        pVtx[0].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, 255);
        pVtx[1].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, 255);
        pVtx[2].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, 255);
        pVtx[3].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, 255);



        pVtx += 4;
    }


    //���_�o�b�t�@���A�����b�N����
    m_pVtxBuff->Unlock();

    int nFadeState = CFade::GetFadeState();

    if (nFadeState == CFade::FADE_OUT)
    {

        CBuffUI::Uninit();
    }

}

//=========================
// �w�i�`�揈��
//=========================
void CBuffUI::Draw()
{
    int nCntBG;

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        if (m_bUse[nCntBG] == true)
        {
            //�e�N�X�`���̐ݒ�
            pDevice->SetTexture(0, m_pTexBuff[nCntBG]);

            //�|���S���̕`��
            pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
        }
    }
}

void CBuffUI::BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_ICON])
{
    for (int nCnt = 0; nCnt < NUM_ICON; nCnt++)
    {
        m_pTexBuff[nCnt] = pTex[nCnt];
    }
}

//============================
//�o�t�t�^UI�̐�������
//============================
CBuffUI* CBuffUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CBuffUI* pBuffUI;

    pBuffUI = new CBuffUI;

    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        pBuffUI->m_nPos[nCntBG] = pos;
        pBuffUI->m_nSize[nCntBG] = size;
    }

    if (FAILED(pBuffUI->Init()))
    {
        delete pBuffUI;
        return nullptr;
    }

    int nCntBG;

    LPDIRECT3DTEXTURE9 pTexture[NUM_ICON];

    //�e�N�X�`���ǂݍ���
    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        switch (nCntBG)
        {
        case 0:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\spdup_icon.png", &pTexture[nCntBG]);
            break;
        case 1:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\instant_icon.png", &pTexture[nCntBG]);
            break;
        }

        if (!pTexture[nCntBG])
        {
            pBuffUI->Uninit();
            delete pBuffUI;
            return nullptr;
        }
    }

    pBuffUI->BindTexture(pTexture);

    return pBuffUI;
}

//============================
//UI��\�������鏈��
//============================
bool CBuffUI::DisplayBuffUI(int nDisplayID, int DisplayOption)
{
    //�\������ꍇ
    if (DisplayOption == CBuffUI::UIDISPLAY::UI_DISPLAY)
    {
        m_bUse[nDisplayID] = true;
    }

    //��\���ɂ���ꍇ
    if (DisplayOption == CBuffUI::UIDISPLAY::UI_HIDDEN)
    {
        m_bUse[nDisplayID] = false;
    }

    return m_bUse[nDisplayID];
}
