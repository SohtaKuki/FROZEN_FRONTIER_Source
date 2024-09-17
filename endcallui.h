//=================================================
//
// �X�^�[�g�R�[��UI�\������ (startcallui.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _ENDCALLUI_H_
#define _ENDCALLUI_H_

#include "object2D.h"

//�}�N����`
#define NUM_ICON	(2)	//�A�C�R���̐�

class CEndCallUI : public CObject2D
{
public:
	//UI�\���\����
	typedef enum
	{
		ICON_SUCCESS = 0,
		ICON_FAILED,
		ICON_MAX,
	}ICONDISPLAY;

	//UI�\���\����
	typedef enum
	{
		UI_DISPLAY = 0,
		UI_HIDDEN,
		UI_MAX,
	}UIDISPLAY;

	CEndCallUI(int nPriority = 6);
	~CEndCallUI() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_ICON]);
	void SetAlpha(int nAlpha);
	static CEndCallUI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static bool DisplayEndCallUI(int nDisplayID, int DisplayOption);
	static bool GetEndStat() { return m_bEndComplete; }
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
	static bool m_bEndComplete;
};

#endif

