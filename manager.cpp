//=================================================
//
// ポリゴン描画のマネージャー管理 (manager.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "object3D.h"
#include "objbg.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "block.h"
#include "item.h"
#include "camera.h"
#include "light.h"
#include "floor.h"
#include "model.h"
#include "3dplayer.h"
#include "billboard.h"
#include "3dblock.h"

CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pKeyboard = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;

//======================
// コンストラクタ
//======================
CManager::CManager()
{

}

//======================
// デストラクタ
//======================
CManager::~CManager()
{

}

//======================
// 初期化処理
//======================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd,BOOL bWindow)
{
	m_pRenderer = new CRenderer;

	m_pKeyboard = new CInputKeyboard;

	m_pRenderer->Init(hWnd, bWindow);

	m_pKeyboard->Init(hInstance, hWnd);

	m_pCamera = new CCamera();

	m_pCamera->Init();

	m_pLight = new CLight();

	m_pLight->Init();

	CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f));
	C3dplayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	C3dblock::Create(D3DXVECTOR3(100.0f, 0.0f, 50.0f));
	C3dblock::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	//CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f));


	//↓2Dポリゴン生成の残骸

	//CObjectBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//CBlock::Create(D3DXVECTOR3(340.0f, 700.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),(CBlock::BLOCKTYPE::NORMAL));
	//CBlock::Create(D3DXVECTOR3(390.0f, 700.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),( CBlock::BLOCKTYPE::NORMAL));
	//CBlock::Create(D3DXVECTOR3(640.0f, 700.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), (CBlock::BLOCKTYPE::NORMAL));
	//CBlock::Create(D3DXVECTOR3(1000.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),(CBlock::BLOCKTYPE::NORMAL));
	//CBlock::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), (CBlock::BLOCKTYPE::NORMAL));

	//CItem::Create(D3DXVECTOR3(570.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//CPlayer::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//CEnemy::Create(D3DXVECTOR3(690.0f, 300.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));


	return S_OK;
}

//======================
// 終了処理
//======================
void CManager::Uninit()
{
	CObject::ReleaseAll();

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//======================
// 更新処理
//======================
void CManager::Update()
{
	m_pRenderer->Update();

	m_pKeyboard->Update();

	m_pCamera->Update();

	m_pLight->Update();
}

//======================
// 描画処理
//======================
void CManager::Draw()
{
	m_pRenderer->Draw();
}

//======================
// レンダラークラスポインタ取得処理
//======================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//======================
// キーボードクラスポインタ取得処理
//======================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//======================
// カメラクラスポインタ取得処理
//======================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//======================
// ライトクラスポインタ取得処理
//======================
CLight* CManager::GetLight()
{
	return m_pLight;
}

