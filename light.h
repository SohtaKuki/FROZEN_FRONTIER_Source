//=================================================
//
// ���C�g���� (light.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"


#define MAX_LIGHT (4)

//�����I�u�W�F�N�g�N���X
class CLight
{
public:
	CLight();
	~CLight();
	HRESULT Init();
	void Uninit();
	void Update();

private:
	D3DLIGHT9 m_alight[MAX_LIGHT];
};

#endif