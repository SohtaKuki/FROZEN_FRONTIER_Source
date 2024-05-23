//=================================================
//
// ポリゴン描画のマネージャー管理 (manager.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "input.h"

//マネージャクラス
class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer* GetRenderer();
	static CInputKeyboard* GetKeyboard();
private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pKeyboard;
};

#endif