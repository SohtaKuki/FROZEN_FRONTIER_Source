//=================================================
//
// ��ʑJ�ڏ��� (scene.cpp)
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
#include "object2D.h"
#include "result.h"
#include "titlebg.h"
#include "gameui.h"
#include "score.h"
#include "resultscore.h"
#include "3dchargeshotui.h"


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

	//�V�[���̏�����
	if (Scene != nullptr)
	{
		Scene->Init();

		return Scene;
	}


	return nullptr;
}

//======================
//�R���X�g���N�^
//======================
CGame::CGame()
{

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

	CTimer::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CScore::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CPlayerHpBar::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(-25.0f, -20.0f, 0.0f));


	//�X�e�[�W�}�l�[�W���[����������
	CStageManager::Create();
	CChargeshotui::Create(D3DXVECTOR3(150.0f, 100.0f, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0));
	//CGameui::Create(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 140.0f, 0.0f));

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
	CResultBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	CResultScore::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
	//�G���^�[�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		CManager::GetFade()->SetFade(CScene::MODE_TITLE);
	}
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
	CTitleBG::Create();
	//CObjectBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	return S_OK;
}

//======================
//�I������
//======================
void CTitle::Uninit()
{
	CScene::Uninit();
}

//======================
//�X�V����
//======================
void CTitle::Update()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		CManager::GetFade()->SetFade(CScene::MODE_GAME);
	}

}

//======================
//�`�揈��
//======================
void CTitle::Draw()
{

}
