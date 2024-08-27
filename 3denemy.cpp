//=================================================
//
// 3D���f���̃v���C���[�̕\������ (3denemy.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dblock.h"
#include "player.h"
#include "block.h"
#include "startobj.h"
#include "3ditem.h"
#include "3denemy.h"
#include "3dbullet.h"
#include "3dchargebullet.h"
#include "3dbrokenblock.h"
#include "3dwall.h"

LPDIRECT3DTEXTURE9 C3denemy::m_pTexBuff = nullptr;
//======================
// �R���X�g���N�^
//======================
C3denemy::C3denemy(int nPriority) : CModel(nPriority)
{
    m_nShotInterval = 0;
    m_nMoveInterval = 0;
    m_nLife = 3;
    m_bMoveSwitch = false;
}

//======================
// �f�X�g���N�^
//======================
C3denemy::~C3denemy()
{

}

//======================
// ����������
//======================
HRESULT C3denemy::Init()
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
void C3denemy::Uninit()
{
    CModel::Uninit();
}

//======================
// �X�V����
//======================
void C3denemy::Update()
{
    D3DXVECTOR3 Pos = CObject3D::GetPos();

    int nCnt = 0;

    //�v���C���[��HP��0�ȏ�̏ꍇ�̂ݒʂ�
    if (m_nLife > 0)
    {
        m_nShotInterval++;
    }

    //������(1�b���̊Ԋu�Ŕ���)
    if (m_nShotInterval == SHOT_INTERVAL)
    {
        C3dbullet::Create(Pos, D3DXVECTOR3(7.0f, 7.0f, 0.0f), m_rot, 1);
        m_nShotInterval = 0;
    }


    if (m_nMoveInterval == 0)
    {
        m_bMoveSwitch = false;

    }

    if (m_nMoveInterval == MOVE_INTERVAL)
    {
        m_bMoveSwitch = true;
    }

    //�t�֕����]������t���O�������̏ꍇ
    if (m_bMoveSwitch == false)
    {
        m_nMoveInterval++;

        if (GetType() == TYPE::ENEMY_XMOVE)
        {
            m_n3DEnemyMove.x += 0.4f;
            m_rot.y = D3DX_PI * -0.5f;
        }

        if (GetType() == TYPE::ENEMY_ZMOVE)
        {
            m_n3DEnemyMove.z += 0.4f;
            m_rot.y = D3DX_PI;
        }
    }

    //�t�֕����]������t���O���L���̏ꍇ
    if (m_bMoveSwitch == true)
    {
        m_nMoveInterval--;

        if (GetType() == TYPE::ENEMY_XMOVE)
        {
            m_n3DEnemyMove.x -= 0.4f;
            m_rot.y = D3DX_PI * 0.5f;
        }

        if (GetType() == TYPE::ENEMY_ZMOVE)
        {
            m_n3DEnemyMove.z -= 0.4f;
            m_rot.y = D3DX_PI * -0.0f;
        }
    }

    //�G��HP�����炷
    if (CManager::GetKeyboard()->GetTrigger(DIK_9))
    {
        m_nLife -= 1;
    }

    if (m_nLife <= 0)
    {
         Uninit();
    }


    //�ߋ����W��ۑ�
    m_nOld3DEnemyPos = Pos;

    Pos.x += m_n3DEnemyMove.x;
    Pos.z += m_n3DEnemyMove.z;

    //�u���b�N�Ƃ̓����蔻��̕␳
    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        for (int nCntObj = 0; nCntObj < MAX_ENEMY; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                if (type == CObject::TYPE::BLOCK)
                {
                    C3dblock* p3dblock = (C3dblock*)pObj;

                    bool bIsCollision = p3dblock->Collision3DBlock(&Pos, &m_nOld3DEnemyPos, &m_n3DEnemyMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        m_bMoveSwitch = true;
                    }
                    //    if (m_n3DEnemyMove.z >= 0.1f && p3dblock->GetMoveBlock().z >= 0.1f || m_n3DEnemyMove.z <= 0.1f && p3dblock->GetMoveBlock().z <= -0.1f)
                    //    {
                    //        Pos.z += p3dblock->GetMoveBlock().z;
                    //    }


                    //    if (m_n3DEnemyMove.z >= 0.1f && p3dblock->GetMoveBlock().z <= -0.1f || m_n3DEnemyMove.z <= -0.1f && p3dblock->GetMoveBlock().z >= 0.1f)
                    //    {
                    //        Pos.z += (p3dblock->GetMoveBlock().z * 2);
                    //    }
                    //}

                }

            }
        }
    }

    //�ǃu���b�N�Ƃ̓����蔻��
    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        for (int nCntObj = 0; nCntObj < 200; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                if (type == CObject::TYPE::WALL_WIDTH)
                {
                    C3dwall* p3dwall = (C3dwall*)pObj;

                    bool bIsCollision = p3dwall->Collision3DWall(&Pos, &m_nOld3DEnemyPos, &m_n3DEnemyMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (m_n3DEnemyMove.z >= 0.1f && p3dwall->GetMoveBlock().z >= 0.1f || m_n3DEnemyMove.z <= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dwall->GetMoveBlock().z;
                        }

                        if (m_n3DEnemyMove.z >= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f || m_n3DEnemyMove.z <= -0.1f && p3dwall->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dwall->GetMoveBlock().z * 2);
                        }
                    }

                }

                if (type == CObject::TYPE::WALL_WIDTH_SHORT)
                {
                    C3dwall* p3dwall = (C3dwall*)pObj;

                    bool bIsCollision = p3dwall->Collision3DWallShort(&Pos, &m_nOld3DEnemyPos, &m_n3DEnemyMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (m_n3DEnemyMove.z >= 0.1f && p3dwall->GetMoveBlock().z >= 0.1f || m_n3DEnemyMove.z <= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dwall->GetMoveBlock().z;
                        }

                        if (m_n3DEnemyMove.z >= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f || m_n3DEnemyMove.z <= -0.1f && p3dwall->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dwall->GetMoveBlock().z * PLAYER_MOVE_BOOST);
                        }
                    }

                }

                if (type == CObject::TYPE::WALL_HEIGHT)
                {

                    C3dwall* p3dwall = (C3dwall*)pObj;


                    bool bIsCollision = p3dwall->Collision3DHeightWall(&Pos, &m_nOld3DEnemyPos, &m_n3DEnemyMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (m_n3DEnemyMove.z >= 0.1f && p3dwall->GetMoveBlock().z >= 0.1f || m_n3DEnemyMove.z <= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dwall->GetMoveBlock().z;
                        }


                        if (m_n3DEnemyMove.z >= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f || m_n3DEnemyMove.z <= -0.1f && p3dwall->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dwall->GetMoveBlock().z * 2);
                        }
                    }

                }


                if (type == CObject::TYPE::WALL_HEIGHT_SHORT)
                {
                    C3dwall* p3dwall = (C3dwall*)pObj;

                    bool bIsCollision = p3dwall->Collision3DHeightWallShort(&Pos, &m_nOld3DEnemyPos, &m_n3DEnemyMove, 50.0f, 50.0f);

                    if (bIsCollision == true)
                    {
                        if (m_n3DEnemyMove.z >= 0.1f && p3dwall->GetMoveBlock().z >= 0.1f || m_n3DEnemyMove.z <= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dwall->GetMoveBlock().z;
                        }

                        if (m_n3DEnemyMove.z >= 0.1f && p3dwall->GetMoveBlock().z <= -0.1f || m_n3DEnemyMove.z <= -0.1f && p3dwall->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dwall->GetMoveBlock().z * 2);
                        }
                    }

                }

            }
        }
    }

    int nFadeState = CFade::GetFadeState();

    if (nFadeState == CFade::FADE_OUT)
    {

        C3denemy::Uninit();
    }

    //���W��ݒ�
    SetPos(Pos);

    //X���W�̈ړ��ʂ��X�V
    m_n3DEnemyMove.x += (Length_value2 - m_n3DEnemyMove.x) * 0.18f;

    //Z���W�̈ړ��ʂ��X�V
    m_n3DEnemyMove.z += (Length_value2 - m_n3DEnemyMove.z) * 0.18f;


}

//======================
// �`�揈��
//======================
void C3denemy::Draw()
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
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

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

                //���f��(�p�[�c)�̕`��
                m_pMesh[nCntParts]->DrawSubset(nCntMat);
            }
        }

    }

    pDevice->SetMaterial(&matDef);
}

void C3denemy::EnemyDamage()
{
    m_nLife--;
}

//======================
// �I�u�W�F�N�g��������
//======================
C3denemy* C3denemy::Create(D3DXVECTOR3 pos,int MoveType)
{
    C3denemy* D3Dplayer = nullptr;

    D3Dplayer = new C3denemy;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3Dplayer->Init()))
    {
        if (MoveType == 0)
        {
            D3Dplayer->SetType(TYPE::ENEMY_NORMAL);
        }

        if (MoveType == 1)
        {
            D3Dplayer->SetType(TYPE::ENEMY_XMOVE);
        }

        if (MoveType == 2)
        {
            D3Dplayer->SetType(TYPE::ENEMY_ZMOVE);
        }

        if (MoveType == 3)
        {
            D3Dplayer->SetType(TYPE::ENEMY_XMOVE);
            D3Dplayer->m_nMoveInterval = MOVE_INTERVAL;
        }

        if (MoveType == 4)
        {
            D3Dplayer->SetType(TYPE::ENEMY_ZMOVE);
            D3Dplayer->m_nMoveInterval = MOVE_INTERVAL;
        }

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
HRESULT C3denemy::Load()
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
void C3denemy::Unload()
{
    CModel::Unload();
}



//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================
void C3denemy::LoadPlayerData(void)
{
    char Datacheck[MAX_CHAR];
    int nCntEnemyData = 0;
    int EnemyModelSave = 0;

    //m_pFile = fopen("data\\MODEL\\MODEL_golden_man\\motion.txt", "r");//�t�@�C�����J��
    m_pFile = fopen("data\\MODEL_Crystal\\motion_crs3.txt", "r");//�t�@�C�����J��

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