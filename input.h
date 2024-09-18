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

//�L�[�{�[�h���͏���
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

//�R���g���[���[����
class CInputJoypad : public CInput
{
public:

	//�L�[�̎��
	typedef enum
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_LB,
		JOYKEY_RB,
		JOYKEY_LT,
		JOYKEY_RT,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	}JOYKEY;

	//�X�e�B�b�N�̔ԍ�
	typedef enum
	{
		STICKTYPE_LEFT = 0, // L3�X�e�B�b�N
		STICKTYPE_RIGHT,	// R3�X�e�B�b�N
		STICKTYPE_MAX
	}STICKTYPE;

	//�X�e�B�b�N�̕���
	typedef enum
	{
		STICKANGLE_UP = 0, // ��
		STICKANGLE_DOWN,   // ��
		STICKANGLE_LEFT,   // ��
		STICKANGLE_RIGHT,  // �E
		STICKANGLE_MAX,
	}STICKANGLE;

	//�X�e�B�b�N�֘A�̓���
	typedef struct
	{
		float afTplDiameter[STICKTYPE_MAX];
		float afAngle[STICKTYPE_MAX];
		bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];
		bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];
		bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];
		bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];
	}STICKINPUT;

	//��{����
	CInputJoypad();
	~CInputJoypad();
	HRESULT Init(void);
	void Uninit() override;
	void Update() override;
	D3DXVECTOR2 GetStickPosition(STICKTYPE stickType);
	bool GetStickTrigger(STICKTYPE stickType, STICKANGLE angle);

	//�L�[�̓��͏�Ԃ�Ԃ�
	bool GetPress(JOYKEY key);		//�v���X��Ԏ擾
	bool GetTrigger(JOYKEY key);	//�g���K�[��Ԃ��擾

private:

	//�����o�ϐ�
	BYTE m_aKeyState[NUM_KEY_MAX];				
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];		
	int m_KeyPressCount;						
	int m_JoyKeyPressCount;						
	XINPUT_STATE m_joykeyState;					
	XINPUT_STATE m_joykeyStateTrigger;			
	int m_Time;									
	WORD m_Strength;							
	D3DXVECTOR3 m_joykeyStickPos;				
	bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX];
	DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; 
	DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX];
	STICKINPUT m_stick;					
	XINPUT_STATE m_XInput;				
	XINPUT_STATE m_joykeyStateRelease;
	XINPUT_STATE m_joykeyCurrentTime;
	XINPUT_STATE m_joykeyExecLastTime;
	XINPUT_STATE m_joykeyInput;			
	XINPUT_VIBRATION m_joykeyMoter;		
	WORD m_Button;						
	WORD m_OldButton;					
};


#endif