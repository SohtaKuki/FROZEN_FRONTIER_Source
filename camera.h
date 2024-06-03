//=================================================
//
// カメラ処理 (camera.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//爆発オブジェクトクラス
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();
private:
	D3DXVECTOR3 m_posV;	//視点
	D3DXVECTOR3 m_posR;	//注視点
	D3DXVECTOR3 m_vecU;	//上方向ベクトル
	D3DXVECTOR3 m_rot;	//回転
	D3DXMATRIX m_mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス
	float m_fDistance;
};

#endif
