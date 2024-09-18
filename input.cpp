//=================================================
//
// ���͏��� (input.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "input.h"

LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//============================
//�R���X�g���N�^
//============================
CInput::CInput()
{

}

//============================
//�f�X�g���N�^
//============================
CInput::~CInput()
{

}

//============================
//����������
//============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
    if (m_pInput == nullptr)
    {
        //DirectInput�I�u�W�F�N�g�̐���
        if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
        {
            return E_FAIL;
        }
    }
    return S_OK;
}

//============================
//�I������
//============================
void CInput::Uninit()
{
    //���̓f�o�C�X(�L�[�{�[�h)�̔j��
    if (m_pDevKeyboard != NULL)
    {
        m_pDevKeyboard->Unacquire();
        m_pDevKeyboard->Release();
        m_pDevKeyboard = NULL;
    }

    //DirectInput�I�u�W�F�N�g�̔j��
    if (m_pInput != NULL)
    {
        m_pInput->Release();
        m_pInput = NULL;
    }
}

//============================
//�R���X�g���N�^
//============================
CInputKeyboard::CInputKeyboard()
{
    //LPDIRECTINPUTDEVICE8 g_pDevKeyboard = nullptr;
}

//============================
//�f�X�g���N�^
//============================
CInputKeyboard::~CInputKeyboard()
{

}

//============================
//�L�[�{�[�h�̏���������
//============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
    CInput::Init(hInstance, hWnd);

    //���̓f�o�C�X(�L�[�{�[�h)�̐���
    if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, nullptr)))
    {
        return E_FAIL;
    }

    //�f�[�^�t�H�[�}�b�g��ݒ�
    if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
    {
        return E_FAIL;
    }

    //�������x����ݒ�
    if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
    {
        return E_FAIL;
    }

    //�L�[�{�[�h�ւ̃A�N�Z�X���擾
    m_pDevKeyboard->Acquire();

    return S_OK;
}

//============================
//�L�[�{�[�h�̏I������
//============================
void CInputKeyboard::Uninit(void)
{
    CInput::Uninit();
}

//============================
//�L�[�{�[�h�̍X�V����
//============================
void CInputKeyboard::Update(void)
{

    BYTE aKeyState[NUM_KEY_MAX];
    int nCntKey;

    if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
    {
        for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
        {
            m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
            m_aKeyState[nCntKey] = aKeyState[nCntKey];
            m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
        }
    }
    else
    {
        m_pDevKeyboard->Acquire();
    }
}

//============================
//�L�[�{�[�h�̃v���X�����擾
//============================
bool CInputKeyboard::GetPress(int nKey)
{
    return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//============================
//�L�[�{�[�h�̃v���X�����擾
//============================
bool CInputKeyboard::GetTrigger(int nKey)
{
    return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//============================
//�L�[�{�[�h�̃v���X�����擾
//============================
bool CInputKeyboard::GetRelease(int nKey)
{
    return ((m_aKeyStateRelease[nKey] & 0x80) != 0) ? false : true;
}

//============================
//�R���g���[���[�̃R���X�g���N�^
//============================
CInputJoypad::CInputJoypad()
{

}

//============================
//�R���g���[���[�̃f�X�g���N�^
//============================
CInputJoypad::~CInputJoypad()
{

}

//============================
//�R���g���[���[�̃f�X�g���N�^
//============================
HRESULT CInputJoypad::Init()
{
    //�������̃N���A
    memset(&m_aKeyState, 0, sizeof(XINPUT_STATE));
    memset(&m_aKeyStateTrigger, 0, sizeof(XINPUT_STATE));

    //XInput�̃X�e�[�g�ݒ�(�L���ɂ���)
    XInputEnable(true);

    // �R���g���[���[�̐U�������0�N���A
    ZeroMemory(&m_joykeyMoter, sizeof(XINPUT_VIBRATION));

    // �U������p�̏�����
    m_Time = 0;
    m_Strength = 0;

    return S_OK;
}

//============================
//�R���g���[���[�̏I������
//============================
void CInputJoypad::Uninit()
{
    //XInput�̃X�e�[�g��ݒ�
    XInputEnable(false);
}

//============================
//�R���g���[���[�̍X�V����
//============================
void CInputJoypad::Update()
{
    XINPUT_STATE joykeystate; //�R���g���[���[�̓��͏��

    //�R���g���[���[�̏����擾
    if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
    {
        m_Button = m_joykeyState.Gamepad.wButtons;							//���݂̃{�^���̏���ݒ�
        m_joykeyStateTrigger.Gamepad.wButtons = m_Button & ~m_OldButton;	//�g���K�[�̏���ݒ�
        m_OldButton = m_joykeyState.Gamepad.wButtons;						//�O��̃{�^���̏����X�V

        m_joykeyState = joykeystate; //�R���g���[���[�̃v���X����ۑ�

        // �U��
        m_joykeyMoter.wLeftMotorSpeed = m_Strength;		// �����U��
        m_joykeyMoter.wRightMotorSpeed = m_Strength;	// �E���U��
        XInputSetState(0, &m_joykeyMoter);				// �U����񑗐M

        // �U�����Ԃ̌��Z
        if (m_Time > 0)
        {
            m_Time--;
        }
        else
        {
            m_Time = 0;
            m_Strength = 0;
        }
    }
}

//============================
//�R���g���[���[�̃v���X�����擾
//============================
bool CInputJoypad::GetPress(JOYKEY key)
{
    return m_joykeyState.Gamepad.wButtons & (0x01 << key);
}

//============================
//�R���g���[���[�̃g���K�[�����擾
//============================
bool CInputJoypad::GetTrigger(JOYKEY key)
{
    return m_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key);
}

//============================
// �X�e�B�b�N��X���AY���̒l���擾�i�͈͂�-32768�`32767�j
//============================
D3DXVECTOR2 CInputJoypad::GetStickPosition(STICKTYPE stickType)
{
    D3DXVECTOR2 stickPos = { 0.0f, 0.0f };

    if (stickType == STICKTYPE_LEFT)
    {
        stickPos.x = m_joykeyState.Gamepad.sThumbLX / 32768.0f; // -1.0�`1.0�ɐ��K��
        stickPos.y = m_joykeyState.Gamepad.sThumbLY / 32768.0f; // -1.0�`1.0�ɐ��K��
    }
    else if (stickType == STICKTYPE_RIGHT)
    {
        stickPos.x = m_joykeyState.Gamepad.sThumbRX / 32768.0f; // -1.0�`1.0�ɐ��K��
        stickPos.y = m_joykeyState.Gamepad.sThumbRY / 32768.0f; // -1.0�`1.0�ɐ��K��
    }

    // �X�e�B�b�N�̃f�b�h�]�[���̐ݒ�
    const float deadZone = 0.2f;
    if (fabs(stickPos.x) < deadZone) stickPos.x = 0.0f;
    if (fabs(stickPos.y) < deadZone) stickPos.y = 0.0f;

    return stickPos;
}

//============================
// �X�e�B�b�N�̃g���K�[������擾
//============================
bool CInputJoypad::GetStickTrigger(STICKTYPE stickType, STICKANGLE angle)
{
    D3DXVECTOR2 stickPos = GetStickPosition(stickType); // �X�e�B�b�N�̌��݂̈ʒu���擾

    bool triggered = false;
    const float threshold = 0.5f; // �X�e�B�b�N�̓��͂��L���ƌ��Ȃ�臒l

    // �X�e�B�b�N�̕����𔻒�
    if (stickType == STICKTYPE_LEFT)
    {
        // ������̃g���K�[����
        if (angle == STICKANGLE_UP && stickPos.y > threshold && !m_stick.abAnglePress[STICKTYPE_LEFT][STICKANGLE_UP])
        {
            triggered = true;
            m_stick.abAnglePress[STICKTYPE_LEFT][STICKANGLE_UP] = true;
        }
        // �������̃g���K�[����
        else if (angle == STICKANGLE_DOWN && stickPos.y < -threshold && !m_stick.abAnglePress[STICKTYPE_LEFT][STICKANGLE_DOWN])
        {
            triggered = true;
            m_stick.abAnglePress[STICKTYPE_LEFT][STICKANGLE_DOWN] = true;
        }
        // �������̃g���K�[����
        else if (angle == STICKANGLE_LEFT && stickPos.x < -threshold && !m_stick.abAnglePress[STICKTYPE_LEFT][STICKANGLE_LEFT])
        {
            triggered = true;
            m_stick.abAnglePress[STICKTYPE_LEFT][STICKANGLE_LEFT] = true;
        }
        // �E�����̃g���K�[����
        else if (angle == STICKANGLE_RIGHT && stickPos.x > threshold && !m_stick.abAnglePress[STICKTYPE_LEFT][STICKANGLE_RIGHT])
        {
            triggered = true;
            m_stick.abAnglePress[STICKTYPE_LEFT][STICKANGLE_RIGHT] = true;
        }
    }
    else if (stickType == STICKTYPE_RIGHT)
    {
        // ���l�ɉE�X�e�B�b�N�̕������������
        if (angle == STICKANGLE_UP && stickPos.y > threshold && !m_stick.abAnglePress[STICKTYPE_RIGHT][STICKANGLE_UP])
        {
            triggered = true;
            m_stick.abAnglePress[STICKTYPE_RIGHT][STICKANGLE_UP] = true;
        }
        else if (angle == STICKANGLE_DOWN && stickPos.y < -threshold && !m_stick.abAnglePress[STICKTYPE_RIGHT][STICKANGLE_DOWN])
        {
            triggered = true;
            m_stick.abAnglePress[STICKTYPE_RIGHT][STICKANGLE_DOWN] = true;
        }
        else if (angle == STICKANGLE_LEFT && stickPos.x < -threshold && !m_stick.abAnglePress[STICKTYPE_RIGHT][STICKANGLE_LEFT])
        {
            triggered = true;
            m_stick.abAnglePress[STICKTYPE_RIGHT][STICKANGLE_LEFT] = true;
        }
        else if (angle == STICKANGLE_RIGHT && stickPos.x > threshold && !m_stick.abAnglePress[STICKTYPE_RIGHT][STICKANGLE_RIGHT])
        {
            triggered = true;
            m_stick.abAnglePress[STICKTYPE_RIGHT][STICKANGLE_RIGHT] = true;
        }
    }

    // �g���K�[���������Ȃ������ꍇ�A���Z�b�g����
    if (fabs(stickPos.x) < threshold && fabs(stickPos.y) < threshold)
    {
        m_stick.abAnglePress[stickType][angle] = false;
    }

    return triggered;
}
