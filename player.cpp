//=================================================
//
// 2Dポリゴンの描画処理 (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "player.h"
#include "bullet.h"

//======================
// コンストラクタ
//======================
CPlayer::CPlayer()
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

	//頂点バッファをロック
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	if (CManager::GetKeyboard()->GetPress(DIK_SPACE))
	{
		//弾の生成
		CBullet::Create(m_nPlayerPos, m_rotPlayer);
	}


	if (CManager::GetKeyboard()->GetPress(DIK_W))
	{
		m_movePlayer.y -= Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_S))
	{
		m_movePlayer.y += Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_D))
	{
		m_movePlayer.x += Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_A))
	{
		m_movePlayer.x -= Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_Q))
	{
		m_rotPlayer.z += 0.2f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_E))
	{
		m_rotPlayer.z -= 0.2f;


	}

	pVtx[0].pos = D3DXVECTOR3(m_nPlayerPos.x - m_nPlayerSize.x, m_nPlayerPos.y - m_nPlayerSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nPlayerPos.x + m_nPlayerSize.x, m_nPlayerPos.y - m_nPlayerSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nPlayerPos.x - m_nPlayerSize.x, m_nPlayerPos.y + m_nPlayerSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nPlayerPos.x + m_nPlayerSize.x, m_nPlayerPos.y + m_nPlayerSize.y, 0.0f);

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
		CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 1.0f);

		CObject2D::GetBuff()->Unlock();
	}

	m_nPlayerPos.x += m_movePlayer.x;
	m_nPlayerPos.y += m_movePlayer.y;

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

	player->m_nPlayerPos = pos;

	player->m_nPlayerSize = size;

	player->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//テクスチャの読み込む
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\runningman000.png", &pTexture);

	player->BindTexture(pTexture);

	return player;
}
