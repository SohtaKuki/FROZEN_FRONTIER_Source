//=================================================
//
// �|���S���̕`�揈�� (main.h)
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

static const int MAX_VERTEX = 4; //�ő咸�_

//�|���S���N���X
class CPolygon
{
public:

    //���_���[2D]�̍\���̂��`
    typedef struct
    {
        D3DXVECTOR3 pos;
        float rhw;
        D3DCOLOR col;
    }VERTEX_2D;

    CPolygon();//�R���X�g���N�^
    ~CPolygon();//�f�X�g���N�^
    void InitPolygon();//�|���S���̏�����
    void UninitPolygon();//�|���S���̏I������
    void UpdatePolygon();//�|���S���̍X�V
    void DrawPolygon();//�|���S���̕`��
private:

};

CPolygon::VERTEX_2D m_aVertex[MAX_VERTEX];

//�v���Z�X�N���X
class CProcess
{
public:
    CProcess();//�R���X�g���N�^
    ~CProcess();//�f�X�g���N�^
    HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow); //����������
    void Uninit(); //�I������
    void Update(); //�X�V����
    void Draw(); //�`�揈��
private:
    CPolygon* m_apPolygon;
};



#endif