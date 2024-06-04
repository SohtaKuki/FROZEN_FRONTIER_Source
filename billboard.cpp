#include "billboard.h"

//======================
// コンストラクタ
//======================
CBillboard::CBillboard(int nPriority) : CObject3D(nPriority)
{

}

//======================
// デストラクタ
//======================
CBillboard::~CBillboard()
{

}

//======================
// 初期化処理
//======================
HRESULT CBillboard::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	for (int nCnt = 0; nCnt < MAX_BIL; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			m_apBillboard[nCnt]->m_nPos = D3DXVECTOR3(37.0f, 55.0f, -10.0f);
			break;
		case 1:
			m_apBillboard[nCnt]->m_nPos = D3DXVECTOR3(57.0f, 50.0f, -17.0f);
			break;
		case 2:
			m_apBillboard[nCnt]->m_nPos = D3DXVECTOR3(50.0f, 65.0f, -69.0f);
			break;
		}
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\billboard000.png", &m_pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 1, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, -5.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================
//終了処理
//======================
void CBillboard::Uninit()
{
	CBillboard::Uninit();
}

//======================
//終了処理
//======================
void CBillboard::Update()
{

}

//======================
// 描画処理
//======================
void CBillboard::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	D3DXMATRIX mtxTrans;	//計算用マトリックス

	//ビューマトリックス取得
	D3DXMATRIX mtxView;

	////ライトを無効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//=========================
	// 壁めり込み防止コード
	//=========================

	////Zの比較方法変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	////Zバッファに書き込まない
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_BIL; nCnt++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_apBillboard[nCnt]->m_mtxWorld);

		//ビューマトリックス取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラの正面に向け続ける
		D3DXMatrixInverse(&m_apBillboard[nCnt]->m_mtxWorld, NULL, &mtxView);	//逆行列を求める

		m_apBillboard[nCnt]->m_mtxWorld._41 = 0.0f;
		m_apBillboard[nCnt]->m_mtxWorld._42 = 0.0f;
		m_apBillboard[nCnt]->m_mtxWorld._43 = 0.0f;

		D3DXMatrixTranslation(&mtxTrans, m_apBillboard[nCnt]->m_nPos.x, m_apBillboard[nCnt]->m_nPos.y, m_apBillboard[nCnt]->m_nPos.z);

		D3DXMatrixMultiply(&m_apBillboard[nCnt]->m_mtxWorld, &m_apBillboard[nCnt]->m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_apBillboard[nCnt]->m_mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		//ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 0, 2);
	}

	//アルファテストを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	//=========================
	// 壁めり込み防止コード
	//=========================

	////Zの比較方法変更
	//pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

	////Zバッファに書き込む
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////ライトを無効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//======================
// オブジェクト生成処理
//======================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBillboard* Billboard = new CBillboard;

	//初期化に成功した場合
	if (SUCCEEDED(Billboard->Init()))
	{
		//Billboard->Load();

		//Billboard->m_nPos = pos;

		//Billboard->m_nSize = size;
	}

	return Billboard;
}