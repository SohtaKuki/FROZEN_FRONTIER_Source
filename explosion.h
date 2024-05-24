//=================================================
//
// 2Dポリゴンの描画処理 (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_


#include "object.h"
#include "object2D.h"

static const int EXPL_IMAGE_PATTERN_ANIM(8);  //アニメのパターン数
static const int EXPL_DELAY_ANIM(20);//アニメの待機時間

static const float EXPL_Angle_value1(0.25f); //ポリゴン角度調整(値1)
static const float EXPL_Angle_value2(0.75f); //ポリゴン角度調整(値2)
static const float EXPL_Angle_value3(0.35f); //ポリゴン角度調整 (値3)
static const float EXPL_Length_value1(3.0f); //ポリゴン長さ調整 (値1)
static const float EXPL_Length_value2(0.0f); //ポリゴン長さ調整 (値2)
static const float EXPL_Attenuation_value(0.10f); //ポリゴン移動量減衰係数

//オブジェクト2Dクラス
class CExplosion :public CObject2D
{
public:
	CExplosion();
	~CExplosion()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CExplosion* Create(D3DXVECTOR3 pos);
	D3DXVECTOR3& GetExplosionPos() { return m_nExplosionPos; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	int AnimationPTN;
	bool bUse;
	int m_CurrentFrame;           // 現在のフレーム
	int m_Numframes;        // アニメーションの総フレーム数
	float m_FrameDuration; // フレームの表示時間
	float m_Frametimer;        // フレームの経過時間
	float m_fLengthExplosion; //対角線の長さ
	float m_fAngleExplosion; //対角線の角度
	float m_PolygonMoveSpeed;	// ポリゴンの移動速度
	float m_PolygonPosX;	// ポリゴン初期X座標
	float m_PolygonPosY;	// ポリゴン初期Y座標
	D3DXVECTOR3 m_nExplosionPos;
protected:
	D3DXVECTOR3 m_moveExplosion;
	D3DXVECTOR3 m_rotExplosion;
	D3DXVECTOR3 m_nExplosionSize;

};

#endif