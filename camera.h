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
private:
	D3DXVECTOR3 m_posV;	//���_
	D3DXVECTOR3 m_posR;	//�����_
	D3DXVECTOR3 m_vecU;	//������x�N�g��
	D3DXVECTOR3 m_rot;	//��]
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	float m_fDistance;
};

#endif
