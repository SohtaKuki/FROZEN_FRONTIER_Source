//=================================================
//
// 3D���f���̃u���b�N�̕\������ (3dwall.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dwall.h"
#include "3dplayer.h"

LPDIRECT3DTEXTURE9 C3dwall::m_pTexBuff = nullptr;

//======================
// �R���X�g���N�^
//======================
C3dwall::C3dwall(int nPriority) : CModel(nPriority)
{

}

//======================
// �f�X�g���N�^
//======================
C3dwall::~C3dwall()
{

}

//======================
// ����������
//======================
HRESULT C3dwall::Init()
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
void C3dwall::Uninit()
{
    CModel::Uninit();
}

//======================
// �X�V����
//======================
void C3dwall::Update()
{

}

//======================
// �`�揈��
//======================
void C3dwall::Draw()
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

//======================
// �I�u�W�F�N�g��������
//======================
C3dwall* C3dwall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType)
{
    C3dwall* D3DWall = nullptr;

    D3DWall = new C3dwall;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3DWall->Init()))
    {
        if (nType == 0)
        {
            D3DWall->SetType(TYPE::WALL_WIDTH);
        }

        if (nType == 1)
        {
            D3DWall->SetType(TYPE::WALL_HEIGHT);
        }

        D3DWall->LoadWallData();

        //D3DWall->Load();//�e�N�X�`����ݒ�(��)

        D3DWall->CObject3D::SetPos(pos);

        D3DWall->m_rot = rot;

        ////�e�N�X�`���̐ݒ�
        //Model->BindTexture(m_pTexBuff);
    }

    return D3DWall;
}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT C3dwall::Load()
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
void C3dwall::Unload()
{
    CModel::Unload();
}



//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================
void C3dwall::LoadWallData(void)
{
    char Datacheck[MAX_CHAR];
    int nCntEnemyData = 0;
    int EnemyModelSave = 0;

    if (GetType() == TYPE::WALL_WIDTH)
    {
        m_pFile = fopen("data\\MODEL\\MODEL_Wall\\icewall_profile.txt", "r");//�t�@�C�����J��
    }

    if (GetType() == TYPE::WALL_HEIGHT)
    {
        m_pFile = fopen("data\\MODEL\\MODEL_Wall\\icewall_profile_yrot.txt", "r");//�t�@�C�����J��
    }

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
        //D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\golden000.jpg", &g_pTextureEnemy);
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

//===========================
// �u���b�N�̓����蔻��
//===========================
bool C3dwall::Collision3DWall(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
    if (GetType() == TYPE::WALL_WIDTH)
    {
        bool bLanding = false; //�d�͂�K�������ꍇ�̂ݎg�p
        float fBlockWidth = 85.0f;
        float fBlockDepth = 0.0f;

        D3DXVECTOR3 Pos = CObject3D::GetPos();


        //�E�������蔻��
        if (pPos->x - fWidth <= Pos.x + fBlockWidth && pPosOld->x - fWidth >= Pos.x + fBlockWidth && pPos->z - fHeight < Pos.z + fBlockDepth - 20.0f && pPos->z  > Pos.z - fBlockDepth - 20.0f)
        {
            pPos->x = Pos.x + fBlockWidth + fWidth;
        }

        //���������蔻��
        else if (pPos->x + fWidth >= Pos.x - fBlockWidth && pPosOld->x + fWidth <= Pos.x - fBlockWidth && pPos->z - fHeight < Pos.z + fBlockDepth - 20.0f && pPos->z > Pos.z - fBlockDepth - 20.0f)
        {
            pPos->x = Pos.x - fBlockWidth - fWidth;
        }

        //�㑤�����蔻��
        if (pPos->x - fWidth < Pos.x + fBlockWidth && pPos->x + fWidth > Pos.x - fBlockWidth && pPos->z - fHeight <= Pos.z + fBlockDepth - 20.0f && pPosOld->z - fHeight >= Pos.z + fBlockDepth - 20.0f)
        {
            pPos->z = Pos.z + fBlockDepth - 20.0f + fHeight;
        }

        //���������蔻��
        else if (pPos->x - fWidth < Pos.x + fBlockWidth && pPos->x + fWidth > Pos.x - fBlockWidth && pPos->z >= Pos.z - fBlockDepth - 20.0f && pPosOld->z <= Pos.z - fBlockDepth - 20.0f)
        {
            pPos->z = Pos.z - fBlockDepth - 20.0f;

        }

        return bLanding;
    }
}

//===========================
// �u���b�N�̓����蔻��
//===========================
bool C3dwall::Collision3DHeightWall(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
    if (GetType() == TYPE::WALL_HEIGHT)
    {
        bool bLanding = false; //�d�͂�K�������ꍇ�̂ݎg�p
        float fBlockWidth = -20.0f;
        float fBlockDepth = 105.0f;

        D3DXVECTOR3 Pos = CObject3D::GetPos();


        //�E�������蔻��
        if (pPos->x - fWidth <= Pos.x + fBlockWidth && pPosOld->x - fWidth >= Pos.x + fBlockWidth && pPos->z - fHeight < Pos.z + fBlockDepth - 20.0f && pPos->z  > Pos.z - fBlockDepth - 20.0f)
        {
            pPos->x = Pos.x + fBlockWidth + fWidth;
        }

        //���������蔻��
        else if (pPos->x + fWidth >= Pos.x - fBlockWidth && pPosOld->x + fWidth <= Pos.x - fBlockWidth && pPos->z - fHeight < Pos.z + fBlockDepth - 20.0f && pPos->z > Pos.z - fBlockDepth - 20.0f)
        {
            pPos->x = Pos.x - fBlockWidth - fWidth;
        }

        //�㑤�����蔻��
        if (pPos->x - fWidth < Pos.x + fBlockWidth && pPos->x + fWidth > Pos.x - fBlockWidth && pPos->z - fHeight <= Pos.z + fBlockDepth - 20.0f && pPosOld->z - fHeight >= Pos.z + fBlockDepth - 20.0f)
        {
            pPos->z = Pos.z + fBlockDepth - 20.0f + fHeight;
        }

        //���������蔻��
        else if (pPos->x - fWidth < Pos.x + fBlockWidth && pPos->x + fWidth > Pos.x - fBlockWidth && pPos->z >= Pos.z - fBlockDepth - 20.0f && pPosOld->z <= Pos.z - fBlockDepth - 20.0f)
        {
            pPos->z = Pos.z - fBlockDepth - 20.0f;

        }

        return bLanding;
    }
}