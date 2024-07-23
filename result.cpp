//=================================================
//
// 2Dポリゴンの描画処理 (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "result.h"
#include "manager.h"

//======================
// コンストラクタ
//======================
CResultBG::CResultBG()
{

}

//======================
// デストラクタ
//======================
CResultBG::~CResultBG()
{

}

//======================
// 初期化処理
//======================
HRESULT CResultBG::Init()
{
	CObject2D::Init();

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nSize.x, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, m_nSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nSize.x, m_nSize.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	CObject2D::GetBuff()->Unlock();

	return S_OK;
}

//======================
// 終了処理
//======================
void CResultBG::Uninit()
{
	CObject2D::Uninit();
}

//======================
// 更新処理
//======================
void CResultBG::Update()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CResultBG::Uninit();
	}
}

//======================
// 描画処理
//======================
void CResultBG::Draw()
{
	CObject2D::Draw();
}

//======================
// オブジェクト生成処理
//======================
CResultBG* CResultBG::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CResultBG* ResultBG = new CResultBG;

	ResultBG->m_nPos = pos;

	ResultBG->m_nSize = size;

	ResultBG->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\result000.png", &pTexture);

	ResultBG->BindTexture(pTexture);

	return ResultBG;
}