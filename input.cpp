//=================================================
//
// 入力処理 (input.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "input.h"

LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//============================
//コンストラクタ
//============================
CInput::CInput()
{

}

//============================
//デストラクタ
//============================
CInput::~CInput()
{

}

//============================
//初期化処理
//============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
    if (m_pInput == nullptr)
    {
        //DirectInputオブジェクトの生成
        if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
        {
            return E_FAIL;
        }
    }
    return S_OK;
}

void CInput::Uninit()
{
    //入力デバイス(キーボード)の破棄
    if (m_pDevKeyboard != NULL)
    {
        m_pDevKeyboard->Unacquire();
        m_pDevKeyboard->Release();
        m_pDevKeyboard = NULL;
    }

    //DirectInputオブジェクトの破棄
    if (m_pInput != NULL)
    {
        m_pInput->Release();
        m_pInput = NULL;
    }
}

//============================
//コンストラクタ
//============================
CInputKeyboard::CInputKeyboard()
{
    //LPDIRECTINPUTDEVICE8 g_pDevKeyboard = nullptr;
}

//============================
//デストラクタ
//============================
CInputKeyboard::~CInputKeyboard()
{

}

//============================
//キーボードの初期化処理
//============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
    CInput::Init(hInstance, hWnd);

    //入力デバイス(キーボード)の生成
    if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, nullptr)))
    {
        return E_FAIL;
    }

    //データフォーマットを設定
    if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
    {
        return E_FAIL;
    }

    //協調レベルを設定
    if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
    {
        return E_FAIL;
    }

    //キーボードへのアクセス権取得
    m_pDevKeyboard->Acquire();

    return S_OK;
}

//============================
//キーボードの終了処理
//============================
void CInputKeyboard::Uninit(void)
{
    CInput::Uninit();
}

//============================
//キーボードの更新処理
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
//キーボードのプレス情報を取得
//============================
bool CInputKeyboard::GetPress(int nKey)
{
    return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//============================
//キーボードのプレス情報を取得
//============================
bool CInputKeyboard::GetTrigger(int nKey)
{
    return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//============================
//キーボードのプレス情報を取得
//============================
bool CInputKeyboard::GetRelease(int nKey)
{
    return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}