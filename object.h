//=================================================
//
// オブジェクトの処理 (object.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "manager.h"

//オブジェクトクラス
class CObject
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	}VERTEX_2D;

	typedef enum
	{
		NONE= 0,
		BULLET,
		ENEMY,
		MAX_TYPE,
	}TYPE;

	CObject();
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();	
	static unsigned const int MAX_OBJECT = 1024;	//オブジェクト最大数
	static CObject* GetObj(int nIdx);
	TYPE GetType() { return m_type; }
	void SetType(TYPE type);
protected:
	void Release();

private:
	static CObject* m_apObject[MAX_OBJECT];	//オブジェクト管理
	TYPE m_type;
	static int m_nNumAll;	//オブジェクトの総数
	int m_nID;	// 自分自身のID
};

#endif
