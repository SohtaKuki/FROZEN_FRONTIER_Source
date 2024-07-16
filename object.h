//=================================================
//
// オブジェクトの処理 (object.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "manager.h"

//オブジェクトクラス
class CObject
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	}VERTEX_2D;

	//頂点情報[3D]の構造体を定義
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;

	}VERTEX_3D;

	typedef enum
	{
		NONE = 0,
		ENEMY, //敵(2DObject用)
		ENEMY_XMOVE, //敵(X座標移動)
		ENEMY_ZMOVE, //敵(Z座標移動)
		START, //スタートマーカー
		GOAL, //ゴールマーカー
		PLAYER, //プレイヤー
		BLOCK, //ブロック
		BROKENBLOCK, //破壊可能ブロック
		WALL_WIDTH, //壁 (横長)
		WALL_HEIGHT, //壁 (縦長)
		WALL_WIDTH_SHORT,//壁 (横長ショート)
		WALL_HEIGHT_SHORT, //壁(縦長ショート)
		D2DITEM, //2DObject用アイテム
		ITEM_WALKSPDUP, //プレイヤー強化アイテム(移動速度上昇)
		ITEM_INSTANTSHOT,//プレイヤー強化アイテム(チャージショット即発射)
		ITEM_ADDTIMER, //タイマー追加アイテム
		TIMER, //タイマー
		FADE, //フェード
		D2DBULLET, //2D用プレイヤー弾
		PLAYER_BULLET, //プレイヤー通常弾
		CHBULLET, //プレイヤー特殊弾(チャージショット)
		ENEMY_BULLET, //敵通常弾
		MAX_TYPE,
	}TYPE;

	CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static unsigned const int MAX_OBJECT = 1024;	//オブジェクト最大数
	static CObject* GetObj(int nPriority ,int nIdx);
	TYPE GetType() { return m_type; }
	void SetType(TYPE type);
	void Release();

private:
	static CObject* m_apObject[MAX_PRIORITY][MAX_OBJECT];	//オブジェクト管理
	TYPE m_type;
	static int m_nNumAll;	//オブジェクトの総数
	int m_nID;	// 自分自身のID
	int m_nPriority;
};

#endif
