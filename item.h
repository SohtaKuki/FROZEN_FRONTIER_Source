//=================================================
//
// �A�C�e���̏��� (item.h)
// Author: Sohta Kuki
//
//=================================================


#ifndef _ITEM_H_
#define _ITEM_H_


#include "object.h"
#include "object2D.h"
#include "player.h"

//�A�C�e���I�u�W�F�N�g�N���X
class CItem : public CPlayer
{
public:
	static const int PLAYER_HITPOINT = 50;

	CItem(int nPriority = 6);
	~CItem() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
};

#endif