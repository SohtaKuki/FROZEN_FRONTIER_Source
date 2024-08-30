//=================================================
//
// �r���{�[�h�`�掮�`���[�W�e�̏��� (3dchargebullet.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dchargebullet.h"
#include "3dblock.h"
#include "3denemy.h"
#include "3dbrokenblock.h"
#include "3dwall.h"
#include "score.h"

//======================
// �R���X�g���N�^
//======================
C3dchargebullet::C3dchargebullet(int nPriority) : CObject3D(nPriority)
{

}

//======================
// �f�X�g���N�^
//======================
C3dchargebullet::~C3dchargebullet()
{

}

//======================
// ����������
//======================
HRESULT C3dchargebullet::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\bullet_RGB.png", &m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 1, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_nSize.x, m_nSize.y, m_nSize.z);
	pVtx[1].pos = D3DXVECTOR3(m_nSize.x, m_nSize.y, m_nSize.z);
	pVtx[2].pos = D3DXVECTOR3(-m_nSize.x, -m_nSize.y, m_nSize.z);
	pVtx[3].pos = D3DXVECTOR3(m_nSize.x, -m_nSize.y, m_nSize.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̏����ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 46, 46, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 46, 46, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 46, 46, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 46, 46, 255);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================
//�I������
//======================
void C3dchargebullet::Uninit()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	CObject3D::Uninit();
}

//======================
//�I������
//======================
void C3dchargebullet::Update()
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nPos += m_nMove;

	m_nLife--;

	//�e������0�̏ꍇ
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-m_nSize.x), (m_nSize.y), (m_nSize.z));
	pVtx[1].pos = D3DXVECTOR3((m_nSize.x), (m_nSize.y), (m_nSize.z));
	pVtx[2].pos = D3DXVECTOR3((-m_nSize.x), (-m_nSize.y), (m_nSize.z));
	pVtx[3].pos = D3DXVECTOR3((m_nSize.x), (-m_nSize.y), (m_nSize.z));

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̏����ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 46, 46, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 46, 46, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 46, 46, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 46, 46, 255);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//�e�ƃu���b�N�̓����蔻��
	for (int nCntObj = 0; nCntObj < C3dblock::MAX_BLOCK; nCntObj++)
	{
		CObject* pObj = CObject::GetObj(3, nCntObj);

		if (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();

			C3dblock* p3dblock = (C3dblock*)pObj;

			D3DXVECTOR3 BlockPos = p3dblock->GetPos();

			//�u���b�N�̏ꍇ
			if (type == CObject::TYPE::BLOCK)
			{
				if (m_nPos.x >= BlockPos.x - 40
					&& m_nPos.x <= BlockPos.x + 40
					&& m_nPos.z >= BlockPos.z - 40
					&& m_nPos.z <= BlockPos.z + 40)
				{
					Uninit();
					return;
				}
			}

		}

	}

	//�e�ƃu���b�N�̓����蔻��
	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		CObject* pObj = CObject::GetObj(3, nCntObj);

		if (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();

			C3dwall* p3dwall = (C3dwall*)pObj;

			D3DXVECTOR3 WallPos = p3dwall->GetPos();

			//�u���b�N�̏ꍇ
			if (type == CObject::TYPE::WALL_WIDTH)
			{
				if (m_nPos.x >= WallPos.x - 120
					&& m_nPos.x <= WallPos.x + 120
					&& m_nPos.z >= WallPos.z - 35
					&& m_nPos.z <= WallPos.z + 35)
				{
					Uninit();
					return;
				}
			}

			//�u���b�N�̏ꍇ
			if (type == CObject::TYPE::WALL_WIDTH_SHORT)
			{
				if (m_nPos.x >= WallPos.x - 60
					&& m_nPos.x <= WallPos.x + 60
					&& m_nPos.z >= WallPos.z - 40
					&& m_nPos.z <= WallPos.z + 40)
				{
					Uninit();
					return;
				}
			}

			//�u���b�N�̏ꍇ
			if (type == CObject::TYPE::WALL_HEIGHT)
			{
				if (m_nPos.x >= WallPos.x - 35
					&& m_nPos.x <= WallPos.x + 35
					&& m_nPos.z >= WallPos.z - 120
					&& m_nPos.z <= WallPos.z + 120)
				{
					Uninit();
					return;
				}
			}

			//�u���b�N�̏ꍇ
			if (type == CObject::TYPE::WALL_HEIGHT_SHORT)
			{
				if (m_nPos.x >= WallPos.x - 35
					&& m_nPos.x <= WallPos.x + 35
					&& m_nPos.z >= WallPos.z - 60
					&& m_nPos.z <= WallPos.z + 60)
				{
					Uninit();
					return;
				}
			}
		}
	}

	//�e�ƃu���b�N�̓����蔻��
	for (int nCntObj = 0; nCntObj < C3dbrokenblock::MAX_BLOCK; nCntObj++)
	{
		CObject* pObj = CObject::GetObj(3, nCntObj);

		if (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();

			C3dbrokenblock* p3dbrokenblock = (C3dbrokenblock*)pObj;

			D3DXVECTOR3 BlockPos = p3dbrokenblock->GetPos();

			//�j��\�u���b�N�̏ꍇ
			if (type == CObject::TYPE::BROKENBLOCK)
			{
				if (m_nPos.x >= BlockPos.x - 40
					&& m_nPos.x <= BlockPos.x + 40
					&& m_nPos.z >= BlockPos.z - 40
					&& m_nPos.z <= BlockPos.z + 40)
				{
					Uninit();
					p3dbrokenblock->Uninit();
					return;
				}
			}
		}
	}

	//�e�ƓG�̓����蔻��
	for (int nCntObj = 0; nCntObj < C3denemy::MAX_ENEMY; nCntObj++)
	{
		CObject* pObj = CObject::GetObj(3, nCntObj);

		if (pObj != nullptr)
		{
			CObject::TYPE type = pObj->GetType();

			C3denemy* p3denemy = (C3denemy*)pObj;

			D3DXVECTOR3 EnemyPos = p3denemy->GetPos();

			//�G�̏ꍇ
			if (type == CObject::TYPE::ENEMY_XMOVE || type == CObject::TYPE::ENEMY_ZMOVE || type == CObject::TYPE::ENEMY_NORMAL)
			{
				if (m_nPos.x >= EnemyPos.x - 40
					&& m_nPos.x <= EnemyPos.x + 40
					&& m_nPos.z >= EnemyPos.z - 40
					&& m_nPos.z <= EnemyPos.z + 40)
				{
					CScore::AddScore(17000);
					p3denemy->Uninit();
					return;
				}
			}

		}
	}

}

//======================
// �`�揈��
//======================
void C3dchargebullet::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//=========================
	// �ǂ߂荞�ݖh�~�R�[�h
	//=========================

	////Z�̔�r���@�ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	////Z�o�b�t�@�ɏ������܂Ȃ�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X�擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����̐��ʂɌ���������
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);	//�t�s������߂�

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	D3DXMatrixTranslation(&mtxTrans, m_nPos.x, m_nPos.y, m_nPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�r���{�[�h�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�A���t�@�e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	//=========================
	// �ǂ߂荞�ݖh�~�R�[�h
	//=========================

	////Z�̔�r���@�ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

	////Z�o�b�t�@�ɏ�������
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//======================
// �I�u�W�F�N�g��������
//======================
C3dchargebullet* C3dchargebullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	C3dchargebullet* chbullet3d = new C3dchargebullet;

	//�������ɐ��������ꍇ
	if (SUCCEEDED(chbullet3d->Init()))
	{
		chbullet3d->SetType(TYPE::CHBULLET);

		chbullet3d->m_nPos = pos;

		//�e�̍��������������␳����
		chbullet3d->m_nPos.y += 10.0f;

		chbullet3d->m_rot = rot;

		chbullet3d->m_nSize = size;

		chbullet3d->m_nLife = 80;

		//�e�̔��˕���
		chbullet3d->m_nMove.x = sinf(chbullet3d->m_rot.y + D3DX_PI) * BULLET_SPD;
		chbullet3d->m_nMove.z = cosf(chbullet3d->m_rot.y + D3DX_PI) * BULLET_SPD;

	}

	return chbullet3d;
}