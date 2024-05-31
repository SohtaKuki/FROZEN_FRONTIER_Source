//=================================================
//
// 弾の処理 (bullet.h)
// Author: Sohta Kuki
//
//=================================================


#ifndef _ITEM_H_
#define _ITEM_H_


#include "object.h"
#include "object2D.h"
#include "player.h"

//弾オブジェクトクラス
class CItem : public CPlayer
{
public:
	static const int BULLET_SIZE = 30;
	static const int BULLET_LIFE = 80;
	static const int ENEMY_HITPOINT = 50;

	CItem(int nPriority = 6);
	~CItem() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	int m_nLife;
};

#endif