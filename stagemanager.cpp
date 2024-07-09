//=================================================
//
// ステージマネージャー処理 (texture.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "stagemanager.h"

#include "3denemy.h"
#include "3dbrokenblock.h"
#include "3dblock.h"
#include "startobj.h"
#include "3ditem.h"
#include "objectX.h"
#include "3dplayer.h"
#include "3dwall.h"
#include "billboard.h"

//======================
//コンストラクタ
//======================
CStageManager::CStageManager()
{

}

//======================
//デストラクタ
//======================
CStageManager::~CStageManager()
{

}

//======================
//初期化処理
//======================
HRESULT CStageManager::Init()
{
	return S_OK;
}

//======================
// 終了処理
//======================
void CStageManager::Uninit()
{

}

//======================
// 更新処理
//======================
void CStageManager::Update()
{

}

//======================
// 描画処理
//======================
void CStageManager::Draw()
{

}

//======================
// オブジェクト生成処理
//======================
CStageManager* CStageManager::Create()
{
    CStageManager* D3DStageManager = nullptr;

    D3DStageManager = new CStageManager;

    //初期化に成功した場合
    if (SUCCEEDED(D3DStageManager->Init()))
    {
        D3DStageManager->LoadStageData();
    }

    return D3DStageManager;
}

//======================
// ステージ配置情報読み込み処理
//======================
void CStageManager::LoadStageData()
{
    char Datacheck[MAX_CHAR];
    int nCntObjectData = 0;
    int CreateObjType[MAX_OBJ];
    int CreateObjType2[MAX_OBJ];

    m_pFile = fopen("data\\LOADSTAGE\\loadstage000.txt", "r");//ファイルを開く

    //ファイルが存在しない場合
    if (m_pFile == NULL)
    {
        return;
    }

    //外部ファイル文字列読み取り
    while (1)
    {
        fscanf(m_pFile, "%s", Datacheck);


            if (Datacheck[0] == '#')
            {
                continue;
            }

            if (!strcmp(Datacheck, "END_STAGESET"))
            {
                fclose(m_pFile);
                break;
            }

            if (!strcmp(Datacheck, "OBJECTSET"))
            {
                while (1)
                {
                    fscanf(m_pFile, "%s", Datacheck);

                    if (!strcmp(Datacheck, "END_OBJECTSET"))
                    {
                        break;
                    }

                    //生成するオブジェクトの種類
                    if (!strcmp(Datacheck, "OBJ_TYPE"))
                    {
                        fscanf(m_pFile, "%s", Datacheck);
                        fscanf(m_pFile, "%d", &CreateObjType[nCntObjectData]);
                    }

                    //オブジェクトの座標
                    if (!strcmp(Datacheck, "POS"))
                    {
                        fscanf(m_pFile, "%s", Datacheck);
                        fscanf(m_pFile, "%f", &m_nPos[nCntObjectData].x);
                        fscanf(m_pFile, "%f", &m_nPos[nCntObjectData].y);
                        fscanf(m_pFile, "%f", &m_nPos[nCntObjectData].z);
                    }

                    //オブジェクトの詳細設定 (一部のオブジェクトでしか使用しない)
                    if (!strcmp(Datacheck, "OBJ_TYPE2"))
                    {
                        fscanf(m_pFile, "%s", Datacheck);
                        fscanf(m_pFile, "%d", &CreateObjType2[nCntObjectData]);
                    }
                }

                nCntObjectData++;
            }

    }

    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    //上記で得た情報を代入
    for (int nCnt = 0; nCnt < nCntObjectData; nCnt++)
    {
        //プレイヤー生成の場合
        if (CreateObjType[nCnt] == 0)
        {
            C3dplayer::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z));
            C3dstartobj::Create();
        }

        //敵生成の場合
        if (CreateObjType[nCnt] == 1)
        {
            C3denemy::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z), CreateObjType2[nCnt]);
        }

        //ブロック生成の場合
        if (CreateObjType[nCnt] == 2)
        {
            C3dblock::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z));
        }

        //ブロック生成の場合
        if (CreateObjType[nCnt] == 3)
        {
            C3dbrokenblock::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z));
        }

        //アイテム生成の場合
        if (CreateObjType[nCnt] == 4)
        {
            C3ditem::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z), CreateObjType2[nCnt]);
        }

        //壁生成の場合
        if (CreateObjType[nCnt] == 5)
        {
            C3dwall::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z));
        }
    }
}
