//=================================================
//
// �I�u�W�F�N�g�̏��� (object.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "manager.h"

//�I�u�W�F�N�g�N���X
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
		ENEMY,
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
	static unsigned const int MAX_OBJECT = 1024;	//�I�u�W�F�N�g�ő吔
	static CObject* GetObject(int nIdx);
	TYPE GetType();
	void SetType(TYPE type);
protected:
	void Release();

private:
	static CObject* m_apObject[MAX_OBJECT];	//�I�u�W�F�N�g�Ǘ�
	TYPE m_type;
	static int m_nNumAll;	//�I�u�W�F�N�g�̑���
	int m_nID;	// �������g��ID
};

#endif
