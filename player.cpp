//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "player.h"
#include "bullet.h"
#include "object.h"
#include "enemy.h"
#include "block.h"

//======================
// �R���X�g���N�^
//======================
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{
	m_PolygonMoveSpeed = 1.0f;
	m_FrameDuration = 0.5f;
	m_Frametimer = 0.5f;
	m_CurrentFrame = 0;           // ���݂̃t���[��
	m_Numframes = 8;        // �A�j���[�V�����̑��t���[����
	m_movePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//======================
// �f�X�g���N�^
//======================
CPlayer::~CPlayer()
{

}

//======================
// ����������
//======================
HRESULT CPlayer::Init()
{
	//������
	CObject2D::Init();
	return S_OK;
}

//======================
// �I������
//======================
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//======================
// �X�V����
//======================
void CPlayer::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//�d��
	m_movePlayer.y += 1.0f;

	D3DXVECTOR3 Pos = CObject2D::GetPos();

	//���_�o�b�t�@�����b�N
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		//�e�̐���
		m_movePlayer.y = -30.0f;
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_P))
	{
		CBullet::Create(Pos, m_rotPlayer);
	}

	if (CManager::GetKeyboard()->GetPress(DIK_L))
	{
		//�e�̐���
		CBullet::Create(Pos, m_rotPlayer);
	}


	if (CManager::GetKeyboard()->GetPress(DIK_D))
	{
		m_movePlayer.x += Length_value1;
		m_movePlayer.y += cosf(D3DX_PI / 2) * 2.0f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_A))
	{
		m_movePlayer.x -= Length_value1;
		m_movePlayer.y += cosf(-D3DX_PI / 2) * 2.0f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_W))
	{
		m_movePlayer.y -= Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_S))
	{
		m_movePlayer.y += Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_Q))
	{
		m_rotPlayer.z += 0.2f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_E))
	{
		m_rotPlayer.z -= 0.2f;
	}

	pVtx[0].pos = D3DXVECTOR3(Pos.x - m_nPlayerSize.x, Pos.y - m_nPlayerSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pos.x + m_nPlayerSize.x, Pos.y - m_nPlayerSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pos.x - m_nPlayerSize.x, Pos.y + m_nPlayerSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pos.x + m_nPlayerSize.x, Pos.y + m_nPlayerSize.y, 0.0f);

	// �A�j���[�V�����t���[���̍X�V
	m_Frametimer += m_FrameDuration;

	if (m_Frametimer >= m_FrameDuration)
	{
		// ���̃t���[���ɐi�߂�
		m_CurrentFrame = (m_CurrentFrame + 1) % m_Numframes;

		// �t���[���̌o�ߎ��Ԃ����Z�b�g
		m_Frametimer = 0.0f;

		CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 1.0f);

		CObject2D::GetBuff()->Unlock();
	}

	//�ߋ����W��ۑ�
	m_nOldPlayerPos = Pos;

	Pos.x += m_movePlayer.x;
	Pos.y += m_movePlayer.y;

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

			if (pObj != nullptr)
			{
				CObject::TYPE type = pObj->GetType();

				if (type == CObject::TYPE::BLOCK)
				{
					CBlock* pBlock = (CBlock*)pObj;

					bool bIsCollision = pBlock->CollisionBlock(&Pos, &m_nOldPlayerPos, &m_movePlayer, 50, 0);

					if (bIsCollision == true)
					{
						m_movePlayer.y = 0.0f;
					}
				}
			}
		}
	}

	////�v���C���[�̏d��
	//m_movePlayer.y += Length_value1;

	SetPos(Pos);

	//CObject2D::GetPos() += m_movePlayer;

	//X���W�̈ړ��ʂ��X�V
	m_movePlayer.x += (Length_value2 - m_movePlayer.x) * Attenuation_value;

	////Y���W�̈ړ��ʂ��X�V(STG�̂ݗL���ɂ���)
	//m_movePlayer.y += (Length_value2 - m_movePlayer.y) * Attenuation_value;




}

//======================
// �`�揈��
//======================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//======================
// �I�u�W�F�N�g��������
//======================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer* player = new CPlayer;

	player->SetType(TYPE::PLAYER);

	player->CObject2D::SetPos(pos);

	player->m_nOldPlayerPos = pos;

	player->m_nPlayerSize = size;

	player->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\runningman000.png", &pTexture);

	player->BindTexture(pTexture);

	return player;
}
