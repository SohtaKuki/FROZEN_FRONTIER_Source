//=================================================
//
// 3Dモデルのプレイヤーの表示処理 (3dplayer.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dblock.h"
#include "player.h"
#include "block.h"
#include "startobj.h"
#include "3ditem.h"
#include "3dbullet.h"
#include "3dchargebullet.h"
#include "3denemy.h"
#include "3dbrokenblock.h"

LPDIRECT3DTEXTURE9 C3dplayer::m_pTexBuff = nullptr;
int C3dplayer::m_nLife = 0;

//======================
// コンストラクタ
//======================
C3dplayer::C3dplayer(int nPriority) : CModel(nPriority)
{
    m_bPlayerBuff = false;
    m_bInstantShot = false;
    m_nBuffTime = 0;
    m_nInstantShotTime = 0;
    m_nLife = 12;
    m_bAButtonPressStartTime = false;
    m_bAButtonPressed = 0;
}

//======================
// デストラクタ
//======================
C3dplayer::~C3dplayer()
{

}

//======================
// 初期化処理
//======================
HRESULT C3dplayer::Init()
{
    //初期化
    if (FAILED(CModel::Init()))
    {
        return E_FAIL;
    }

    return S_OK;
}

//======================
// 終了処理
//======================
void C3dplayer::Uninit()
{
    CModel::Uninit();
}

//======================
// 更新処理
//======================
void C3dplayer::Update()
{
    D3DXVECTOR3 Pos = CObject3D::GetPos();

    //SetPlayerPos();

    int nCnt = 0;

    //プレイヤーのHPが0以上の場合のみ通す
    if (m_nLife > 0)
    {
        if (CManager::GetKeyboard()->GetPress(DIK_D))
        {
            if (m_bPlayerBuff == false)
            {
                m_n3DPlayerMove.x += 1.0f;
                m_rot.y = D3DX_PI * -0.5f;
            }

            if (m_bPlayerBuff == true)
            {
                m_n3DPlayerMove.x += 1.0f * 2.0;
                m_rot.y = D3DX_PI * -0.5f;
            }
        }

        if (CManager::GetKeyboard()->GetPress(DIK_A))
        {
            if (m_bPlayerBuff == false)
            {
                m_n3DPlayerMove.x -= 1.0f;
                m_rot.y = D3DX_PI * 0.5f;
            }

            if (m_bPlayerBuff == true)
            {
                m_n3DPlayerMove.x -= 1.0f * 2.0;
                m_rot.y = D3DX_PI * 0.5f;
            }
        }

        if (CManager::GetKeyboard()->GetPress(DIK_W))
        {
            if (m_bPlayerBuff == false)
            {
                m_n3DPlayerMove.z += 1.0f;
                m_rot.y = D3DX_PI;
            }

            if (m_bPlayerBuff == true)
            {
                m_n3DPlayerMove.z += 1.0f * 2.0f;
                m_rot.y = D3DX_PI;
            }
        }

        if (CManager::GetKeyboard()->GetPress(DIK_S))
        {
            if (m_bPlayerBuff == false)
            {
                m_n3DPlayerMove.z -= 1.0f;
                m_rot.y = -D3DX_PI * -0.0f;
            }

            if (m_bPlayerBuff == true)
            {
                m_n3DPlayerMove.z -= 1.0f * 2.0f;
                m_rot.y = D3DX_PI * -0.0f;
            }
        }
    }

    //球発射
    if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
    {
        //チャージショット即発射バフが有効の場合は通さない
        if (m_bInstantShot == false)
        {
            C3dbullet::Create(Pos, D3DXVECTOR3(10.0f, 10.0f, 0.0f), m_rot,0);
        }
    }

    // スペースキーが押されたとき (長押し発射)
    if (CManager::GetKeyboard()->GetPress(DIK_SPACE))
    {
        // スペースキーがまだ押されていない場合
        if (!m_bAButtonPressed)
        {
            m_bAButtonPressed = true;
            m_bAButtonPressStartTime = GetTickCount64(); // タイムスタンプを記録
        }
        //スペースキーを2秒以上長押ししている場合
        else if (CManager::GetKeyboard()->GetPress(DIK_SPACE) == true && (GetTickCount64() - m_bAButtonPressStartTime >= 2000 - 1000))
        {

        }
    }
    else
    {
        // スペースキーが離された場合かつ長押し時間が2秒以上の場合
        if (m_bAButtonPressed && (GetTickCount64() - m_bAButtonPressStartTime >= 2000))
        {
            //チャージショット即発射バフが有効の場合は通さない
            if (m_bInstantShot == false)
            {
                // 玉の発射を実行
                C3dchargebullet::Create(Pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), m_rot);
            }

        }
        // Jキーのフラグをリセット
        m_bAButtonPressed = false;




    }

    //球発射
    if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
    {
        //チャージショット即発射バフが有効の場合は通さない
        if (m_bInstantShot == true)
        {
            C3dchargebullet::Create(Pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), m_rot);
        }
    }



    //プレイヤーのHPを減らす
    if (CManager::GetKeyboard()->GetTrigger(DIK_K))
    {
        m_nLife -= 1;
    }

    if (m_nLife == 0)
    {
        Uninit();
        CManager::GetFade()->SetFade(CScene::MODE_RESULT);
    }

    //過去座標を保存
    m_nOld3DPlayerPos = Pos;

    Pos.x += m_n3DPlayerMove.x;
    Pos.z += m_n3DPlayerMove.z;

    //バフアイテムの当たり判定
    for (int nCntObj = 0; nCntObj < C3ditem::MAX_ITEM; nCntObj++)
    {
        CObject* pObj = CObject::GetObj(3, nCntObj);

        if (pObj != nullptr)
        {
            CObject::TYPE type = pObj->GetType();

            C3ditem * p3dItem = (C3ditem*)pObj;

            D3DXVECTOR3 EnemyPos = p3dItem->GetPos();

            //プレイヤー移動速度上昇アイテムの場合
            if (type == CObject::TYPE::ITEM_WALKSPDUP)
            {
                if (CObject3D::GetPos().x >= EnemyPos.x - 50
                    && CObject3D::GetPos().x <= EnemyPos.x + 50
                    && CObject3D::GetPos().z >= EnemyPos.z - 50
                    && CObject3D::GetPos().z <= EnemyPos.z + 50)
                {
                    m_bPlayerBuff = true;
                    p3dItem->Uninit();
                    return;
                }
            }

            //チャージショット即発射バフアイテムの場合
            if (type == CObject::TYPE::ITEM_INSTANTSHOT)
            {
                if (CObject3D::GetPos().x >= EnemyPos.x - 50
                    && CObject3D::GetPos().x <= EnemyPos.x + 50
                    && CObject3D::GetPos().z >= EnemyPos.z - 50
                    && CObject3D::GetPos().z <= EnemyPos.z + 50)
                {
                    m_bInstantShot = true;
                    p3dItem->Uninit();
                    return;
                }
            }
        }
    }


    //プレイヤー移動速度上昇強化がtrueの場合
    if (m_bPlayerBuff == true)
    {
        m_nBuffTime++;

        //10秒たったらfalseにする
        if (m_nBuffTime == 600)
        {
            m_bPlayerBuff = false;
            m_nBuffTime = 0;
        }
    }

    //チャージショット即発射バフがtrueの場合
    if (m_bInstantShot == true)
    {
        m_nInstantShotTime++;

        //6秒たったらfalseにする
        if (m_nInstantShotTime == 360)
        {
            m_bInstantShot = false;
            m_nInstantShotTime = 0;
        }
    }

    //ブロックとの当たり判定の補正
    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        for (int nCntObj = 0; nCntObj < C3dblock::MAX_BLOCK; nCntObj++)
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
                        if (m_n3DPlayerMove.z >= 0.1f && p3dblock->GetMoveBlock().z >= 0.1f || m_n3DPlayerMove.z <= 0.1f && p3dblock->GetMoveBlock().z <= -0.1f)
                        {
                            Pos.z += p3dblock->GetMoveBlock().z;
                        }

                        if (m_n3DPlayerMove.z >= 0.1f && p3dblock->GetMoveBlock().z <= -0.1f || m_n3DPlayerMove.z <= -0.1f && p3dblock->GetMoveBlock().z >= 0.1f)
                        {
                            Pos.z += (p3dblock->GetMoveBlock().z * 2);
                        }
                    }

                }

            }
        }
    }

    //破壊可能ブロックとの当たり判定
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
                            Pos.z += (p3dbrokenblock->GetMoveBlock().z * 2);
                        }
                    }

                }

            }
        }
    }

    //座標を設定
    SetPos(Pos);

    //X座標の移動量を更新
    m_n3DPlayerMove.x += (Length_value2 - m_n3DPlayerMove.x) * Attenuation_value;

    //Z座標の移動量を更新
    m_n3DPlayerMove.z += (Length_value2 - m_n3DPlayerMove.z) * Attenuation_value;

 
}

//======================
// 描画処理
//======================
void C3dplayer::Draw()
{
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
    D3DMATERIAL9 matDef; //現在のマテリアル保存用
    D3DXMATERIAL* pMat; //マテリアルデータへのポインタ
    D3DXVECTOR3 Pos = CObject3D::GetPos();

    //ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxworld);

    //向きを反映
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

    //位置を反映
    D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld , &mtxTrans);

    ////モデルの影の設定
    //D3DXMATRIX mtxshadow , mtxshadowTrans;
    //D3DXPLANE plane;
    //D3DXVECTOR4 vecLight;
    //D3DXVECTOR3 pos, nor;

    //D3DXMatrixIdentity(&mtxshadow);

    ////ライトの逆方向ベクトルを設定
    //vecLight = D3DXVECTOR4(0.5f, 0.6f, 0.7f,1.0f);
    //pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
    //nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

    //D3DXPlaneFromPointNormal(&plane, &pos, &nor);
    //D3DXMatrixShadow(&mtxshadow,&vecLight,&plane);

    //m_mtxworld * mtxshadow;

    //ワールドマトリックスの設定
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

    //マテリアルを取得
    pDevice->GetMaterial(&matDef);

    for (int nCntParts = 0; nCntParts < NUM_MODEL; nCntParts++)
    {
        //ワールドマトリックスの初期化
        D3DXMatrixIdentity(&m_aModel[nCntParts].mtxworld);

        //向きを反映
        D3DXMatrixRotationYawPitchRoll(&mtxRot, m_aModel[nCntParts].rot.y, m_aModel[nCntParts].rot.x, m_aModel[nCntParts].rot.z);
        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxRot);

        //位置を反映
        D3DXMatrixTranslation(&mtxTrans, m_aModel[nCntParts].pos.x, m_aModel[nCntParts].pos.y, m_aModel[nCntParts].pos.z);
        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxTrans);

        //親子関係
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
            //マトリックスの設定
            pDevice->SetTransform(D3DTS_WORLD, &m_aModel[nCntParts].mtxworld);

            pMat = (D3DXMATERIAL*)m_pBuffMat[nCntParts]->GetBufferPointer();


            for (int nCntMat = 0; nCntMat < (int)m_nNumMat[nCntParts]; nCntMat++)
            {
                //マテリアルの設定
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                //テクスチャの設定
                pDevice->SetTexture(0, m_pTexBuff);

                //テクスチャが存在する
                if (pMat[nCntMat].pTextureFilename != NULL)
                {
                    //テクスチャの設定
                    pDevice->SetTexture(0,&m_aModel[0].m_pTexture[nCntMat]);
                }

                else
                {
                    //テクスチャの設定
                    pDevice->SetTexture(0, NULL);
                }

                if (m_nLife > 0)
                {
                    //モデル(パーツ)の描画
                    m_pMesh[nCntParts]->DrawSubset(nCntMat);
                }

            }
        }

    }

    pDevice->SetMaterial(&matDef);
}

//======================
// オブジェクト生成処理
//======================
C3dplayer* C3dplayer::Create(D3DXVECTOR3 pos)
{
    C3dplayer* D3Dplayer = nullptr;

    D3Dplayer = new C3dplayer;

    //初期化に成功した場合
    if (SUCCEEDED(D3Dplayer->Init()))
    {
        D3Dplayer->SetType(TYPE::PLAYER);

        D3Dplayer->LoadPlayerData();

        D3Dplayer->CObject3D::SetPos(pos);

        //D3Dplayer->Load();//テクスチャを設定(仮)


        ////テクスチャの設定
        //Model->BindTexture(m_pTexBuff);
    }

    return D3Dplayer;
}

//======================
// テクスチャロード処理
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
// テクスチャアンロード(終了)処理
//======================
void C3dplayer::Unload()
{
    CModel::Unload();
}

void C3dplayer::PlayerDamage()
{
    m_nLife -= 1;
}

//===========================
// 外部ファイル読み込み処理
//===========================
void C3dplayer::LoadPlayerData(void)
{
    char Datacheck[MAX_CHAR];
    int nCntEnemyData = 0;
    int EnemyModelSave = 0;

    //m_pFile = fopen("data\\MODEL\\MODEL_golden_man\\motion.txt", "r");//ファイルを開く
    m_pFile = fopen("data\\MODEL\\MODEL_SLIME\\motion.txt", "r");//ファイルを開く

    //ファイルが存在しない場合
    if (m_pFile == NULL)
    {
        return;
    }

    //外部ファイル文字列読み取り
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

        //パーツ数
        if (!strcmp(Datacheck, "NUM_PARTS"))
        {
            fscanf(m_pFile, "%s", Datacheck);
            fscanf(m_pFile, "%d", &EnemyModelSave);
        }

        //ファイル名
        if (!strcmp(Datacheck, "MODEL_FILENAME"))
        {
            fscanf(m_pFile, "%s", Datacheck);
            fscanf(m_pFile, "%s", &CModel::m_aLoadEnemy[EnemyModelSave].filename[0]);
            EnemyModelSave++;
        }

        //パーツの詳細
        if (!strcmp(Datacheck, "PARTSSET"))
        {
            while (1)
            {
                fscanf(m_pFile, "%s", Datacheck);

                //パーツ詳細終わり検知
                if (!strcmp(Datacheck, "END_PARTSSET"))
                {
                    break;
                }

                //インデックス
                else if (!strcmp(Datacheck, "INDEX"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%d", &CModel::m_aLoadEnemy[nCntEnemyData].index);
                }

                //親設定
                else if (!strcmp(Datacheck, "PARENT"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%d", &CModel::m_aLoadEnemy[nCntEnemyData].parent);
                }

                //立ち位置
                else if (!strcmp(Datacheck, "POS"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].pos.x);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].pos.y);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].pos.z);
                }

                //向き
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

    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    //ここで上記の処理で得た数値を代入
    for (int nCnt = 0; nCnt < EnemyModelSave; nCnt++)
    {
        D3DXLoadMeshFromX(&CModel::m_aLoadEnemy[nCnt].filename[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[nCnt], NULL, &m_nNumMat[nCnt], &m_pMesh[nCnt]);
        //D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\golden000.jpg", &m_pTexture);
        m_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_aModel[nCnt].nLife = 4;
        m_aModel[nCnt].nIdxModelParent = CModel::m_aLoadEnemy[nCnt].parent;
        m_aModel[nCnt].bUse = true;

        //敵の立ち位置初期化
        //m_nPos = D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
        //m_aEnemy.rot = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);

        m_aModel[nCnt].pos = D3DXVECTOR3(CModel::m_aLoadEnemy[nCnt].pos.x, CModel::m_aLoadEnemy[nCnt].pos.y, CModel::m_aLoadEnemy[nCnt].pos.z);
        m_aModel[nCnt].rot = D3DXVECTOR3(CModel::m_aLoadEnemy[nCnt].rot.x, CModel::m_aLoadEnemy[nCnt].rot.y, CModel::m_aLoadEnemy[nCnt].rot.z);
    }
}