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

//============================
//終了処理
//============================
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
            m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
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
    return ((m_aKeyStateRelease[nKey] & 0x80) != 0) ? false : true;
}

//============================
//コントローラーのコンストラクタ
//============================
CInputJoypad::CInputJoypad()
{

}

//============================
//コントローラーのデストラクタ
//============================
CInputJoypad::~CInputJoypad()
{

}

//============================
//コントローラーのデストラクタ
//============================
HRESULT CInputJoypad::Init()
{
    //メモリのクリア
    memset(&m_aKeyState, 0, sizeof(XINPUT_STATE));
    memset(&m_aKeyStateTrigger, 0, sizeof(XINPUT_STATE));

    //XInputのステート設定(有効にする)
    XInputEnable(true);

    // コントローラーの振動制御の0クリア
    ZeroMemory(&m_joykeyMoter, sizeof(XINPUT_VIBRATION));

    // 振動制御用の初期化
    m_Time = 0;
    m_Strength = 0;

    return S_OK;
}

//============================
//コントローラーの終了処理
//============================
void CInputJoypad::Uninit()
{
    //XInputのステートを設定
    XInputEnable(false);
}

//============================
//コントローラーの更新処理
//============================
void CInputJoypad::Update()
{
    XINPUT_STATE joykeystate; //コントローラーの入力情報

    //コントローラーの情報を取得
    if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
    {
        m_Button = m_joykeyState.Gamepad.wButtons;							//現在のボタンの情報を設定
        m_joykeyStateTrigger.Gamepad.wButtons = m_Button & ~m_OldButton;	//トリガーの情報を設定
        m_OldButton = m_joykeyState.Gamepad.wButtons;						//前回のボタンの情報を更新

        m_joykeyState = joykeystate; //コントローラーのプレス情報を保存

        // 振動
        m_joykeyMoter.wLeftMotorSpeed = m_Strength;		// 左側振動
        m_joykeyMoter.wRightMotorSpeed = m_Strength;	// 右側振動
        XInputSetState(0, &m_joykeyMoter);				// 振動情報送信

        // 振動時間の減算
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
//コントローラーのプレス情報を取得
//============================
bool CInputJoypad::GetPress(JOYKEY key)
{
    return m_joykeyState.Gamepad.wButtons & (0x01 << key);
}

//============================
//コントローラーのトリガー情報を取得
//============================
bool CInputJoypad::GetTrigger(JOYKEY key)
{
    return m_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key);
}