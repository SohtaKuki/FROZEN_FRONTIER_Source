//=================================================
//
// カメラ処理 (camera.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "camera.h"
#include "manager.h"


//======================
// コンストラクタ
//======================
CCamera::CCamera()
{

}

//======================
// デストラクタ
//======================
CCamera::~CCamera()
{

}

//======================
// 初期化処理
//======================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 110.0f, -700.0f);
	m_posR = D3DXVECTOR3(0.0f ,0.0f, 300.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = sqrtf((0.0f * 0.0f * 100.0f) + (m_posV.z * m_posV.z));

	return S_OK;
}

//======================
// 終了処理
//======================
void CCamera::Uninit()
{

}

//======================
// 更新処理
//======================
void CCamera::Update()
{
	if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
	{
		m_posV.x += 2.0f;
		m_posR.x += 2.0f;

	}

	if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
	{
		m_posV.x -= 2.0f;
		m_posR.x -= 2.0f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_UP))
	{
		m_posV.y += 2.0f;
		m_posR.y += 2.0f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_DOWN))
	{
		m_posV.y -= 2.0f;
		m_posR.y -= 2.0f;
	}


	if (CManager::GetKeyboard()->GetPress(DIK_F))
	{
		m_posV.z -= 6.0f;
		m_posR.z -= 6.0f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_R))
	{
		m_posV.z += 6.0f;
		m_posR.z += 6.0f;
	}
}

//======================
// カメラの設定処理
//======================
void CCamera::SetCamera()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(50.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1800.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

