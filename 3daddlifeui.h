//=================================================
//
// �`���[�W�V���b�g�[�U����UI�\������(3dchargeshotui.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _ADDLIFEUI_H_
#define _ADDLIFEUI_H_

#include "object.h"
#include "object2D.h"

//�w�i�I�u�W�F�N�g�N���X
class CAddlifeui :public CObject2D
{
public:
	CAddlifeui();
	~CAddlifeui()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CAddlifeui* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	static bool DisplayAddLifeUI();
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	static bool m_bUse;
	int m_nDisplaytime; //�\�����Ă��鎞��
	int m_nAlpha; //�e�N�X�`�������x
};

#endif

