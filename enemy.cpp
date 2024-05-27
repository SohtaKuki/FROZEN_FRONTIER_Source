//=================================================
//
// 2Dポリゴンの描画処理 (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "enemy.h"
#include "bullet.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CEnemy::m_pTexTemp = nullptr;

//======================
// コンストラクタ
//======================
CEnemy::CEnemy()
{
	m_PolygonMoveSpeed = 1.0f;
	m_PolygonPosX = 500.0f;
	m_PolygonPosY = 200.0f;
	m_FrameDuration = 0.5f;
	m_Frametimer = 0.5f;
	m_CurrentFrame = 0;           // 現在のフレーム
	m_Numframes = 8;        // アニメーションの総フレーム数
}
//======================
// デストラクタ
//======================
CEnemy::~CEnemy()
{

}

//======================
// 初期化処理
//======================
HRESULT CEnemy::Init()
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
void CEnemy::Uninit()
{
	Unload();
	CObject2D::Uninit();
}

//======================
// 更新処理
//======================
void CEnemy::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	//頂点バッファをロック
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(m_nEnemyPos.x - m_nEnemySize.x, m_nEnemyPos.y - m_nEnemySize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nEnemyPos.x + m_nEnemySize.x, m_nEnemyPos.y - m_nEnemySize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nEnemyPos.x - m_nEnemySize.x, m_nEnemyPos.y + m_nEnemySize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nEnemyPos.x + m_nEnemySize.x, m_nEnemyPos.y + m_nEnemySize.y, 0.0f);


	m_nEnemyPos.x += m_moveEnemy.x;
	m_nEnemyPos.y += m_moveEnemy.y;

	//移動量を更新
	m_moveEnemy.x += (Length_value2 - m_moveEnemy.x) * Attenuation_value;
	m_moveEnemy.y += (Length_value2 - m_moveEnemy.y) * Attenuation_value;



}

//======================
// 描画処理
//======================
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//======================
// オブジェクト生成処理
//======================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy* enemy = nullptr;

	enemy = new CEnemy;

	if (!FAILED(enemy->Init()))
	{
		enemy->Init();

		enemy->Load();

		enemy->m_nEnemyPos = pos;

		enemy->m_nEnemySize = size;

		enemy->BindTexture(m_pTexTemp);
	}

	return enemy;
}

HRESULT CEnemy::Load()
{
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy000.png", &m_pTexTemp)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CEnemy::Unload()
{
	if (m_pTexTemp != nullptr)
	{
		m_pTexTemp->Release();
		m_pTexTemp = nullptr;
	}
}
