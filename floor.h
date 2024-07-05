//=================================================
//
// ���̕`�揈�� (floor.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "object.h"
#include "object3D.h"


#define FLOOR_SIZE (2000.0f)

//�I�u�W�F�N�g2D�N���X
class CFloor : public CObject3D
{
public:
	CFloor(int nPriority = 3);
	~CFloor() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);
	static CFloor* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load();
	static void Unload();
	void SetPos(D3DXVECTOR3 pos);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	D3DXMATRIX m_mtxWorld;
	bool bUse;
protected:
	D3DXVECTOR3 m_nMove;
	D3DXVECTOR3 m_rot;
};

#endif
