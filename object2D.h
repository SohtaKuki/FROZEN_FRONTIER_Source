#ifndef _OBJECT_2D_H_
#define _OBJECT_2D_H_

#include "main.h"
#include "object.h"

class CObject2D :public CObject
{
public:
	CObject2D();
	~CObject2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

#endif
