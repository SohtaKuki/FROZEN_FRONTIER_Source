//=================================================
//
// 弾の処理 (bullet.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "bullet.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "explosion.h"

//============================
//コンストラクタ
//============================
CBullet::CBullet()
{
	m_nLife = 0;
}

//============================
//デストラクタ
//============================
CBullet::~CBullet()
{

}

//============================
//弾の初期化処理
//============================
HRESULT CBullet::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//弾の初期化処理
//============================
void CBullet::Uninit()
{
	//初期化
	CObject2D::Uninit();
}

//============================
//弾の更新処理
//============================
void CBullet::Update()
{
	CPlayer::GetPlayerPos() += m_nMove;

	m_nLife--;

	
	if (m_nLife <= 0)
	{
		CExplosion::Create(CPlayer::GetPlayerPos());
		CObject2D::Uninit();
		CObject::Release();
		return;
	}

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos.x = CPlayer::GetPlayerPos().x - 35 * 0.5f;
	pVtx[0].pos.y = CPlayer::GetPlayerPos().y - 35 * 0.5f;

	pVtx[1].pos.x = CPlayer::GetPlayerPos().x + 35 * 0.5f;
 	pVtx[1].pos.y = CPlayer::GetPlayerPos().y - 35 * 0.5f;

	pVtx[2].pos.x = CPlayer::GetPlayerPos().x - 35 * 0.5f;
	pVtx[2].pos.y = CPlayer::GetPlayerPos().y + 35 * 0.5f;

	pVtx[3].pos.x = CPlayer::GetPlayerPos().x + 35 * 0.5f;
	pVtx[3].pos.y = CPlayer::GetPlayerPos().y + 35 * 0.5f;

	//頂点バッファをアンロックする
	CObject2D::GetBuff()->Unlock();
}

//============================
//弾の描画処理
//============================
void CBullet::Draw()
{
	CObject2D::Draw();
}

//============================
//弾の生成処理
//============================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBullet* pBullet;

	pBullet = new CBullet;

	pBullet->CPlayer::GetPlayerPos() = pos;
	pBullet->m_rot = rot;
	pBullet->m_nLife = BULLET_LIFE;

	//移動量を設定
	pBullet->m_nMove.x = sinf(D3DX_PI * (pBullet->m_rot.z / D3DX_PI) - D3DX_PI * 0.5f) * BULLET_SPD;
	pBullet->m_nMove.y = cosf(D3DX_PI * (pBullet->m_rot.z / D3DX_PI) - D3DX_PI * 0.5f) * BULLET_SPD;

	pBullet->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//テクスチャの読み込む
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),"data\\TEXTURE\\bullet_yellow.png",&pTexture);

	//テクスチャの設定
	pBullet->BindTexture(pTexture);

	return pBullet;
}