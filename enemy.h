//=================================================
//
// 2Dポリゴンの描画処理 (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "object.h"
#include "object2D.h"


//オブジェクト2Dクラス
class CEnemy :public CObject2D
{
public:
	CEnemy();
	~CEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	D3DXVECTOR3& GetEnemyPos() { return m_nEnemyPos; }
	static const int CP_IMAGE_PATTERN_ANIM = 8;  //アニメのパターン数
	static const int CP_DELAY_ANIM = 20;//アニメの待機時間

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	int AnimationPTN;
	bool bUse;
	int m_CurrentFrame;           // 現在のフレーム
	int m_Numframes;        // アニメーションの総フレーム数
	float m_FrameDuration; // フレームの表示時間
	float m_Frametimer;        // フレームの経過時間
	float m_fLengthEnemy; //対角線の長さ
	float m_fAngleEnemy; //対角線の角度
	float m_PolygonMoveSpeed;	// ポリゴンの移動速度
	float m_PolygonPosX;	// ポリゴン初期X座標
	float m_PolygonPosY;	// ポリゴン初期Y座標
	D3DXVECTOR3 m_moveEnemy;
	D3DXVECTOR3 m_rotEnemy;
	D3DXVECTOR3 m_nEnemySize;
	D3DXVECTOR3 m_nEnemyPos;

};

#endif
