#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

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