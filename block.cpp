//=================================================
//
// 2Dポリゴンの描画処理 (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "block.h"
#include "bullet.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CBlock::m_pTexTemp = nullptr;

//======================
// コンストラクタ
//======================
CBlock::CBlock(int nPriority) : CObject2D(nPriority)
{
	m_nLife = 4;
	m_PolygonMoveSpeed = 1.0f;

}
//======================
// デストラクタ
//======================
CBlock::~CBlock()
{

}

//======================
// 初期化処理
//======================
HRESULT CBlock::Init()
{
	//初期化
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
// 終了処理
//======================
void CBlock::Uninit()
{
	Unload();
	CObject2D::Uninit();
}

//======================
// 更新処理
//======================
void CBlock::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロック
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_nBlockPos.x - m_nBlockSize.x, m_nBlockPos.y - m_nBlockSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nBlockPos.x + m_nBlockSize.x, m_nBlockPos.y - m_nBlockSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nBlockPos.x - m_nBlockSize.x, m_nBlockPos.y + m_nBlockSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nBlockPos.x + m_nBlockSize.x, m_nBlockPos.y + m_nBlockSize.y, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_nBlockPos.x += m_moveBlock.x;
	m_nBlockPos.y += m_moveBlock.y;

	//移動量を更新
	m_moveBlock.x += (Length_value2 - m_moveBlock.x) * Attenuation_value;
	m_moveBlock.y += (Length_value2 - m_moveBlock.y) * Attenuation_value;

}

//======================
// 描画処理
//======================
void CBlock::Draw()
{
	CObject2D::Draw();
}

//======================
// オブジェクト生成処理
//======================
CBlock* CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBlock* enemy = nullptr;

	enemy = new CBlock;

	if (SUCCEEDED(enemy->Init()))
	{
		enemy->SetType(TYPE::BLOCK);

		enemy->Load();

		enemy->m_nBlockPos = pos;

		enemy->m_nBlockSize = size;

		//テクスチャの設定
		enemy->BindTexture(m_pTexTemp);
	}

	return enemy;
}

//======================
// ダメージ処理
//======================
void CBlock::Damage()
{
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject* pObj = CObject::GetObj(3, nCntObj);

		if (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();
			if (type == CObject::TYPE::ENEMY)
			{
				m_nLife -= 1;

				VERTEX_2D* pVtx;

				CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				pVtx += 4;

				CObject2D::GetBuff()->Unlock();
			}

			if (m_nLife == 0)
			{
				CObject2D::Uninit();
				CObject::Release();
			}
		}
	}
}

//======================
// テクスチャロード処理
//======================
HRESULT CBlock::Load()
{
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block003.png", &m_pTexTemp)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
// テクスチャアンロード(終了)処理
//======================
void CBlock::Unload()
{
	if (m_pTexTemp != nullptr)
	{
		m_pTexTemp->Release();
		m_pTexTemp = nullptr;
	}
}

void CBlock::SetPos(D3DXVECTOR3 pos)
{
	CBlock* enemy = nullptr;
}
