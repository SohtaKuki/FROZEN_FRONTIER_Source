#ifndef _TITLEBG_H_
#define _TITLEBG_H_

#include "object2D.h"

//É}ÉNÉçíËã`
#define NUM_BG	(6)	//îwåiÇÃêî

class CTitleBG : public CObject2D
{
public:
	CTitleBG(int nPriority = 3);
	~CTitleBG() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_BG]);
	static CTitleBG* Create();
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff[NUM_BG];
	D3DXVECTOR3 m_nPos[NUM_BG];
	float m_aPosTexV[NUM_BG];
	float m_aPosTexXV[NUM_BG];
};

#endif

