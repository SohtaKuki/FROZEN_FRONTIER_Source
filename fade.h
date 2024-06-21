//=================================================
//
// 画面遷移時のフェード処理 (fade.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _FADE_H_
#define _FADE_H_

#include "scene.h"

//ゲームクラス
class CFade
{
public:

	//定数
	static const int FADE_TIME = 90;

	//フェードの列挙型
	typedef enum
	{
		FADE_NONE = 0,
		FADE_OUT,	
		FADE_IN,		
		FADE_MAX,		
	}FADE;

	//メンバ関数
	CFade();	
	~CFade();	
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void SetAlpha(float falpha);
	static void SetFade(CScene::MODE mode);

private:
	
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	float m_fAlpha;						
	static FADE m_FadeState;			
	static bool m_bEndFade;				
	static CScene::MODE m_Mode;			
};


#endif