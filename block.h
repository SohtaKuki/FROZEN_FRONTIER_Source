//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "object.h"
#include "object2D.h"


//�I�u�W�F�N�g2D�N���X
class CBlock :public CObject2D
{
public:
	typedef enum
	{
		NONE = 0,
		NORMAL,
		ITEM,
		GOAL,
		MAX_TYPE,
	}BLOCKTYPE;

	CBlock(int nPriority = 3);
	~CBlock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Damage();
	HRESULT Load();
	static void Unload();
	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nBlockType);
	static unsigned const int MAX_BLOCK = 1024;	//�I�u�W�F�N�g�ő吔
	static unsigned const int PLAYER_HEIGHT = 50;
	static unsigned const int PLAYER_WIDTH = 50;
	static unsigned const int BLOCK_SIZE = 4000;
	static unsigned const int BLOCK_COLIDTC_X = 40;
	static unsigned const int BLOCK_COLIDTC_Y = 40;
	void SetPos(D3DXVECTOR3 pos);
	bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	int m_nLife;
	int m_nBlockType;
	bool bUse;
	float m_fLengthBlock; //�Ίp���̒���
	float m_fAngleBlock; //�Ίp���̊p�x
	float m_PolygonMoveSpeed;	// �|���S���̈ړ����x
	D3DXVECTOR3 m_moveBlock;
	D3DXVECTOR3 m_rotBlock;
	D3DXVECTOR3 m_nBlockSize;
	static LPDIRECT3DTEXTURE9 m_pTexTemp;

};

#endif
