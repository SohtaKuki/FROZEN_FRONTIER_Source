//=================================================
//
// フェード処理 (fade.cpp)
// Author: Sohta Kuki
//
//=================================================


#include "fade.h"
#include "manager.h"
#include "object.h"

//静的メンバの初期化
CScene::MODE CFade::m_Mode = CScene::MODE_TITLE;
bool CFade::m_bEndFade = false;					
CFade::FADE CFade::m_FadeState = CFade::FADE_NONE;

//============================
//フェードのコンストラクタ
//============================
CFade::CFade()
{
	//メンバ変数の初期化
	m_pVtxBuff = nullptr;			
	m_Mode = CScene::MODE_TITLE;	
	m_bEndFade = true;				
	m_FadeState = CFade::FADE_NONE;	
}

//============================
//フェードのデストラクタ
//============================
CFade::~CFade()
{

}

//============================
//フェードの初期化
//============================
HRESULT CFade::Init()
{

	m_fAlpha = 1.0f;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(CObject::VERTEX_2D) * 4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_pVtxBuff,NULL);

	CObject::VERTEX_2D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = SCREEN_WIDTH;
	pVtx[3].pos.y = SCREEN_HEIGHT;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//最初のシーンの設定
	SetFade(CScene::MODE_TITLE);

	return S_OK;
}

//============================
//フェードの終了処理
//============================
void CFade::Uninit()
{
	//使用していたら破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================
//フェードの更新処理
//============================
void CFade::Update()
{
	
	if (!m_bEndFade)
	{
		switch (m_FadeState)
		{
		case FADE_NONE:	//何もなし
			break;

		case FADE_OUT:	//フェードアウト

			//透明度が最大じゃないなら
			if (m_fAlpha <= 1.0f)
			{
				m_fAlpha += 1.0f / (float)FADE_TIME;

				SetAlpha(m_fAlpha);

				if (m_fAlpha >= 1.0f)
				{
					//最大値に補正
					m_fAlpha = 1.0f;

					//CManager::SetScene(m_Mode);

					//フェードインの処理に移る
					m_FadeState = FADE_IN;

				}
			}

			break;

		case FADE_IN:

			//透明度が0.0fじゃないなら
			if (m_fAlpha >= 0.0f)
			{
				//α値を増加
				m_fAlpha -= 1.0f / (float)FADE_TIME;

				//α値の設定
				SetAlpha(m_fAlpha);

				//透明度が0.0f以下になったら
				if (m_fAlpha <= 0.0f)
				{
					//最小値に補正
					m_fAlpha = 0.0f;

					//フェードインの処理に移る
					m_FadeState = FADE_NONE;
					m_bEndFade = true;	//処理が終わった判定に
				}
			}
			break;
		}
	}
}

void CFade::SetAlpha(float falpha)
{
	CObject::VERTEX_2D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//フェードの描画処理
//============================
void CFade::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject::VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}


void CFade::SetFade(CScene::MODE mode)
{
	m_bEndFade = false;
	m_FadeState = FADE_OUT;

	//モードを設定
	m_Mode = mode;
}