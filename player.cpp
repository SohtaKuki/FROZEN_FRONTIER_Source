//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "player.h"
#include "bullet.h"

//======================
// �R���X�g���N�^
//======================
CPlayer::CPlayer()
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
CPlayer::~CPlayer()
{

}

//======================
// ����������
//======================
HRESULT CPlayer::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_OBJECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\runningman000.png", &m_pTexBuff);

	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos.x = m_PolygonPosX + sinf(m_rotPlayer.z - D3DX_PI * 0.75) * m_fLengthPlayer;
	pVtx[0].pos.y = m_PolygonPosY + cosf(m_rotPlayer.z - D3DX_PI * 0.75f) * m_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_PolygonPosX + sinf(m_rotPlayer.z + D3DX_PI * 0.75f) * m_fLengthPlayer;
	pVtx[1].pos.y = m_PolygonPosY + cosf(m_rotPlayer.z + D3DX_PI * 0.75f) * m_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_PolygonPosX + sinf(m_rotPlayer.z - D3DX_PI * 0.75f) * m_fLengthPlayer;
	pVtx[2].pos.y = m_PolygonPosY + cosf(m_rotPlayer.z - D3DX_PI * 0.75f) * m_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_PolygonPosX + sinf(m_rotPlayer.z + D3DX_PI * 0.25f) * m_fLengthPlayer;
	pVtx[3].pos.y = m_PolygonPosY + cosf(m_rotPlayer.z + D3DX_PI * 0.25f) * m_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================
// �I������
//======================
void CPlayer::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexBuff != nullptr)
	{
		m_pTexBuff->Release();
		m_pTexBuff = nullptr;
	}
}

//======================
// �X�V����
//======================
void CPlayer::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (CManager::GetKeyboard()->GetPress(DIK_W))
	{
		m_movePlayer.y -= Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_S))
	{
		m_movePlayer.y += Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_D))
	{
		m_movePlayer.x += Length_value1;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_A))
	{
		m_movePlayer.x -= Length_value1;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_SPACE))
	{
		//�e�̐���
		CBullet::Create(CObject2D::GetPos(), m_rot);
	}

	pVtx[0].pos = D3DXVECTOR3(m_nPlayerPos.x - m_nPlayerSize.x, m_nPlayerPos.y - m_nPlayerSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nPlayerPos.x + m_nPlayerSize.x, m_nPlayerPos.y - m_nPlayerSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nPlayerPos.x - m_nPlayerSize.x, m_nPlayerPos.y + m_nPlayerSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nPlayerPos.x + m_nPlayerSize.x, m_nPlayerPos.y + m_nPlayerSize.y, 0.0f);

	// �A�j���[�V�����t���[���̍X�V
	m_Frametimer += m_FrameDuration;

	if (m_Frametimer >= m_FrameDuration)
	{
		// ���̃t���[���ɐi�߂�
		m_CurrentFrame = (m_CurrentFrame + 1) % m_Numframes;

		// �t���[���̌o�ߎ��Ԃ����Z�b�g
		m_Frametimer = 0.0f;

		// �e�N�X�`�����W�̍X�V
		VERTEX_2D* pVtx;
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f * m_CurrentFrame, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f * (m_CurrentFrame + 1), 1.0f);



		m_pVtxBuff->Unlock();
	}

	m_nPlayerPos.x += m_movePlayer.x;
	m_nPlayerPos.y += m_movePlayer.y;

	//�ړ��ʂ��X�V
	m_movePlayer.x += (Length_value2 - m_movePlayer.x) * Attenuation_value;
	m_movePlayer.y += (Length_value2 - m_movePlayer.y) * Attenuation_value;


	//if (CPlayer::AnimationPTN > IMAGE_PATTERN_ANIM)
	//{
	//	CPlayer::AnimationPTN = 0;
	//}

}

//======================
// �`�揈��
//======================
void CPlayer::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTexBuff);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//======================
// �I�u�W�F�N�g��������
//======================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer* player = new CPlayer;

	player->m_nPlayerPos = pos;

	player->m_nPlayerSize = size;

	player->Init();

	return player;
}
