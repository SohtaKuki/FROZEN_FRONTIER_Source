//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "object.h"
#include "object2D.h"

static const int CP_IMAGE_PATTERN_ANIM(8);  //�A�j���̃p�^�[����
static const int CP_DELAY_ANIM(20);//�A�j���̑ҋ@����

static const float Angle_value1(0.25f); //�|���S���p�x����(�l1)
static const float Angle_value2(0.75f); //�|���S���p�x����(�l2)
static const float Angle_value3(0.35f); //�|���S���p�x���� (�l3)
static const float Length_value1(3.0f); //�|���S���������� (�l1)
static const float Length_value2(0.0f); //�|���S���������� (�l2)
static const float Attenuation_value(0.10f); //�|���S���ړ��ʌ����W��

//�I�u�W�F�N�g2D�N���X
class CPlayer :public CObject2D
{
public:
	CPlayer();
	~CPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	D3DXVECTOR3 m_nPlayerPos;

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	int AnimationPTN;
	bool bUse;
	int m_CurrentFrame;           // ���݂̃t���[��
	int m_Numframes;        // �A�j���[�V�����̑��t���[����
	float m_FrameDuration; // �t���[���̕\������
	float m_Frametimer;        // �t���[���̌o�ߎ���
	float m_fLengthPlayer; //�Ίp���̒���
	float m_fAnglePlayer; //�Ίp���̊p�x
	float m_PolygonMoveSpeed;	// �|���S���̈ړ����x
	float m_PolygonPosX;	// �|���S������X���W
	float m_PolygonPosY;	// �|���S������Y���W
	CObject2D* m_apObject2D;
	CInputKeyboard* m_apInputKey;
protected:
	D3DXVECTOR3 m_movePlayer;
	D3DXVECTOR3 m_rotPlayer;
	D3DXVECTOR3 m_nPlayerSize;
	
};

#endif
