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


//�e�I�u�W�F�N�g�N���X
class CBullet : public CPlayer
{
public:
	static const int BULLET_SIZE = 30;
	static const int BULLET_LIFE = 120;

	CBullet();				
	~CBullet() override;	
	HRESULT Init() override;
	void Uninit() override;	
	void Update() override;	
	void Draw() override;	
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	int m_Life;	
};

#endif