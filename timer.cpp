//=================================================
//
// アイテムの処理 (timer.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "timer.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "block.h"

//============================
//コンストラクタ
//============================
CTimer::CTimer(int nPriority) : CObject2D(nPriority)
{
	m_nTime = 10;
	m_nTimerCnt = 0;
}

//============================
//デストラクタ
//============================
CTimer::~CTimer()
{

}

//============================
//アイテムの初期化処理
//============================
HRESULT CTimer::Init()
{
	//for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	//{
		//初期化
		CObject2D::Init();
	//}

	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{
		//頂点座標を設定
		pVtx[0].pos = D3DXVECTOR3(620.0f + (nCntTime * TEX_TIME_INTERVAL), 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(670.0f + (nCntTime * TEX_TIME_INTERVAL), 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(620.0f + (nCntTime * TEX_TIME_INTERVAL), 90.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(670.0f + (nCntTime * TEX_TIME_INTERVAL), 90.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	CObject2D::GetBuff()->Unlock();

	return S_OK;
}

//============================
//アイテムの初期化処理
//============================
void CTimer::Uninit()
{
	//初期化
	CObject2D::Uninit();
}

//============================
//アイテムの更新処理
//============================
void CTimer::Update()
{

	VERTEX_2D* pVtx;

	int aPosTexU[NUM_TIME];

	m_nTimerCnt++;

	if (m_nTimerCnt == MAX_TIMESPEED)
	{
		m_nTime--; //時間を1秒減らす
		m_nTimerCnt = 0; //フレームカウントリセット
	}

	// 時間の値をコピー
	int CopyTime = m_nTime;

	// 各桁の値を計算
	for (int nCntTime = NUM_TIME - 1; nCntTime >= 0; nCntTime--)
	{
		aPosTexU[nCntTime] = CopyTime % 10;
		CopyTime /= 10;
	}



	//頂点バッファをロックし、頂点情報へのポインタを取得
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 1.0f);

		if (m_nTime > 80)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 252, 219, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 252, 219, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 252, 219, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 252, 219, 255);
		}

		else if (m_nTime > 20 < 80)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (m_nTime < 20)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		}
	}

	//頂点バッファをアンロックする
	CObject2D::GetBuff()->Unlock();

	if (m_nTime < 0)
	{
		m_nTime = 0;
		Uninit();
		CManager::SetMode(CScene::MODE_TITLE);
	}

}

//============================
//アイテムの描画処理
//============================
void CTimer::Draw()

{	//テクスチャ座標の更新
	CObject2D::Draw();
}

//============================
//アイテムの生成処理
//============================
CTimer* CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTimer* pTimer;

	pTimer = new CTimer;

	pTimer->SetType(TYPE::TIMER);
	pTimer->CObject2D::SetPos(pos);
	pTimer->m_rot = rot;

	//アイテムの初期化
	pTimer->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//テクスチャの読み込む
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\SCORE_NUMBER.png", &pTexture);

	//テクスチャの設定
	pTimer->BindTexture(pTexture);

	return pTimer;
}