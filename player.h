//=================================================
//
// 2Dポリゴンの描画処理 (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "object.h"

static const int CP_IMAGE_PATTERN_ANIM(8);  //アニメのパターン数
static const int CP_DELAY_ANIM(20);//アニメの待機時間

//オブジェクト2Dクラス
class CPlayer :public CObject
{
public:
	CPlayer();
	~CPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	int AnimationPTN;
	bool bUse;
	int m_CurrentFrame = 0;           // 現在のフレーム
	int m_Numframes = 8;        // アニメーションの総フレーム数
	float m_FrameDuration = 0.5f; // フレームの表示時間
	float m_Frametimer = 0.0f;        // フレームの経過時間
};

#endif
