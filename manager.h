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
#include "camera.h"
#include "light.h"

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
	static CCamera* GetCamera();
	static CLight* GetLight();
private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pKeyboard;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
};

#endif