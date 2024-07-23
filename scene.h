//=================================================
//
// 画面遷移処理 (scene.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

class CScene
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	}MODE;
	CScene();
	virtual ~CScene();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CScene* Create(MODE mode);
	
private:
	MODE m_mode;
};

class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};

class CGame : public CScene
{
public:
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};



class CResult : public CScene
{
public:
	CResult();
	~CResult();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};


#endif