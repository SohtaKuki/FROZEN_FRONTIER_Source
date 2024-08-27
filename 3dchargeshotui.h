//=================================================
//
// 2Dポリゴンの描画処理 (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _CHARGESHOTUI_H_
#define _CHARGESHOTUI_H_

#include "object.h"
#include "object2D.h"

//背景オブジェクトクラス
class CChargeshotui :public CObject2D
{
public:
	CChargeshotui();
	~CChargeshotui()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CChargeshotui* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	static bool DisplayShotOKUI();
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	static bool m_bUse;
	int m_nDisplaytime; //表示している時間
	int m_nAlpha; //テクスチャ透明度
};

#endif

