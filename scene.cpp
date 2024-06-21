//=================================================
//
// ��ʑJ�ڏ��� (scene.cpp)
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
//�R���X�g���N�^
//======================
CScene::CScene()
{

}

//======================
//�f�X�g���N�^
//======================
CScene::~CScene()
{

}

//======================
//����������
//======================
HRESULT CScene::Init()
{
	return S_OK;
}

//======================
//�I������
//======================
void CScene::Uninit()
{
	CObject::ReleaseAll();
}

//======================
//�X�V����
//======================
void CScene::Update()
{

}

//======================
//�`�揈��
//======================
void CScene::Draw()
{

}

//======================
// �I�u�W�F�N�g��������
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
//�R���X�g���N�^
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
//�f�X�g���N�^
//======================
CGame::~CGame()
{

}

//======================
//����������
//======================
HRESULT CGame::Init()
{
	CScene::Init();

	return S_OK;
}

//======================
//�I������
//======================
void CGame::Uninit()
{
	CScene::Uninit();
}

//======================
//�X�V����
//======================
void CGame::Update()
{

}

//======================
//�`�揈��
//======================
void CGame::Draw()
{

}

//======================
//�R���X�g���N�^
//======================
CResult::CResult()
{

}

//======================
//�f�X�g���N�^
//======================
CResult::~CResult()
{

}

//======================
//����������
//======================
HRESULT CResult::Init()
{
	return S_OK;
}

//======================
//�I������
//======================
void CResult::Uninit()
{
	CScene::Uninit();
}

//======================
//�X�V����
//======================
void CResult::Update()
{

}

//======================
//�`�揈��
//======================
void CResult::Draw()
{

}

//======================
//�R���X�g���N�^
//======================
CTitle::CTitle()
{
	CObjectBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
}

//======================
//�f�X�g���N�^
//======================
CTitle::~CTitle()
{

}

//======================
//����������
//======================
HRESULT CTitle::Init()
{
	return S_OK;
}

//======================
//�I������
//======================
void CTitle::Uninit()
{

}

//======================
//�X�V����
//======================
void CTitle::Update()
{


}

//======================
//�`�揈��
//======================
void CTitle::Draw()
{

}
