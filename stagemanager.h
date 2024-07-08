//=================================================
//
// ステージマネージャー処理 (stagemanager.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_

#include "main.h"

class CStageManager
{
public:
	CStageManager();
	virtual ~CStageManager();
	static HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
private:
};

#endif