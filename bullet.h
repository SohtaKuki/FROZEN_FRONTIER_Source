#ifndef _BULLET_H_
#define _BULLET_H_


#include "object.h"
#include "object2D.h"
#include "player.h"


//オブジェクト2Dクラス
class CBullet :public CObject2D
{
public:
	CBullet();
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 size);
	D3DXVECTOR3 m_nBulletPos;
	D3DXVECTOR3 m_moveBullet;
	D3DXVECTOR3 m_rotBullet;
	D3DXVECTOR3 m_nBulletSize;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	int AnimationPTN;
	bool bUse;
	int m_CurrentFrame;           // 現在のフレーム
	int m_Numframes;        // アニメーションの総フレーム数
	float m_FrameDuration; // フレームの表示時間
	float m_Frametimer;        // フレームの経過時間
	float m_fLengthBullet; //対角線の長さ
	float m_fAngleBullet; //対角線の角度
	float m_PolygonMoveSpeed;	// ポリゴンの移動速度
	float m_PolygonPosX;	// ポリゴン初期X座標
	float m_PolygonPosY;	// ポリゴン初期Y座標
	CObject2D* m_apObject2D;
	CInputKeyboard* m_apInputKey;
protected:


};

#endif