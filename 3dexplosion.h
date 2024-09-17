//=================================================
//
// �r���{�[�h�`�掮�e�̃w�b�_�[�t�@�C�� (3dexplosion.h)
// Author: Sohta Kuki
//
//=================================================
#ifndef _3D_EXPLOSION_H_	
#define _3D_EXPLOSION_H_	

#include "object3D.h"

//�I�u�W�F�N�g2D�N���X
class C3dexplosion :public CObject3D
{
public:
	static const int BULLET_SPD = 6;
	static const int EXPLOSION_PATTERN_ANIM = 8;  //�����A�j���̃p�^�[����
	static const int DELAY_ANIM = 4;//�A�j���̑ҋ@����
	C3dexplosion(int nPriority = 3);
	~C3dexplosion() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);
	static C3dexplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int type);
	D3DXVECTOR3& GetBulletPos() { return m_nPos; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	int m_nLife;
	int m_nType;
	int m_nCounterAnim;
	int m_nPatternAnimExpl;
	bool m_bUse;

};

#endif