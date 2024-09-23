//=================================================
//
// �X�^�[�g�R�[��UI�\������ (startcallui.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "endcallui.h"

bool CEndCallUI::m_bUse[NUM_ICON] = {};
bool CEndCallUI::m_bEndComplete = true;

//============================
//�R���X�g���N�^
//============================
CEndCallUI::CEndCallUI(int nPriority) : CObject2D(nPriority)
{
    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        m_pTexBuff[nCntBG] = nullptr;
    }

    m_bUse[0] = false;
    m_bUse[1] = false;
    m_bUse[2] = false;
    m_pVtxBuff = nullptr;
    m_nAlphaCnt = 255;
    m_nMissonAnim = 0;
    m_bAlphaSwitch = false;
    m_bImageSwitch = false;
    m_bEndComplete = true;
}

//============================
//�f�X�g���N�^
//============================
CEndCallUI::~CEndCallUI()
{

}

//=====================
// �w�i����������
//======================
HRESULT CEndCallUI::Init()
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
            pVtx[0].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
            pVtx[1].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
            pVtx[2].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);
            pVtx[3].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);

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
        case 2:
            //���_���W�̐ݒ�
            pVtx[0].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
            pVtx[1].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
            pVtx[2].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);
            pVtx[3].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);

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
void CEndCallUI::Uninit()
{
    //�e�N�X�`���̔j��
    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        if (m_pTexBuff[nCntBG] != nullptr)
        {
            m_pTexBuff[nCntBG]->Release();
            m_pTexBuff[nCntBG] = nullptr;
        }
    }

    //���_�o�b�t�@�̔j��
    if (m_pVtxBuff != nullptr)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = nullptr;
    }

    CObject::Release();
}

//=========================
// �w�i�X�V����
//=========================
void CEndCallUI::Update()
{

    //�t�F�[�h�̏�Ԃ��擾
    int nFadeState = CFade::GetFadeState();

    //�t�F�[�h�A�E�g�ɂȂ����ꍇ�A�I�������Ɉڍs
    if (nFadeState == CFade::FADE_OUT)
    {
        CEndCallUI::Uninit();
        return;
    }


    if (m_bUse[CEndCallUI::ICON_SUCCESS] == true)
    {
        CScene::UpdateSwitch(0);
        m_bEndComplete = false;

        if (m_nPos[CEndCallUI::ICON_SUCCESS].y <= 160.0f)
        {
            m_nPos[CEndCallUI::ICON_SUCCESS].y += 6.0f;
        }

        if (m_nPos[CEndCallUI::ICON_SUCCESS].y >= 160.0f)
        {
            m_nPos[CEndCallUI::ICON_SUCCESS].y == 160.0f;
            m_nMissonAnim++;

            if (m_nMissonAnim == 160)
            {
                m_bEndComplete = true;
                CManager::GetFade()->SetFade(CScene::MODE_RESULT);
                m_bUse[CEndCallUI::ICON_SUCCESS] = false;
                m_nMissonAnim = 0;
                //CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_STARTCALL2);
            }
        }
    }

    //=================
    //�ʃe�N�X�`����\��������
    //================
    if (m_bUse[CEndCallUI::ICON_FAILED] == true)
    {
        CScene::UpdateSwitch(0);
        m_bEndComplete = false;

        if (m_nPos[CEndCallUI::ICON_FAILED].y <= 160.0f)
        {
            m_nPos[CEndCallUI::ICON_FAILED].y += 6.0f;
        }

        if (m_nPos[CEndCallUI::ICON_FAILED].y >= 160.0f)
        {
            m_nPos[CEndCallUI::ICON_FAILED].y == 160.0f;
            m_nMissonAnim++;

            if (m_nMissonAnim == 160)
            {
                m_bEndComplete = true;
                CManager::GetFade()->SetFade(CScene::MODE_RESULT);
                m_bUse[CEndCallUI::ICON_FAILED] = false;
                m_nMissonAnim = 0;
                //CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_STARTCALL2);
            }
        }
    }

    if (m_bUse[CEndCallUI::ICON_SPSUCCESS] == true)
    {
        CScene::UpdateSwitch(0);
        m_bEndComplete = false;

        if (m_nPos[CEndCallUI::ICON_SPSUCCESS].y <= 160.0f)
        {
            m_nPos[CEndCallUI::ICON_SPSUCCESS].y += 6.0f;
        }

        if (m_nPos[CEndCallUI::ICON_SPSUCCESS].y >= 160.0f)
        {
            m_nPos[CEndCallUI::ICON_SPSUCCESS].y == 160.0f;
            m_nMissonAnim++;

            if (m_nMissonAnim == 160)
            {
                m_bEndComplete = true;
                CManager::GetFade()->SetFade(CScene::MODE_RESULT);
                m_bUse[CEndCallUI::ICON_SPSUCCESS] = false;
                m_nMissonAnim = 0;
                //CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_STARTCALL2);
            }
        }
    }


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

    SetAlpha(m_nAlphaCnt);

}

void CEndCallUI::SetAlpha(int nAlpha)
{
    int nCntBG;
    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@���b�N
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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

        pVtx[0].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
        pVtx[1].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
        pVtx[2].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);
        pVtx[3].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);

        pVtx[0].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt);
        pVtx[1].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt);
        pVtx[2].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt);
        pVtx[3].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt);



        pVtx += 4;
    }


    //���_�o�b�t�@���A�����b�N����
    m_pVtxBuff->Unlock();
}

//=========================
// �w�i�`�揈��
//=========================
void CEndCallUI::Draw()
{
    int nCntBG;

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject::VERTEX_2D));

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

void CEndCallUI::BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_ICON])
{
    for (int nCnt = 0; nCnt < NUM_ICON; nCnt++)
    {
        m_pTexBuff[nCnt] = pTex[nCnt];
    }
}

//============================
//�o�t�t�^UI�̐�������
//============================
CEndCallUI* CEndCallUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CEndCallUI* pEndCallUI;

    pEndCallUI = new CEndCallUI;

    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        pEndCallUI->m_nPos[nCntBG] = pos;
        pEndCallUI->m_nSize[nCntBG] = size;
    }

    if (FAILED(pEndCallUI->Init()))
    {
        delete pEndCallUI;
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
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\goal_window.png", &pTexture[nCntBG]);
            break;
        case 1:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\dead_window.png", &pTexture[nCntBG]);
            break;
        case 2:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\spgoal_window.png", &pTexture[nCntBG]);
            break;
        }

        if (!pTexture[nCntBG])
        {
            pEndCallUI->Uninit();
            delete pEndCallUI;
            return nullptr;
        }
    }

    pEndCallUI->BindTexture(pTexture);

    return pEndCallUI;
}

//============================
//UI��\�������鏈��
//============================
bool CEndCallUI::DisplayEndCallUI(int nDisplayID, int DisplayOption)
{
    //�\������ꍇ
    if (DisplayOption == CEndCallUI::UIDISPLAY::UI_DISPLAY)
    {
        m_bUse[nDisplayID] = true;
    }

    //��\���ɂ���ꍇ
    if (DisplayOption == CEndCallUI::UIDISPLAY::UI_HIDDEN)
    {
        m_bUse[nDisplayID] = false;
    }

    //�N���A���̉���
    if (m_bUse[CEndCallUI::ICON_SUCCESS] == true)
    {
        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_CLEAR);
    }


    //SP�N���A���̉���
    else if (m_bUse[CEndCallUI::ICON_SPSUCCESS] == true)
    {
        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_CLEAR);
    }

    //���s���̉���
    else if (m_bUse[CEndCallUI::ICON_FAILED] == true)
    {
        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_FAILED);
    }

    return m_bUse[nDisplayID];
}
