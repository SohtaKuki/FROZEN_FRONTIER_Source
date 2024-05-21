#ifndef _OBJECT_2D_H_
#define _OBJECT_2D_H_


#include "object.h"

static const int IMAGE_PATTERN_ANIM(8);  //�A�j���̃p�^�[����
static const int DELAY_ANIM (20);//�A�j���̑ҋ@����

class CObject2D :public CObject
{
public:
	CObject2D();
	~CObject2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	int AnimationPTN;
	bool bUse;
	int m_CurrentFrame = 0;           // ���݂̃t���[��
	int m_Numframes = 8;        // �A�j���[�V�����̑��t���[����
	float m_FrameDuration = 0.5f; // �t���[���̕\������
	float m_Frametimer = 0.0f;        // �t���[���̌o�ߎ���
};

#endif
