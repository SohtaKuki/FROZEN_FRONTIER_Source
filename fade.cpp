//=================================================
//
// フェード処理 (fade.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "fade.h"
#include "manager.h"
#include "object.h"


CScene::MODE CFade::m_Mode = CScene::MODE_TITLE;
bool CFade::m_bEndFade = false;					
CFade::FADE CFade::m_FadeState = CFade::FADE_NONE;

//============================
//コンストラクタ
//============================
CFade::CFade()
{
	m_pVtxBuff = nullptr;			
	m_Mode = CScene::MODE_TITLE;	
	m_bEndFade = true;				
	m_FadeState = CFade::FADE_NONE;	
}

//============================
//デストラクタ
//============================
CFade::~CFade()
{

}

//============================
//初期化処理
//============================
HRESULT CFade::Init()
{
	m_fAlpha = 1.0f;

	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(CObject::VERTEX_2D) * 4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_pVtxBuff,NULL);

	CObject::VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	SetFade(CScene::MODE::MODE_TITLE);

	return S_OK;
}

//============================
//終了処理
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
//更新処理
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

			if (m_fAlpha <= 1.0f)
			{
				m_fAlpha += 1.0f / (float)FADE_TIME;

				SetAlpha(m_fAlpha);

				if (m_fAlpha >= 1.0f)
				{
					//最大値に補正
					m_fAlpha = 1.0f;

					CManager::SetMode(m_Mode);

					m_FadeState = FADE_IN;

				}
			}

			break;

		case FADE_IN:

			if (m_fAlpha >= 0.0f)
			{

				m_fAlpha -= 1.0f / (float)FADE_TIME;

				SetAlpha(m_fAlpha);

				if (m_fAlpha <= 0.0f)
				{
					m_fAlpha = 0.0f;

					m_FadeState = FADE_NONE;
					m_bEndFade = true;
				}
			}
			break;
		}
	}
}


void CFade::SetAlpha(float fAlpha)
{
	CObject::VERTEX_2D* pVtx; 

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fAlpha);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fAlpha);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fAlpha);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fAlpha);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//描画処理
//============================
void CFade::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject::VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, NULL);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//============================
//フェードの設定処理
//============================
void CFade::SetFade(CScene::MODE mode)
{
	m_bEndFade = false;
	m_FadeState = FADE_OUT;

	m_Mode = mode;
}