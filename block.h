//=================================================
//
// 2Dポリゴンの描画処理 (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "object.h"
#include "object2D.h"


//オブジェクト2Dクラス
class CBlock :public CObject2D
{
public:
	CBlock();
	~CBlock()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Damage();
	HRESULT Load();
	static void Unload();
	static CBlock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3& GetBlockPos() { return m_nBlockPos; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	int m_nLife;
	bool bUse;
	float m_fLengthBlock; //対角線の長さ
	float m_fAngleBlock; //対角線の角度
	float m_PolygonMoveSpeed;	// ポリゴンの移動速度
	D3DXVECTOR3 m_moveBlock;
	D3DXVECTOR3 m_rotBlock;
	D3DXVECTOR3 m_nBlockSize;
	D3DXVECTOR3 m_nBlockPos;
	static LPDIRECT3DTEXTURE9 m_pTexTemp;

};

#endif
