//=================================================
//
// �|���S���̕`�揈�� (main.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <Windows.h>
#include"d3dx9.h"

#include "renderer.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

static const int SCREEN_WIDTH(1280); //��ʉ𑜓x�i���j
static const int SCREEN_HEIGHT(720);//��ʉ𑜓x�i�����j
static const int FVF_VERTEX_2D(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

#endif

