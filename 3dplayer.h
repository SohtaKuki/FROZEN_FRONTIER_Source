//=================================================
//
// 3Dモデルのプレイヤーの表示処理 (3dplayer.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _3DPLAYER_H_
#define _3DPLAYER_H_

#include "object3D.h"
#include "objectX.h"

#define MAX_CHAR (256) //行の読み込む数
#define NUM_MODEL (16) //モデルの数

static const float PLAYER_MOVE_SPD = 0.7f; //プレイヤーの移動速度
static const float PLAYER_MOVE_BOOST = 1.2f; //プレイヤーの移動速度上昇の倍率

//オブジェクト3Dクラス
class C3dplayer : public CModel
{
public:

	typedef struct
	{
		char filename[MAX_CHAR];
		int index;
		int parent;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;

	}LoadEnemy;

	//モデルの構造体
	typedef struct
	{

		D3DXMATRIX mtxworld;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		LPDIRECT3DTEXTURE9 m_pTexture;
		int nLife;
		bool bUse;
		int nCounterState;
		int nIdxModelParent;	//親モデルのインデックス

	}ModelPartsEnemy;

	C3dplayer(int nPriority = 3);
	~C3dplayer() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//void SetPlayerPos();
	static C3dplayer* Create(D3DXVECTOR3 pos);
	//void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	static HRESULT Load();
	static void Unload();
	void PlayerDamage(int nDamage);
	void LoadPlayerData();
	//void OldPlayerPos() { m_nPos = m_nOld3DPlayerPos; }
	//void OldPlayerPosZ() { m_nPos.z = m_nOld3DPlayerPos.z; }
	static int GetPlayerLife() {return m_nLife ; }
	D3DXVECTOR3& GetPlayerPos() { return m_nOld3DPlayerPos; }//座標の取得
private:
	D3DXMATRIX m_mtxworld;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nOld3DPlayerPos;
	D3DXVECTOR3 m_nSize;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh[NUM_MODEL];
	LPD3DXBUFFER m_pBuffMat[NUM_MODEL];
	DWORD m_nNumMat[NUM_MODEL];
	//Enemy m_aEnemy;
	LoadEnemy m_aLoadEnemy[NUM_MODEL];
	ModelPartsEnemy m_aModel[NUM_MODEL];
	bool bUse;
	DWORD m_bAButtonPressStartTime;
	bool m_bAButtonPressed;
	FILE* m_pFile;//ファイルポインタを宣言
	bool m_bPlayerBuff;
	bool m_bInstantShot;
	int m_nBuffTime;
	int m_nInstantShotTime;
	int m_KeyStart;
	static int m_nLife;
protected:
	D3DXVECTOR3 m_n3DPlayerMove;
	D3DXVECTOR3 m_rot;

};

#endif