//=================================================
//
// オブジェクトの処理 (object.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "object.h"

unsigned const int MAX_OBJECT = 1028;	// オブジェクトの最大数
int CObject::m_nNumAll = 0;				// オブジェクト総数
CObject* CObject::m_apObject[MAX_OBJECT] = {};	// オブジェクト管理

//======================
// コンストラクタ
//======================
CObject::CObject()
{

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_apObject[nCnt] == nullptr)
		{
			m_apObject[nCnt] = this;	// 自身を代入
			m_nID = nCnt;	// IDを代入
			m_nNumAll++; // オブジェクト総数を増やす

			break;
		}
	}
}

//======================
// デストラクタ
//======================
CObject::~CObject()
{

}

//======================
// 初期化処理
//======================
HRESULT CObject::Init()
{

}

//======================
// 終了処理
//======================
void CObject::Uninit()
{

}

//======================
// 更新処理
//======================
void CObject::Update()
{
	
}

//======================
// 描画処理
//======================
void CObject::Draw()
{
	
}

//======================
// 解放処理
//======================
void CObject::Release()
{
	int nID = m_nID;

	if (m_apObject[nID] != nullptr)
	{
		delete m_apObject[nID];
		m_apObject[nID] = nullptr;
		m_nNumAll--;
	}
}

//======================
// 全開放処理
//======================
void CObject::ReleaseAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			delete m_apObject[nCnt];
			m_apObject[nCnt] = nullptr;
		}
	}
}

//======================
// 全更新処理
//======================
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			m_apObject[nCnt]->Update();
		}
	}
}

//======================
// 全描画処理
//======================
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			m_apObject[nCnt]->Draw();
		}
	}
}
