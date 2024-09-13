//=================================================
//
// �X�^�[�g�R�[��UI�\������ (startcallui.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _STARTCALLUI_H_
#define _STARTCALLUI_H_

#include "object2D.h"

//�}�N����`
#define NUM_ICON	(2)	//�A�C�R���̐�

class CStartCallUI : public CObject2D
{
public:
	//UI�\���\����
	typedef enum
	{
		ICON_SPDUP = 0,
		ICON_INSTANTSHOT,
		ICON_MAX,
	}ICONDISPLAY;

	//UI�\���\����
	typedef enum
	{
		UI_DISPLAY = 0,
		UI_HIDDEN,
		UI_MAX,
	}UIDISPLAY;

	CStartCallUI(int nPriority = 6);
	~CStartCallUI() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_ICON]);
	void SetAlpha(int nAlpha);
	static CStartCallUI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static bool DisplayStartCallUI(int nDisplayID, int DisplayOption);
	static bool GetStartStat() { return m_bStartComplete; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff[NUM_ICON];
	D3DXVECTOR3 m_nPos[NUM_ICON];
	D3DXVECTOR3 m_nSize[NUM_ICON];
	float m_aPosTexV[NUM_ICON];
	float m_aPosTexXV[NUM_ICON];
	static bool m_bUse[NUM_ICON];
	int m_nAlphaCnt;
	int m_nMissonAnim;
	bool m_bAlphaSwitch;
	bool m_bImageSwitch;
	static bool m_bStartComplete;
};

#endif

