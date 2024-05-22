//=================================================
//
// �|���S���`��̃}�l�[�W���[�Ǘ� (manager.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//�}�l�[�W���N���X
class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer* GetRenderer();
private:
	static CRenderer* m_pRenderer;
};

#endif