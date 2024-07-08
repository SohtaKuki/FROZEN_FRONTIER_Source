//=================================================
//
// ステージマネージャー処理 (texture.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "stagemanager.h"

#include "3denemy.h"
#include "3dbrokenblock.h"
#include "3dblock.h"
#include "startobj.h"
#include "3ditem.h"
#include "objectX.h"
#include "3dplayer.h"
#include "billboard.h"

//======================
//コンストラクタ
//======================
CStageManager::CStageManager()
{

}

//======================
//デストラクタ
//======================
CStageManager::~CStageManager()
{

}

//======================
//初期化処理
//======================
HRESULT CStageManager::Init()
{
	C3dplayer::Create(D3DXVECTOR3(300.0f, 0.0f, -50.0f));

	C3denemy::Create(D3DXVECTOR3(-300.0f, 0.0f, -100.0f), 0);
	C3denemy::Create(D3DXVECTOR3(-300.0f, 0.0f, -400.0f), 1);
	C3denemy::Create(D3DXVECTOR3(-300.0f, 0.0f, -700.0f), 1);

	C3dstartobj::Create();

	C3dblock::Create(D3DXVECTOR3(100.0f, 0.0f, 50.0f));
	C3dblock::Create(D3DXVECTOR3(300.0f, 0.0f, 50.0f));


	C3dblock::Create(D3DXVECTOR3(400.0f, 0.0f, 50.0f));



	C3dbrokenblock::Create(D3DXVECTOR3(100.0f, 0.0f, 250.0f));
	C3dbrokenblock::Create(D3DXVECTOR3(300.0f, 0.0f, 250.0f));


	C3dbrokenblock::Create(D3DXVECTOR3(00.0f, 0.0f, 250.0f));

	C3ditem::Create(D3DXVECTOR3(-50.0f, 0.0f, 50.0f), 0);

	C3ditem::Create(D3DXVECTOR3(-150.0f, 0.0f, 50.0f), 1);

	C3ditem::Create(D3DXVECTOR3(-300.0f, 0.0f, 50.0f), 1);

	return S_OK;
}

void CStageManager::Uninit()
{

}

void CStageManager::Update()
{

}

void CStageManager::Draw()
{

}
