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
    return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}