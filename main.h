//=================================================
//
// ポリゴンの描画処理 (main.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _MAIN_H_
#define _MAIN_H_


#include <windows.h>
#include "d3dx9.h"

#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")

static const int SCREEN_WIDTH(1280);
static const int SCREEN_HEIGHT(720);
static const int FVF_VERTEX_2D(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

static const int MAX_VERTEX = 4; //最大頂点

//ポリゴンクラス
class CPolygon
{
public:

    //頂点情報[2D]の構造体を定義
    typedef struct
    {
        D3DXVECTOR3 pos;
        float rhw;
        D3DCOLOR col;
    }VERTEX_2D;

    CPolygon();//コンストラクタ
    ~CPolygon();//デストラクタ
    void InitPolygon();//ポリゴンの初期化
    void UninitPolygon();//ポリゴンの終了処理
    void UpdatePolygon();//ポリゴンの更新
    void DrawPolygon();//ポリゴンの描画
private:

};

CPolygon::VERTEX_2D m_aVertex[MAX_VERTEX];

//プロセスクラス
class CProcess
{
public:
    CProcess();//コンストラクタ
    ~CProcess();//デストラクタ
    HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow); //初期化処理
    void Uninit(); //終了処理
    void Update(); //更新処理
    void Draw(); //描画処理
private:
    CPolygon* m_apPolygon;
};



#endif