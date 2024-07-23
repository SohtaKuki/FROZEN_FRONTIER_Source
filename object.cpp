//=================================================
//
// �I�u�W�F�N�g�̏��� (object.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "object.h"

unsigned const int MAX_OBJECT = 1028;	// �I�u�W�F�N�g�̍ő吔
int CObject::m_nNumAll = 0;				// �I�u�W�F�N�g����
CObject* CObject::m_apObject[MAX_PRIORITY][MAX_OBJECT] = {};	// �I�u�W�F�N�g�Ǘ�

//======================
// �R���X�g���N�^
//======================
CObject::CObject(int nPriority)
{
	m_nPriority = nPriority;

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		if (m_apObject[m_nPriority][nCnt] == nullptr)
		{
			m_apObject[m_nPriority][nCnt] = this;	// ���g����
			m_nID = nCnt;	// ID����
			m_nNumAll++; // �I�u�W�F�N�g�����𑝂₷

			break;
		}
	}
}

//======================
// �f�X�g���N�^
//======================
CObject::~CObject()
{

}

//======================
// ����������
//======================
HRESULT CObject::Init()
{
	return S_OK;
}

//======================
// �I������
//======================
void CObject::Uninit()
{

}

//======================
// �X�V����
//======================
void CObject::Update()
{

}

//======================
// �`�揈��
//======================
void CObject::Draw()
{
	
}

//======================
// �������
//======================
void CObject::Release()
{
	int nID = m_nID;

	int nPriority = m_nPriority;
	
	if (m_apObject[nID] != nullptr)
	{
		delete m_apObject[nPriority][nID];
		m_apObject[nPriority][nID] = nullptr;
		m_nNumAll--;
	}

	
}

//======================
// �S�J������
//======================
void CObject::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{

		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_apObject[nCntPriority][nCnt] != nullptr)
			{
				m_apObject[nCntPriority][nCnt]->Release();
				m_apObject[nCntPriority][nCnt] = nullptr;
			}
		}
	}
}

//======================
// �S�X�V����
//======================
void CObject::UpdateAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_apObject[nCntPriority][nCnt] != nullptr)
			{
				m_apObject[nCntPriority][nCnt]->Update();
			}
		}
	}
}

//======================
// �S�`�揈��
//======================
void CObject::DrawAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			if (m_apObject[nCntPriority][nCnt] != nullptr)
			{
				m_apObject[nCntPriority][nCnt]->Draw();
			}
		}
	}
}

//=====================
// �I�u�W�F�N�g�擾
//=====================
CObject * CObject::GetObj(int nPriority ,int nIdx)
{
	return m_apObject[nPriority][nIdx];
}


void CObject::SetType(TYPE type)
{
	m_type = type;
}
