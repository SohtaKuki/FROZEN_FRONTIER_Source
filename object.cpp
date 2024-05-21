#include "object.h"

unsigned const int MAX_OBJECT = 1028;	// オブジェクトの最大数
int CObject::m_nNumAll = 0;				// オブジェクト総数
CObject* CObject::m_apObject[MAX_OBJECT] = {};	// オブジェクト管理

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

CObject::~CObject()
{

}

HRESULT CObject::Init()
{


	return S_OK;
}

void CObject::Uninit()
{

}

void CObject::Update()
{
	
}

void CObject::Draw()
{
	
}

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
