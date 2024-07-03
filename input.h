//=================================================
//
// ���͏����ɕK�v�ȃw�b�_�[�t�@�C�� (input.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"


//�}�N����`
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

//���̓N���X
class CInput
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;
protected:
	static LPDIRECTINPUT8 m_pInput; //DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;
};

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
};

#endif