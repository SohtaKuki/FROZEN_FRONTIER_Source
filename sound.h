//=================================================
//
// �T�E���h�֌W���� (sound.h)
// Author: Sohta Kuki (Base code by AKIRA TANAKA)
//
//=================================================

#ifndef _SOUND_H_ 
#define _SOUND_H_


#include "main.h"

//�T�E���h�N���X
class CSound
{
public:
	//�T�E���h�񋓌^
	typedef enum
	{
		SOUND_LABEL_BGM = 0,
		SOUND_LABEL_MAX,
	}SOUND_LABEL;

	//�����o�֐�
	CSound();							
	~CSound();							
	HRESULT Init(HWND hWnd);			
	void Uninit(void);					
	HRESULT PlaySound(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);		
	void Stop(void);					
private:
	IXAudio2* m_pXAudio2 = NULL;							
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;		
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};				
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};				
};

#endif