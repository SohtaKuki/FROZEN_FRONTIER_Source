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
	void LoadStageData();
	static CStageManager* Create();
	const static int MAX_OBJ = 1000;
private:
	FILE* m_pFile;//ファイルポインタを宣言
	D3DXVECTOR3 m_nPos[MAX_OBJ];
};

#endif