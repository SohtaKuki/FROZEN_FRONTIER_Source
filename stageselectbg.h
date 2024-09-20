//=================================================
//
// �^�C�g����ʂ̔w�i���� (titlebg.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _STAGESELECTBG_H_
#define _STAGESELECTBG_H_

#include "object2D.h"

//�}�N����`
#define NUM_BG	(4)	//�w�i�̐�

class CStageSelectBG : public CObject2D
{
public:
	CStageSelectBG(int nPriority = 3);
	~CStageSelectBG() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_BG]);
	static CStageSelectBG* Create();
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff[NUM_BG];
	D3DXVECTOR3 m_nPos[NUM_BG];
	float m_aPosTexV[NUM_BG];
	float m_aPosTexXV[NUM_BG];
};

#endif

