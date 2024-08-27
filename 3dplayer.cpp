//=================================================
//
// 3D���f���̃v���C���[�̕\������ (3dplayer.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dblock.h"
#include "3dmoveblock.h"
#include "player.h"
#include "block.h"
#include "startobj.h"
#include "3ditem.h"
#include "3dbullet.h"
#include "3dchargebullet.h"
#include "3denemy.h"
#include "3dbrokenblock.h"
#include "3dwall.h"
#include "3dgoalobj.h"
#include "timer.h"
#include "floor.h"
#include "score.h"
#include "3dchargeshotui.h"
#include "3daddlifeui.h"

LPDIRECT3DTEXTURE9 C3dplayer::m_pTexBuff = nullptr;
int C3dplayer::m_nLife = 0;
bool C3dplayer::m_bAButtonPressed = false;

//======================
// �R���X�g���N�^
//======================
C3dplayer::C3dplayer(int nPriority) : CModel(nPriority)
{
    m_bPlayerBuff = false;
    m_bInstantShot = false;
    m_nBuffTime = 0;
    m_nInstantShotTime = 0;
    m_nLife = PLAYER_LIFE;
    m_bAButtonPressStartTime = false;
    m_bAButtonPressed = 0;
    m_nJumpCnt = 0;
}

//======================
// �f�X�g���N�^
//======================
C3dplayer::~C3dplayer()
{

}

//======================
// ����������
//======================
HRESULT C3dplayer::Init()
{
    //������
    if (FAILED(CModel::Init()))
    {
        return E_FAIL;
    }

    return S_OK;
}

//======================
// �I������
//======================
void C3dplayer::Uninit()
{
    CModel::Uninit();
}

//======================
// �X�V����
//======================
void C3dplayer::Update()
{
    D3DXVECTOR3 Pos = CObject3D::GetPos();

    //SetPlayerPos();

    int nCnt = 0;

    //�v���C���[�̍ő�̗͒l�𒴂��Ȃ��悤�ɂ���
    if (m_nLife >= PLAYER_LIFE)
    {
        m_nLife = PLAYER_LIFE;
    }

    //�d�͂̓K�p
    m_n3DPlayerMove.y -= 1.0f;

    //�v���C���[��HP��0�ȏ�̏ꍇ�̂ݒʂ�
    if (m_nLife > 0)
    {
        if (CManager::GetKeyboard()->GetPress(DIK_D) || CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_RIGHT))
        {
            if (m_bPlayerBuff == false)
            {
                m_n3DPlayerMove.x += PLAYER_MOVE_SPD;
                m_rot.y = D3DX_PI * -0.5f;
            }

            if (m_bPlayerBuff == true)
            {
                m_n3DPlayerMove.x += PLAYER_MOVE_SPD * PLAYER_MOVE_BOOST;
                m_rot.y = D3DX_PI * -0.5f;
            }
        }


        //�v���C���[�̃W�����v����
        if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A))
        {
            //�v���C���[�̃W�����v����0�̏ꍇ(2�i�ȏ�̃W�����v�h�~)
            if (m_nJumpCnt == 0)
            {
                m_n3DPlayerMove.y += 30.0f;
                m_nJumpCnt++;
            }
        }

        if (CManager::GetKeyboard()->GetPress(DIK_A)|| CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_LEFT))
        {
            if (m_bPlayerBuff == false)
            {
                m_n3DPlayerMove.x -= PLAYER_MOVE_SPD;
                m_rot.y = D3DX_PI * 0.5f;
            }

            if (m_bPlayerBuff == true)
            {
                m_n3DPlayerMove.x -= PLAYER_MOVE_SPD * PLAYER_MOVE_BOOST;
                m_rot.y = D3DX_PI * 0.5f;
            }
        }

        //W�L�[�܂��́A�\���L�[�㉟����
        if (CManager::GetKeyboard()->GetPress(DIK_W) || CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_UP))
        {
            if (m_bPlayerBuff == false)
            {
                m_n3DPlayerMove.z += PLAYER_MOVE_SPD;
                m_rot.y = D3DX_PI;
            }

            if (m_bPlayerBuff == true)
            {
                m_n3DPlayerMove.z += PLAYER_MOVE_SPD * PLAYER_MOVE_BOOST;
                m_rot.y = D3DX_PI;
            }
        }

        //S�L�[�܂��́A�\���L�[��������
        if (CManager::GetKeyboard()->GetPress(DIK_S) || CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_DOWN))
        {
            if (m_bPlayerBuff == false)
            {
                m_n3DPlayerMove.z -= PLAYER_MOVE_SPD;
                m_rot.y = -D3DX_PI * -0.0f;
            }

            if (m_bPlayerBuff == true)
            {
                m_n3DPlayerMove.z -= PLAYER_MOVE_SPD * PLAYER_MOVE_BOOST;
                m_rot.y = D3DX_PI * -0.0f;
            }
        }
    }

    //������
    if (CManager::GetKeyboard()->GetTrigger(DIK_M) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_RB))
    {
        //�`���[�W�V���b�g�����˃o�t���L���̏ꍇ�͒ʂ��Ȃ�
        if (m_bInstantShot == false)
        {
            C3dbullet::Create(Pos, D3DXVECTOR3(7.0f, 7.0f, 0.0f), m_rot,0);
        }
    }

    // �X�y�[�X�L�[�������ꂽ�Ƃ� (����������)
    if (CManager::GetKeyboard()->GetPress(DIK_M) || CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_RB))
    {
        // �X�y�[�X�L�[���܂�������Ă��Ȃ��ꍇ
        if (!m_bAButtonPressed)
        {
            m_bAButtonPressed = true;
            m_bAButtonPressStartTime = GetTickCount64(); // �^�C���X�^���v���L�^
        }
        //�X�y�[�X�L�[��2�b�ȏ㒷�������Ă���ꍇ
        else if ((CManager::GetKeyboard()->GetPress(DIK_M) == true && (GetTickCount64() - m_bAButtonPressStartTime >= 2000))|| (CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_RB) == true && (GetTickCount64() - m_bAButtonPressStartTime >= 2000)))
        {
            CChargeshotui::DisplayShotOKUI();
        }
    }
    else
    {
        // �X�y�[�X�L�[�������ꂽ�ꍇ�����������Ԃ�2�b�ȏ�̏ꍇ
        if (m_bAButtonPressed && (GetTickCount64() - m_bAButtonPressStartTime >= 2000))
        {
            
            //�`���[�W�V���b�g�����˃o�t���L���̏ꍇ�͒ʂ��Ȃ�
            if (m_bInstantShot == false)
            {
                // �ʂ̔��˂����s
                C3dchargebullet::Create(Pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), m_rot);
            }

        }
        // J�L�[�̃t���O�����Z�b�g
        m_bAButtonPressed = false;


    }

    //������
    if (CManager::GetKeyboard()->GetTrigger(DIK_M) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_RB))
    {
        //�`���[�W�V���b�g�����˃o�t���L���̏ꍇ�͒ʂ��Ȃ�
        if (m_bInstantShot == true)
        {
            C3dchargebullet::Create(Pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), m_rot);
        }
    }

    //�v���C���[��HP�����炷
    if (CManager::GetKeyboard()->GetPress(DIK_K))
    {
        m_nLife -= 1;
    }

    if (CManager::GetKeyboard()->GetPress(DIK_N))
    {
        CScore::AddScore(2000); //�c�莞�Ԃ�ǉ�
    }

    //�v���C���[�̗̑͂�0�ȉ��ɂȂ����ꍇ���U���g��ʂ֑J��
    if (m_nLife <= 0)
    {
        Uninit();
        CManager::GetFade()->SetFade(CScene::MODE_RESULT);
    }

    ////�^�C�}�[�̏����𖳌��ɂ��Ă鎞�̂ݎg�p
    //if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
    //{
    //    Uninit();
    //    CManager::GetFade()->SetFade(CScene::MODE_GAME);
    //}

    //�ߋ����W��ۑ�
    m_nOld3DPlayerPos = Pos;

    Pos.x += m_n3DPlayerMove.x;
    Pos.y += m_n3DPlayerMove.y;
    Pos.z += m_n3DPlayerMove.z;

    //�o�t�A�C�e���̓����蔻��
    for (int nCntObj = 0; nCntObj < C3ditem::MAX_ITEM; nCntObj++)
    {
        CObject* pObj = CObject::GetObj(3, nCntObj);

        if (pObj != nullptr)
        {
            CObject::TYPE type = pObj->GetType();

            C3ditem * p3dItem = (C3ditem*)pObj;

            D3DXVECTOR3 EnemyPos = p3dItem->GetPos();

            //�v���C���[�ړ����x�㏸�A�C�e���̏ꍇ
            if (type == CObject::TYPE::ITEM_WALKSPDUP)
            {
                if (CObject3D::GetPos().x >= EnemyPos.x - 40
                    && CObject3D::GetPos().x <= EnemyPos.x + 40
                    && CObject3D::GetPos().z >= EnemyPos.z - 40
                    && CObject3D::GetPos().z <= EnemyPos.z + 40)
                {
                    //�o�t���ʂ��������̏ꍇ�͌��ʎ��Ԃ����Z�b�g����
                    if (m_bPlayerBuff == true)
                    { 
                        m_nBuffTime = 0;
                    }

                    //�o�t���ʂ��t�^����ĂȂ��ꍇ
                    if (m_bPlayerBuff == false)
                    {
                        m_bPlayerBuff = true;
                    }

                    p3dItem->Uninit();
                    return;
                }
            }

            //�`���[�W�V���b�g�����˃o�t�A�C�e���̏ꍇ
            if (type == CObject::TYPE::ITEM_INSTANTSHOT)
            {
                if (CObject3D::GetPos().x >= EnemyPos.x - 40
                    && CObject3D::GetPos().x <= EnemyPos.x + 40
                    && CObject3D::GetPos().z >= EnemyPos.z - 40
                    && CObject3D::GetPos().z <= EnemyPos.z + 40)
                {
                    //�o�t���ʂ��������̏ꍇ�͌��ʎ��Ԃ����Z�b�g����
                    if (m_bInstantShot == true)
                    {
                        m_nInstantShotTime = 0;
                    }

                    //�o�t���ʂ��t�^����ĂȂ��ꍇ
                    if (m_bInstantShot == false)
                    {
                        m_bInstantShot = true; //�����˃t���O��L���ɂ���
                    }
                    
                    p3dItem->Uninit();
                    return;
                }
            }
            //�^�C�}�[�ǉ��A�C�e���̏ꍇ
            if (type == CObject::TYPE::ITEM_ADDTIMER)
            {
                if (CObject3D::GetPos().x >= EnemyPos.x - 40
                    && CObject3D::GetPos().x <= EnemyPos.x + 40
                    && CObject3D::GetPos().z >= EnemyPos.z - 40
                    && CObject3D::GetPos().z <= EnemyPos.z + 40)
                {
                    CTimer::AddTimer(20); //�c�莞�Ԃ�ǉ�
                    p3dItem->Uninit();
                    return;
                }
            }

            //�̗͒ǉ��A�C�e���̏ꍇ
            if (type == CObject::TYPE::ITEM_ADDLIFE)
            {
                if (CObject3D::GetPos().x >= EnemyPos.x - 40
                    && CObject3D::GetPos().x <= EnemyPos.x + 40
                    && CObject3D::GetPos().z >= EnemyPos.z - 40
                    && CObject3D::GetPos().z <= EnemyPos.z + 40)
                {
                    CAddlifeui::DisplayAddLifeUI();
                    m_nLife += 15;
                    p3dItem->Uninit();
                    return;
                }
            }
        }
    }


    //�v���C���[�ړ����x�㏸������true�̏ꍇ
    if (m_bPlayerBuff == true)
    {
        m_nBuffTime++;

        //10�b��������false�ɂ���
        if (m_nBuffTime == 600)
        {
            m_bPlayerBuff = false;
        }
    }

    //�v���C���[�ړ����x�㏸������false�̏ꍇ
    if (m_bPlayerBuff == false)
    {
        m_nBuffTime = 0;
    }

    //�`���[�W�V���b�g�����˃o�t��true�̏ꍇ
    if (m_bInstantShot == true)
    {
        m_nInstantShotTime++;

        //6�b��������false�ɂ���
        if (m_nInstantShotTime == 360)
        {
            m_bInstantShot = false;
        }
    }

    //�`���[�W�V���b�g�����˃o�t��true�̏ꍇ
    if (m_bInstantShot == false)
    {
        m_nInstantShotTime = 0;
    }

    //�u���b�N�Ƃ̓����蔻��̕␳
    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        for (int nCntObj = 0; nCntObj < C3dblock::GetMaxBlock() +10; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                if (type == CObject::TYPE::BLOCK)
                {
                    C3dblock* p3dblock = (C3dblock*)pObj;

                    bool bIsCollision = p3dblock->Collision3DBlock(&Pos,&m_nOld3DPlayerPos,&m_n3DPlayerMove,50.0f,50.0f);

                    if (bIsCollision == true)
                    {
                        if (p3dblock->GetMoveBlock().z >= 0.01f)
                        {
                            m_n3DPlayerMove.y = 0.0f;
                            Pos.z += p3dblock->GetMoveBlock().z;
                        }

                        if (p3dblock->GetMoveBlock().z <= -0.01f)
                        {
                            m_n3DPlayerMove.y = 0.0f;
                            Pos.z += p3dblock->GetMoveBlock().z;
                        }
                    }

                }

            }
        }
    }

    //�u���b�N�Ƃ̓����蔻��̕␳
    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        for (int nCntObj = 0; nCntObj < 10; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                if (type == CObject::TYPE::MOVEBLOCK_Z)
                {
                    C3dmoveblock* p3dmoveblock = (C3dmoveblock*)pObj;

                    bool bIsCollision = p3dmoveblock->Collision3DMoveblock(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (p3dmoveblock->GetMoveBlockZ().z >= 0.01f)
                        {
                            m_n3DPlayerMove.y = 0.0f;
                            m_nJumpCnt = 0;
                            Pos.z += (p3dmoveblock->GetMoveBlockZ().z * 2);
                        }

                        if (p3dmoveblock->GetMoveBlockZ().z <= -0.01f)
                        {
                            m_n3DPlayerMove.y = 0.0f;
                            m_nJumpCnt = 0;
                            Pos.z += (p3dmoveblock->GetMoveBlockZ().z * 2);
                        }
                    }

                }

            }
        }
    }

    //�j��\�u���b�N�Ƃ̓����蔻��
    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        for (int nCntObj = 0; nCntObj < C3dbrokenblock::MAX_BLOCK; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                if (type == CObject::TYPE::BROKENBLOCK)
                {
                    C3dbrokenblock* p3dbrokenblock = (C3dbrokenblock*)pObj;

                    bool bIsCollision = p3dbrokenblock->Collision3DBrokenBlock(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (m_n3DPlayerMove.z >= 0.1f && p3dbrokenblock->GetMoveBlock().z >= 0.1f || m_n3DPlayerMove.z <= 0.1f && p3dbrokenblock->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dbrokenblock->GetMoveBlock().z;
                        }

                        if (m_n3DPlayerMove.z >= 0.1f && p3dbrokenblock->GetMoveBlock().z <= -0.1f || m_n3DPlayerMove.z <= -0.1f && p3dbrokenblock->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dbrokenblock->GetMoveBlock().z * PLAYER_MOVE_BOOST);
                        }
                    }

                }

            }
        }
    }

    //�ǃu���b�N�Ƃ̓����蔻��
    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        for (int nCntObj = 0; nCntObj < C3dbrokenblock::MAX_BLOCK; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                if (type == CObject::TYPE::WALL_WIDTH)
                {
                    C3dwall* p3dwall = (C3dwall*)pObj;

                    bool bIsCollision = p3dwall->Collision3DWall(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (m_n3DPlayerMove.z >= 0.1f && p3dwall->GetMoveBlock().z >= 0.1f || m_n3DPlayerMove.z <= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dwall->GetMoveBlock().z;
                        }

                        if (m_n3DPlayerMove.z >= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f || m_n3DPlayerMove.z <= -0.1f && p3dwall->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dwall->GetMoveBlock().z * PLAYER_MOVE_BOOST);
                        }
                    }

                }

                if (type == CObject::TYPE::WALL_WIDTH_SHORT)
                {
                    C3dwall* p3dwall = (C3dwall*)pObj;

                    bool bIsCollision = p3dwall->Collision3DWallShort(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (m_n3DPlayerMove.z >= 0.1f && p3dwall->GetMoveBlock().z >= 0.1f || m_n3DPlayerMove.z <= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dwall->GetMoveBlock().z;
                        }

                        if (m_n3DPlayerMove.z >= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f || m_n3DPlayerMove.z <= -0.1f && p3dwall->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dwall->GetMoveBlock().z * PLAYER_MOVE_BOOST);
                        }
                    }

                }

                if (type == CObject::TYPE::WALL_HEIGHT)
                {
                    C3dwall* p3dwall = (C3dwall*)pObj;

                    bool bIsCollision = p3dwall->Collision3DHeightWall(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (m_n3DPlayerMove.z >= 0.1f && p3dwall->GetMoveBlock().z >= 0.1f || m_n3DPlayerMove.z <= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dwall->GetMoveBlock().z;
                        }

                        if (m_n3DPlayerMove.z >= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f || m_n3DPlayerMove.z <= -0.1f && p3dwall->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dwall->GetMoveBlock().z * 2);
                        }
                    }

                }

                if (type == CObject::TYPE::WALL_HEIGHT_SHORT)
                {
                    C3dwall* p3dwall = (C3dwall*)pObj;

                    bool bIsCollision = p3dwall->Collision3DHeightWallShort(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (m_n3DPlayerMove.z >= 0.1f && p3dwall->GetMoveBlock().z >= 0.1f || m_n3DPlayerMove.z <= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dwall->GetMoveBlock().z;
                        }

                        if (m_n3DPlayerMove.z >= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f || m_n3DPlayerMove.z <= -0.1f && p3dwall->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dwall->GetMoveBlock().z * 2);
                        }
                    }

                }

            }
        }
    }

    //���Ƃ̓����蔻��̕␳
    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        for (int nCntObj = 0; nCntObj < 1; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                if (type == CObject::TYPE::FLOOR)
                {
                    CFloor* p3dfloor = (CFloor*)pObj;

                    bool bIsCollision = p3dfloor->Collision3DFloor(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 0.0f);

                    if (bIsCollision == true)
                    {
                        m_nJumpCnt = 0;
                        m_n3DPlayerMove.y = 0.0f;
                    }
                }
            }
        }
    }



    //�S�[���}�[�J�[�Ƃ̓����蔻��̕␳
    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        for (int nCntObj = 0; nCntObj < C3dblock::MAX_BLOCK; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                if (type == CObject::TYPE::GOAL)
                {
                    C3dgoalobj* p3dgoalobj = (C3dgoalobj*)pObj;

                    bool bIsCollision = p3dgoalobj->Collision3DGoalobj(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 50.0f);
                }
            }
        }
    }

    //���W��ݒ�
    SetPos(Pos);

    //X���W�̈ړ��ʂ��X�V
    m_n3DPlayerMove.x += (Length_value2 - m_n3DPlayerMove.x) * Attenuation_value;

    //Y���W�̈ړ��ʂ��X�V
    m_n3DPlayerMove.y += (Length_value2 - m_n3DPlayerMove.y) * Attenuation_value;

    //Z���W�̈ړ��ʂ��X�V
    m_n3DPlayerMove.z += (Length_value2 - m_n3DPlayerMove.z) * Attenuation_value;

 
}

//======================
// �`�揈��
//======================
void C3dplayer::Draw()
{
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
    D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
    D3DXMATERIAL* pMat; //�}�e���A���f�[�^�ւ̃|�C���^
    D3DXVECTOR3 Pos = CObject3D::GetPos();

    //���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxworld);

    //�����𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

    //�ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld , &mtxTrans);

    ////���f���̉e�̐ݒ�
    //D3DXMATRIX mtxshadow , mtxshadowTrans;
    //D3DXPLANE plane;
    //D3DXVECTOR4 vecLight;
    //D3DXVECTOR3 pos, nor;

    //D3DXMatrixIdentity(&mtxshadow);

    ////���C�g�̋t�����x�N�g����ݒ�
    //vecLight = D3DXVECTOR4(0.5f, 0.6f, 0.7f,1.0f);
    //pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
    //nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

    //D3DXPlaneFromPointNormal(&plane, &pos, &nor);
    //D3DXMatrixShadow(&mtxshadow,&vecLight,&plane);

    //m_mtxworld * mtxshadow;

    //���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

    //�}�e���A�����擾
    pDevice->GetMaterial(&matDef);

    for (int nCntParts = 0; nCntParts < NUM_MODEL; nCntParts++)
    {
        //���[���h�}�g���b�N�X�̏�����
        D3DXMatrixIdentity(&m_aModel[nCntParts].mtxworld);

        //�����𔽉f
        D3DXMatrixRotationYawPitchRoll(&mtxRot, m_aModel[nCntParts].rot.y, m_aModel[nCntParts].rot.x, m_aModel[nCntParts].rot.z);
        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxRot);

        //�ʒu�𔽉f
        D3DXMatrixTranslation(&mtxTrans, m_aModel[nCntParts].pos.x, m_aModel[nCntParts].pos.y, m_aModel[nCntParts].pos.z);
        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxTrans);

        //�e�q�֌W
        D3DXMATRIX mtxParent;


        if (m_aModel[nCntParts].nIdxModelParent == -1)
        {
            mtxParent = m_mtxworld;
        }

        else
        {
            mtxParent = m_aModel[m_aModel[nCntParts].nIdxModelParent].mtxworld;
        }

        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxParent);

        if (m_aModel[nCntParts].bUse == true)
        {
            //�}�g���b�N�X�̐ݒ�
            pDevice->SetTransform(D3DTS_WORLD, &m_aModel[nCntParts].mtxworld);

            pMat = (D3DXMATERIAL*)m_pBuffMat[nCntParts]->GetBufferPointer();


            for (int nCntMat = 0; nCntMat < (int)m_nNumMat[nCntParts]; nCntMat++)
            {
                //�}�e���A���̐ݒ�
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                //�e�N�X�`���̐ݒ�
                pDevice->SetTexture(0, m_pTexBuff);

                //�e�N�X�`�������݂���
                if (pMat[nCntMat].pTextureFilename != NULL)
                {
                    //�e�N�X�`���̐ݒ�
                    pDevice->SetTexture(0,&m_aModel[0].m_pTexture[nCntMat]);
                }

                else
                {
                    //�e�N�X�`���̐ݒ�
                    pDevice->SetTexture(0, NULL);
                }

                if (m_nLife > 0)
                {
                    //���f��(�p�[�c)�̕`��
                    m_pMesh[nCntParts]->DrawSubset(nCntMat);
                }

            }
        }

    }

    pDevice->SetMaterial(&matDef);
}

//======================
// �I�u�W�F�N�g��������
//======================
C3dplayer* C3dplayer::Create(D3DXVECTOR3 pos)
{
    C3dplayer* D3Dplayer = nullptr;

    D3Dplayer = new C3dplayer;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3Dplayer->Init()))
    {
        D3Dplayer->SetType(TYPE::PLAYER);

        D3Dplayer->LoadPlayerData();

        D3Dplayer->CObject3D::SetPos(pos);

        //D3Dplayer->Load();//�e�N�X�`����ݒ�(��)


        ////�e�N�X�`���̐ݒ�
        //Model->BindTexture(m_pTexBuff);
    }

    return D3Dplayer;
}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT C3dplayer::Load()
{
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    if (FAILED(D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\samplepos.png", &m_pTexBuff)))
    {
        return E_FAIL;
    }

    return S_OK;
}

//======================
// �e�N�X�`���A�����[�h(�I��)����
//======================
void C3dplayer::Unload()
{
    CModel::Unload();
}

void C3dplayer::PlayerDamage(int nDamage)
{
    m_nLife -= nDamage;
}

//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================
void C3dplayer::LoadPlayerData(void)
{
    char Datacheck[MAX_CHAR];
    int nCntEnemyData = 0;
    int EnemyModelSave = 0;

    //m_pFile = fopen("data\\MODEL\\MODEL_golden_man\\motion.txt", "r");//�t�@�C�����J��
    m_pFile = fopen("data\\MODEL\\MODEL_SLIME\\motion.txt", "r");//�t�@�C�����J��

    //�t�@�C�������݂��Ȃ��ꍇ
    if (m_pFile == NULL)
    {
        return;
    }

    //�O���t�@�C��������ǂݎ��
    while (1)
    {
        fscanf(m_pFile, "%s", Datacheck);

        if (!strcmp(Datacheck, "END_CHARACTERSET"))
        {
            fclose(m_pFile);
            break;
        }

        if (Datacheck[0] == '#')
        {
            continue;
        }

        //�p�[�c��
        if (!strcmp(Datacheck, "NUM_PARTS"))
        {
            fscanf(m_pFile, "%s", Datacheck);
            fscanf(m_pFile, "%d", &EnemyModelSave);
        }

        //�t�@�C����
        if (!strcmp(Datacheck, "MODEL_FILENAME"))
        {
            fscanf(m_pFile, "%s", Datacheck);
            fscanf(m_pFile, "%s", &CModel::m_aLoadEnemy[EnemyModelSave].filename[0]);
            EnemyModelSave++;
        }

        //�p�[�c�̏ڍ�
        if (!strcmp(Datacheck, "PARTSSET"))
        {
            while (1)
            {
                fscanf(m_pFile, "%s", Datacheck);

                //�p�[�c�ڍ׏I��茟�m
                if (!strcmp(Datacheck, "END_PARTSSET"))
                {
                    break;
                }

                //�C���f�b�N�X
                else if (!strcmp(Datacheck, "INDEX"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%d", &CModel::m_aLoadEnemy[nCntEnemyData].index);
                }

                //�e�ݒ�
                else if (!strcmp(Datacheck, "PARENT"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%d", &CModel::m_aLoadEnemy[nCntEnemyData].parent);
                }

                //�����ʒu
                else if (!strcmp(Datacheck, "POS"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].pos.x);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].pos.y);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].pos.z);
                }

                //����
                else if (!strcmp(Datacheck, "ROT"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].rot.x);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].rot.y);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].rot.z);
                }
            }
            nCntEnemyData++;
        }
    }

    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    //�����ŏ�L�̏����œ������l����
    for (int nCnt = 0; nCnt < EnemyModelSave; nCnt++)
    {
        D3DXLoadMeshFromX(&CModel::m_aLoadEnemy[nCnt].filename[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[nCnt], NULL, &m_nNumMat[nCnt], &m_pMesh[nCnt]);
        //D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\golden000.jpg", &m_pTexture);
        m_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_aModel[nCnt].nLife = 4;
        m_aModel[nCnt].nIdxModelParent = CModel::m_aLoadEnemy[nCnt].parent;
        m_aModel[nCnt].bUse = true;

        //�G�̗����ʒu������
        //m_nPos = D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
        //m_aEnemy.rot = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);

        m_aModel[nCnt].pos = D3DXVECTOR3(CModel::m_aLoadEnemy[nCnt].pos.x, CModel::m_aLoadEnemy[nCnt].pos.y, CModel::m_aLoadEnemy[nCnt].pos.z);
        m_aModel[nCnt].rot = D3DXVECTOR3(CModel::m_aLoadEnemy[nCnt].rot.x, CModel::m_aLoadEnemy[nCnt].rot.y, CModel::m_aLoadEnemy[nCnt].rot.z);
    }
}