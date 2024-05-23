#ifndef _BULLET_H_
#define _BULLET_H_


#include "object.h"
#include "object2D.h"
#include "player.h"


class CBullet : public CObject2D
{
public:

	//定数の初期化
	static const int BULLET_SIZE = 30;
	static const int BULLET_LIFE = 120;

	//メンバ関数
	CBullet();					//コンストラクタ
	~CBullet() override;		//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//弾の生成

private:
	int m_Life;					//寿命
};

#endif