#ifndef _BULLET_H_
#define _BULLET_H_


#include "object.h"
#include "object2D.h"
#include "player.h"


//�I�u�W�F�N�g2D�N���X
class CBullet :public CObject2D
{
public:
	CBullet();
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR3 size);
	D3DXVECTOR3 m_nBulletPos;
	D3DXVECTOR3 m_moveBullet;
	D3DXVECTOR3 m_rotBullet;
	D3DXVECTOR3 m_nBulletSize;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	int AnimationPTN;
	bool bUse;
	int m_CurrentFrame;           // ���݂̃t���[��
	int m_Numframes;        // �A�j���[�V�����̑��t���[����
	float m_FrameDuration; // �t���[���̕\������
	float m_Frametimer;        // �t���[���̌o�ߎ���
	float m_fLengthBullet; //�Ίp���̒���
	float m_fAngleBullet; //�Ίp���̊p�x
	float m_PolygonMoveSpeed;	// �|���S���̈ړ����x
	float m_PolygonPosX;	// �|���S������X���W
	float m_PolygonPosY;	// �|���S������Y���W
	CObject2D* m_apObject2D;
	CInputKeyboard* m_apInputKey;
protected:


};

#endif