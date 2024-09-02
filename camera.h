//=================================================
//
// �J�������� (camera.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�����I�u�W�F�N�g�N���X
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera();
	static void SetShake(int shakeframe,float shake);
private:
	D3DXVECTOR3 m_posV;	//���_
	D3DXVECTOR3 m_posR;	//�����_
	D3DXVECTOR3 m_vecU;	//������x�N�g��
	D3DXVECTOR3 m_rot;	//��]
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	static int m_nShakeframe;
	static float m_fShake;
	float m_fStartPos; //�t�H�O�̊J�n�n�_
	float m_fEndPos; //�t�H�O�̏I���n�_
	float m_fFogDisity; //�t�H�O�̖��x
	float m_fDistance;
	
};

#endif
