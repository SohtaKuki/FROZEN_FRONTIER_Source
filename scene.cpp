//=================================================
//
// 画面遷移処理 (scene.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "scene.h"
#include "objbg.h"
#include "stagemanager.h"
#include "floor.h"


#include "timer.h"
#include "playerhpbar.h"
#include "result.h"


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

	//シーンの初期化
	if (Scene != nullptr)
	{
		Scene->Init();

		return Scene;
	}


	return nullptr;
}

//======================
//コンストラクタ
//======================
CGame::CGame()
{

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

	CTimer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPlayerHpBar::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(-25.0f, -20.0f, 0.0f));
	CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f));

	//ステージマネージャー初期化処理
	CStageManager::Create();

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
	CResultBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

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
	//エンターキーが押されたとき
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CScene::MODE_TITLE);
	}
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
	CObjectBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	return S_OK;
}

//======================
//終了処理
//======================
void CTitle::Uninit()
{
	CScene::Uninit();
}

//======================
//更新処理
//======================
void CTitle::Update()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CScene::MODE_GAME);
	}

}

//======================
//描画処理
//======================
void CTitle::Draw()
{

}
