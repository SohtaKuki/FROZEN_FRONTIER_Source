//=================================================
//
// 画面遷移処理 (scene.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "scene.h"
#include "objbg.h"
#include "floor.h"
#include "objectX.h"
#include "3dplayer.h"
#include "billboard.h"
#include "3dblock.h"
#include "startobj.h"
#include "3ditem.h"
#include "timer.h"

//======================
//コンストラクタ
//======================
CScene::CScene()
{

}

//======================
//デストラクタ
//======================
CScene::~CScene()
{

}

//======================
//初期化処理
//======================
HRESULT CScene::Init()
{
	return S_OK;
}

//======================
//終了処理
//======================
void CScene::Uninit()
{
	CObject::ReleaseAll();
}

//======================
//更新処理
//======================
void CScene::Update()
{

}

//======================
//描画処理
//======================
void CScene::Draw()
{

}

//======================
// オブジェクト生成処理
//======================
CScene* CScene::Create(MODE mode)
{
	CScene* Scene = nullptr;

	switch (mode)
	{
	case MODE_TITLE:
		Scene = new CTitle();
		break;
	case MODE_GAME:
		Scene = new CGame;
		break;
	case MODE_RESULT:
		Scene = new CResult;
		break;
	default:
		break;

	}

	Scene->m_mode = mode;
	Scene->Init();
	return Scene;
}

//======================
//コンストラクタ
//======================
CGame::CGame()
{
	CTimer::Create(D3DXVECTOR3(0.0f, 0.0f, 00.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f));
	C3dplayer::Create(D3DXVECTOR3(300.0f, 0.0f, -50.0f));
	C3dstartobj::Create();

	C3dblock::Create(D3DXVECTOR3(100.0f, 0.0f, 50.0f));

	C3ditem::Create(D3DXVECTOR3(-50.0f, 0.0f, 50.0f), 0);

	C3ditem::Create(D3DXVECTOR3(-150.0f, 0.0f, 50.0f), 0);
	CBillboard::Create(D3DXVECTOR3(37.0f, 55.0f, -10.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));
	CBillboard::Create(D3DXVECTOR3(67.0f, 55.0f, -30.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f));

}

//======================
//デストラクタ
//======================
CGame::~CGame()
{

}

//======================
//初期化処理
//======================
HRESULT CGame::Init()
{
	CScene::Init();

	return S_OK;
}

//======================
//終了処理
//======================
void CGame::Uninit()
{
	CScene::Uninit();
}

//======================
//更新処理
//======================
void CGame::Update()
{

}

//======================
//描画処理
//======================
void CGame::Draw()
{

}

//======================
//コンストラクタ
//======================
CResult::CResult()
{

}

//======================
//デストラクタ
//======================
CResult::~CResult()
{

}

//======================
//初期化処理
//======================
HRESULT CResult::Init()
{
	return S_OK;
}

//======================
//終了処理
//======================
void CResult::Uninit()
{
	CScene::Uninit();
}

//======================
//更新処理
//======================
void CResult::Update()
{

}

//======================
//描画処理
//======================
void CResult::Draw()
{

}

//======================
//コンストラクタ
//======================
CTitle::CTitle()
{
	CObjectBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
}

//======================
//デストラクタ
//======================
CTitle::~CTitle()
{

}

//======================
//初期化処理
//======================
HRESULT CTitle::Init()
{
	return S_OK;
}

//======================
//終了処理
//======================
void CTitle::Uninit()
{

}

//======================
//更新処理
//======================
void CTitle::Update()
{


}

//======================
//描画処理
//======================
void CTitle::Draw()
{

}
