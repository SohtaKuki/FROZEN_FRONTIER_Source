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

CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pKeyboard = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CScene* CManager::m_pScene = nullptr;
CFade* CManager::m_pFade = nullptr;


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

	m_pScene = new CScene();

	m_pScene->Init();

	m_pFade = new CFade();
	
	m_pFade->Init();
	
	//SetMode(CScene::MODE::MODE_TITLE);

	//m_pFade->SetFade(CScene::MODE::MODE_TITLE);

	//CBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f));


	//↓2Dポリゴン生成の残骸



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

	m_pLight->Update();

	m_pCamera->Update();

	m_pScene->Update();

	m_pFade->Update();
}

//======================
// 描画処理
//======================
void CManager::Draw()
{
	m_pRenderer->Draw();

	m_pFade->Draw();
}

//======================
// モードを生成
//======================
void CManager::SetMode(CScene::MODE mode)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	m_pScene = CScene::Create(mode);
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

//======================
// ライトクラスポインタ取得処理
//======================
CFade* CManager::GetFade()
{
	return m_pFade;
}



