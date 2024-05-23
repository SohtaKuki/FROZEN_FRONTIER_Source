//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "bullet.h"

//======================
// �R���X�g���N�^
//======================
CBullet::CBullet()
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
CBullet::~CBullet()
{

}

//======================
// ����������
//======================
HRESULT CBullet::Init()
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
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet_yellow.png", &m_pTexBuff);

	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos.x = m_PolygonPosX + sinf(m_rotBullet.z - D3DX_PI * 0.75) * m_fLengthBullet;
	pVtx[0].pos.y = m_PolygonPosY + cosf(m_rotBullet.z - D3DX_PI * 0.75f) * m_fLengthBullet;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_PolygonPosX + sinf(m_rotBullet.z + D3DX_PI * 0.75f) * m_fLengthBullet;
	pVtx[1].pos.y = m_PolygonPosY + cosf(m_rotBullet.z + D3DX_PI * 0.75f) * m_fLengthBullet;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_PolygonPosX + sinf(m_rotBullet.z - D3DX_PI * 0.75f) * m_fLengthBullet;
	pVtx[2].pos.y = m_PolygonPosY + cosf(m_rotBullet.z - D3DX_PI * 0.75f) * m_fLengthBullet;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_PolygonPosX + sinf(m_rotBullet.z + D3DX_PI * 0.25f) * m_fLengthBullet;
	pVtx[3].pos.y = m_PolygonPosY + cosf(m_rotBullet.z + D3DX_PI * 0.25f) * m_fLengthBullet;
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
void CBullet::Uninit()
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
void CBullet::Update()
{
	int nCntExplosion;
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (CManager::GetKeyboard())
	{
		m_moveBullet.x += 1;
	}

	pVtx[0].pos = D3DXVECTOR3(m_nBulletPos.x - m_nBulletSize.x, m_nBulletPos.y - m_nBulletSize.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nBulletPos.x + m_nBulletSize.x, m_nBulletPos.y - m_nBulletSize.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nBulletPos.x - m_nBulletSize.x, m_nBulletPos.y + m_nBulletSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nBulletPos.x + m_nBulletSize.x, m_nBulletPos.y + m_nBulletSize.y, 0.0f);


	m_nBulletPos.x += m_moveBullet.x;
	m_nBulletPos.y += m_moveBullet.y;

	//�ړ��ʂ��X�V
	m_moveBullet.x += (Length_value2 - m_moveBullet.x) * Attenuation_value;
	m_moveBullet.y += (Length_value2 - m_moveBullet.y) * Attenuation_value;


	//if (CBullet::AnimationPTN > IMAGE_PATTERN_ANIM)
	//{
	//	CBullet::AnimationPTN = 0;
	//}

}

//======================
// �`�揈��
//======================
void CBullet::Draw()
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
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	CBullet* bullet = new CBullet;

	bullet->m_nBulletPos = pos;

	bullet->m_nBulletSize = size;

	bullet->Init();

	return bullet;
}