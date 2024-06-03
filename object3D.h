//=================================================
//
// 3Dポリゴンの描画処理 (object3D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _OBJECT_3D_H_
#define _OBJECT_3D_H_

#include "object.h"
#include "input.h"

#define FIELD_SIZE (500.0f)

//オブジェクト2Dクラス
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);
	static CObject3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos) { m_nPos = pos; }
	static HRESULT Load();
	static void Unload();
	D3DXVECTOR3& GetPos() { return m_nPos; }
	D3DXVECTOR3& GetSize() { return m_nSize; }		//サイズの取得
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	D3DXMATRIX m_mtxWorld;
	int AnimationPTN;
	bool bUse;
protected:
	D3DXVECTOR3 m_nMove;
	D3DXVECTOR3 m_rot;
};

#endif
