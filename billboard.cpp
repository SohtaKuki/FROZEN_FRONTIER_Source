#include "billboard.h"

//======================
// �R���X�g���N�^
//======================
CBillboard::CBillboard(int nPriority) : CObject3D(nPriority)
{

}

//======================
// �f�X�g���N�^
//======================
CBillboard::~CBillboard()
{

}

//======================
// ����������
//======================
HRESULT CBillboard::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	for (int nCnt = 0; nCnt < MAX_BIL; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			m_apBillboard[nCnt]->m_nPos = D3DXVECTOR3(37.0f, 55.0f, -10.0f);
			break;
		case 1:
			m_apBillboard[nCnt]->m_nPos = D3DXVECTOR3(57.0f, 50.0f, -17.0f);
			break;
		case 2:
			m_apBillboard[nCnt]->m_nPos = D3DXVECTOR3(50.0f, 65.0f, -69.0f);
			break;
		}
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\billboard000.png", &m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 1, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, -5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(5.0f, -5.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================
//�I������
//======================
void CBillboard::Uninit()
{
	CBillboard::Uninit();
}

//======================
//�I������
//======================
void CBillboard::Update()
{

}

//======================
// �`�揈��
//======================
void CBillboard::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;

	////���C�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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

	for (int nCnt = 0; nCnt < MAX_BIL; nCnt++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_apBillboard[nCnt]->m_mtxWorld);

		//�r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����̐��ʂɌ���������
		D3DXMatrixInverse(&m_apBillboard[nCnt]->m_mtxWorld, NULL, &mtxView);	//�t�s������߂�

		m_apBillboard[nCnt]->m_mtxWorld._41 = 0.0f;
		m_apBillboard[nCnt]->m_mtxWorld._42 = 0.0f;
		m_apBillboard[nCnt]->m_mtxWorld._43 = 0.0f;

		D3DXMatrixTranslation(&mtxTrans, m_apBillboard[nCnt]->m_nPos.x, m_apBillboard[nCnt]->m_nPos.y, m_apBillboard[nCnt]->m_nPos.z);

		D3DXMatrixMultiply(&m_apBillboard[nCnt]->m_mtxWorld, &m_apBillboard[nCnt]->m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_apBillboard[nCnt]->m_mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		//�r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 0, 2);
	}

	//�A���t�@�e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	//=========================
	// �ǂ߂荞�ݖh�~�R�[�h
	//=========================

	////Z�̔�r���@�ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

	////Z�o�b�t�@�ɏ�������
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////���C�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//======================
// �I�u�W�F�N�g��������
//======================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBillboard* Billboard = new CBillboard;

	//�������ɐ��������ꍇ
	if (SUCCEEDED(Billboard->Init()))
	{
		//Billboard->Load();

		//Billboard->m_nPos = pos;

		//Billboard->m_nSize = size;
	}

	return Billboard;
}