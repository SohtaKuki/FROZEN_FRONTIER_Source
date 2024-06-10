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

	//���_���[3D]�̍\���̂��`
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;

	}VERTEX_3D;

	typedef enum
	{
		NONE= 0,
		BULLET,
		ENEMY,
		PLAYER,
		BLOCK,
		ITEM,
		START,
		MAX_TYPE,
	}TYPE;

	CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static unsigned const int MAX_OBJECT = 1024;	//�I�u�W�F�N�g�ő吔
	static CObject* GetObj(int nPriority ,int nIdx);
	TYPE GetType() { return m_type; }
	void SetType(TYPE type);
protected:
	void Release();

private:
	static CObject* m_apObject[MAX_PRIORITY][MAX_OBJECT];	//�I�u�W�F�N�g�Ǘ�
	TYPE m_type;
	static int m_nNumAll;	//�I�u�W�F�N�g�̑���
	int m_nID;	// �������g��ID
	int m_nPriority;
};

#endif
