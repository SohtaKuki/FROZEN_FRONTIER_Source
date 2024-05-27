//=================================================
//
// 弾の処理 (bullet.h)
// Author: Sohta Kuki
//
//=================================================


#ifndef _BULLET_H_
#define _BULLET_H_


#include "object.h"
#include "object2D.h"
#include "player.h"

//弾の速度
static const float BULLET_SPD = 6.0f;

//弾オブジェクトクラス
class CBullet : public CPlayer
{
public:
	static const int BULLET_SIZE = 30;
	static const int BULLET_LIFE = 80;

	CBullet();				
	~CBullet() override;	
	HRESULT Init() override;
	void Uninit() override;	
	void Update() override;	
	void Draw() override;	
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	D3DXVECTOR3& GetBulletPos() { return m_nPos; }

private:
	int m_nLife;	
	D3DXVECTOR3 m_nPos;
};

#endif