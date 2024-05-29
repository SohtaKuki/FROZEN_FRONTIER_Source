//=================================================
//
// 2Dポリゴンの描画処理 (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "player.h"
#include "bullet.h"
#include "object.h"
#include "enemy.h"
#include "block.h"

//======================
// コンストラクタ
//======================
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{
	m_PolygonMoveSpeed = 1.0f;
	m_FrameDuration = 0.5f;
	m_Frametimer = 0.5f;
	m_CurrentFrame = 0;           // 現在のフレーム
	m_Numframes = 8;        // アニメーションの総フレーム数
}
//======================
// デストラクタ
//======================
CPlayer::~CPlayer()
{

}

//======================
// 初期化処理
//======================
HRESULT CPlayer::Init()
{
	//初期化
	CObject2D::Init();
	return S_OK;
}

//======================
// 終了処理
//======================
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//======================
// 更新処理
//======================
void CPlayer::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	D3DXVECTOR3 Pos = CObject2D::GetPos();

	//頂点バッファをロック
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		//弾の生成
		CBullet::Create(Pos, m_rotPlayer);
	}

	if (CManager::GetKeyboard()->GetPress(DIK_P))
	{
		//弾の生成
		CBullet::Create(Pos, m_rotPlayer);
	}


	if (CManager::GetKeyboard()->GetPress(DIK_D))
	{
		m_movePlayer.x += Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_A))
	{
		m_movePlayer.x -= Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_W))
	{
		m_movePlayer.y -= Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_S))
	{
		m_movePlayer.y += Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_Q))
	{
		m_rotPlayer.z += 0.2f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_E))
	{
		m_rotPlayer.z -= 0.2f;
	}

	pVtx[0].pos = D3DXVECTOR3(Pos.x - m_nPlayerSize.x, Pos.y - m_nPlayerSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pos.x + m_nPlayerSize.x, Pos.y - m_nPlayerSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pos.x - m_nPlayerSize.x, Pos.y + m_nPlayerSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pos.x + m_nPlayerSize.x, Pos.y + m_nPlayerSize.y, 0.0f);

	// アニメーションフレームの更新
	m_Frametimer += m_FrameDuration;

	if (m_Frametimer >= m_FrameDuration)
	{
		// 次のフレームに進める
		m_CurrentFrame = (m_CurrentFrame + 1) % m_Numframes;

		// フレームの経過時間をリセット
		m_Frametimer = 0.0f;

		CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 1.0f);

		CObject2D::GetBuff()->Unlock();
	}

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject* pObj = CObject::GetObj(3, nCntObj);

		if (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();

			CBlock* pBlock = (CBlock*)pObj;

			if (type == CObject::TYPE::BLOCK)
			{
				//if (Pos.x >= pBlock->GetBlockPos().x - BLOCK_CLLISION
				//	&& Pos.x <= pBlock->GetBlockPos().x + BLOCK_CLLISION
				//	&& Pos.y >= pBlock->GetBlockPos().y - BLOCK_CLLISION
					//&& Pos.y <= pBlock->GetBlockPos().y + BLOCK_CLLISION)
						//ブロックの当たり判定(プレイヤー側)

				bool bIsCollision = pBlock->CollisionBlock(&Pos, &m_nOldPlayerPos, &m_movePlayer, 50, 50);

				if (bIsCollision == true)
				{
					m_nOldPlayerPos = Pos;
					//return;
				}
			}
		}
	}

	////プレイヤーの重力
	//m_movePlayer.y += Length_value1;

	Pos.x += m_movePlayer.x;
	Pos.y += m_movePlayer.y;

	SetPos(Pos);

	//CObject2D::GetPos() += m_movePlayer;

	//移動量を更新
	m_movePlayer.x += (Length_value2 - m_movePlayer.x) * Attenuation_value;
	m_movePlayer.y += (Length_value2 - m_movePlayer.y) * Attenuation_value;



}

//======================
// 描画処理
//======================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//======================
// オブジェクト生成処理
//======================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer* player = new CPlayer;

	player->SetType(TYPE::PLAYER);

	player->CObject2D::SetPos(pos);

	player->m_nOldPlayerPos = pos;

	player->m_nPlayerSize = size;

	player->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//テクスチャの読み込む
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\runningman000.png", &pTexture);

	player->BindTexture(pTexture);

	return player;
}
