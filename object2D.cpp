#include "object2D.h"
#


CObject2D::CObject2D()
{

}

CObject2D::~CObject2D()
{

}

HRESULT CObject2D::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_OBJECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\runningman000.png", &m_pTexBuff);

	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(m_nPos.x - m_nSize.x, m_nPos.y - m_nSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x, m_nPos.y - m_nSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nPos.x - m_nSize.x, m_nPos.y + m_nSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x, m_nPos.y + m_nSize.y, 0.0f);

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

	m_pVtxBuff->Unlock();

	return S_OK;
}

void CObject2D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexBuff != nullptr)
	{
		m_pTexBuff->Release();
		m_pTexBuff = nullptr;
	}
}

void CObject2D::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    // アニメーションフレームの更新
	m_Frametimer += m_FrameDuration;
    if (m_Frametimer >= m_FrameDuration)
    {
        // 次のフレームに進める
		m_CurrentFrame = (m_CurrentFrame + 1) % m_Numframes;

        // フレームの経過時間をリセット
		m_Frametimer = 0.0f;

        // テクスチャ座標の更新
        VERTEX_2D* pVtx;
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
        pVtx[0].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 0.0f);
        pVtx[1].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 0.0f);
        pVtx[2].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 1.0f);
        pVtx[3].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 1.0f);

		m_pVtxBuff->Unlock();
    }


	//if (CObject2D::AnimationPTN > IMAGE_PATTERN_ANIM)
	//{
	//	CObject2D::AnimationPTN = 0;
	//}

}

void CObject2D::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTexBuff);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CObject2D* Object2D = new CObject2D;

	Object2D->m_nPos = pos;

	Object2D->m_nSize = size;

	Object2D->Init();

	return Object2D;
}