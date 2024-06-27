//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _PLAYER_HPBAR_H_
#define _PLAYER_HPBAR_H_

#include "object.h"
#include "object2D.h"

//�w�i�I�u�W�F�N�g�N���X
class CPlayerHpBar :public CObject2D
{
public:
	CPlayerHpBar(int nPriority = 6);
	~CPlayerHpBar()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CPlayerHpBar* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	bool bUse;
	int m_CurrentFrame = 0;           // ���݂̃t���[��
	int m_Numframes = 8;        // �A�j���[�V�����̑��t���[����
	float m_FrameDuration = 0.5f; // �t���[���̕\������
	float m_Frametimer = 0.0f;        // �t���[���̌o�ߎ���
};

#endif

