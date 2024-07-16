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
		NONE = 0,
		ENEMY, //�G(2DObject�p)
		ENEMY_XMOVE, //�G(X���W�ړ�)
		ENEMY_ZMOVE, //�G(Z���W�ړ�)
		START, //�X�^�[�g�}�[�J�[
		GOAL, //�S�[���}�[�J�[
		PLAYER, //�v���C���[
		BLOCK, //�u���b�N
		BROKENBLOCK, //�j��\�u���b�N
		WALL_WIDTH, //�� (����)
		WALL_HEIGHT, //�� (�c��)
		WALL_WIDTH_SHORT,//�� (�����V���[�g)
		WALL_HEIGHT_SHORT, //��(�c���V���[�g)
		D2DITEM, //2DObject�p�A�C�e��
		ITEM_WALKSPDUP, //�v���C���[�����A�C�e��(�ړ����x�㏸)
		ITEM_INSTANTSHOT,//�v���C���[�����A�C�e��(�`���[�W�V���b�g������)
		ITEM_ADDTIMER, //�^�C�}�[�ǉ��A�C�e��
		TIMER, //�^�C�}�[
		FADE, //�t�F�[�h
		D2DBULLET, //2D�p�v���C���[�e
		PLAYER_BULLET, //�v���C���[�ʏ�e
		CHBULLET, //�v���C���[����e(�`���[�W�V���b�g)
		ENEMY_BULLET, //�G�ʏ�e
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
	void Release();

private:
	static CObject* m_apObject[MAX_PRIORITY][MAX_OBJECT];	//�I�u�W�F�N�g�Ǘ�
	TYPE m_type;
	static int m_nNumAll;	//�I�u�W�F�N�g�̑���
	int m_nID;	// �������g��ID
	int m_nPriority;
};

#endif
