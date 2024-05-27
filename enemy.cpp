//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "enemy.h"
#include "bullet.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CEnemy::m_pTexTemp = nullptr;

//======================
// �R���X�g���N�^
//======================
CEnemy::CEnemy()
{
	m_PolygonMoveSpeed = 1.0f;
	m_PolygonPosX = 500.0f;
	m_PolygonPosY = 200.0f;
	m_FrameDuration = 0.5f;
	m_Frametimer = 0.5f;
	m_CurrentFrame = 0;           // ���݂̃t���[��
	m_Numframes = 8;        // �A�j���[�V�����̑��t���[����
}
//======================
// �f�X�g���N�^
//======================
CEnemy::~CEnemy()
{

}

//======================
// ����������
//======================
HRESULT CEnemy::Init()
{
	//������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
// �I������
//======================
void CEnemy::Uninit()
{
	Unload();
	CObject2D::Uninit();
}

//======================
// �X�V����
//======================
void CEnemy::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(m_nEnemyPos.x - m_nEnemySize.x, m_nEnemyPos.y - m_nEnemySize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nEnemyPos.x + m_nEnemySize.x, m_nEnemyPos.y - m_nEnemySize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nEnemyPos.x - m_nEnemySize.x, m_nEnemyPos.y + m_nEnemySize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nEnemyPos.x + m_nEnemySize.x, m_nEnemyPos.y + m_nEnemySize.y, 0.0f);


	m_nEnemyPos.x += m_moveEnemy.x;
	m_nEnemyPos.y += m_moveEnemy.y;

	//�ړ��ʂ��X�V
	m_moveEnemy.x += (Length_value2 - m_moveEnemy.x) * Attenuation_value;
	m_moveEnemy.y += (Length_value2 - m_moveEnemy.y) * Attenuation_value;



}

//======================
// �`�揈��
//======================
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//======================
// �I�u�W�F�N�g��������
//======================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy* enemy = nullptr;

	enemy = new CEnemy;

	if (!FAILED(enemy->Init()))
	{
		enemy->Init();

		enemy->Load();

		enemy->m_nEnemyPos = pos;

		enemy->m_nEnemySize = size;

		enemy->BindTexture(m_pTexTemp);
	}

	return enemy;
}

HRESULT CEnemy::Load()
{
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy000.png", &m_pTexTemp)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CEnemy::Unload()
{
	if (m_pTexTemp != nullptr)
	{
		m_pTexTemp->Release();
		m_pTexTemp = nullptr;
	}
}
