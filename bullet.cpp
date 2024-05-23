

#include "bullet.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"

//============================
//コンストラクタ
//============================
CBullet::CBullet()
{

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

	VERTEX_2D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos.x = CObject2D::GetPos().x - 30 * 0.5f;
	pVtx[0].pos.y = CObject2D::GetPos().y - 30 * 0.5f;
	pVtx[1].pos.x = CObject2D::GetPos().x + 30 * 0.5f;
	pVtx[1].pos.y = CObject2D::GetPos().y - 30 * 0.5f;
	pVtx[2].pos.x = CObject2D::GetPos().x - 30 * 0.5f;
	pVtx[2].pos.y = CObject2D::GetPos().y + 30 * 0.5f;
	pVtx[3].pos.x = CObject2D::GetPos().x + 30 * 0.5f;
	pVtx[3].pos.y = CObject2D::GetPos().y + 30 * 0.5f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//x.y
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	CObject2D::GetBuff()->Unlock();

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
	//位置に移動量を加算
	CObject2D::GetPos() += m_nMove;

	m_Life--;

	//体力が0になったら
	if (m_Life <= 0)
	{
		////弾の削除と爆発
		//CExplosion::Create(CObject2D::GetPos());
		CObject2D::Uninit();
		CObject::Release();
		return;
	}

	VERTEX_2D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos.x = CObject2D::GetPos().x - BULLET_SIZE * 0.5f;
	pVtx[0].pos.y = CObject2D::GetPos().y - BULLET_SIZE * 0.5f;
	pVtx[1].pos.x = CObject2D::GetPos().x + BULLET_SIZE * 0.5f;
	pVtx[1].pos.y = CObject2D::GetPos().y - BULLET_SIZE * 0.5f;
	pVtx[2].pos.x = CObject2D::GetPos().x - BULLET_SIZE * 0.5f;
	pVtx[2].pos.y = CObject2D::GetPos().y + BULLET_SIZE * 0.5f;
	pVtx[3].pos.x = CObject2D::GetPos().x + BULLET_SIZE * 0.5f;
	pVtx[3].pos.y = CObject2D::GetPos().y + BULLET_SIZE * 0.5f;

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

	//パラメータの設定
	pBullet->CObject2D::GetPos() = pos;
	pBullet->m_rot = rot;
	pBullet->m_Life = BULLET_LIFE;

	//移動量を設定
	pBullet->m_nMove.x = sinf(D3DX_PI * (pBullet->m_rot.z / D3DX_PI) - D3DX_PI * 0.5f) * 5.0f;
	pBullet->m_nMove.y = cosf(D3DX_PI * (pBullet->m_rot.z / D3DX_PI) - D3DX_PI * 0.5f) * 5.0f;

	pBullet->Init();

	//テクスチャの生成用
	LPDIRECT3DTEXTURE9 pTexture;

	//テクスチャの読み込む
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),"data\\TEXTURE\\bullet_yellow.png",&pTexture);

	//テクスチャの設定
	pBullet->BindTexture(pTexture);

	return pBullet;
}