//=================================================
//
// �e�̏��� (bullet.h)
// Author: Sohta Kuki
//
//=================================================


#ifndef _BULLET_H_
#define _BULLET_H_


#include "object.h"
#include "object2D.h"
#include "player.h"

//�e�̑��x
static const float BULLET_SPD = 6.0f;

//�e�I�u�W�F�N�g�N���X
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