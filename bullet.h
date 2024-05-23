#ifndef _BULLET_H_
#define _BULLET_H_


#include "object.h"
#include "object2D.h"
#include "player.h"


class CBullet : public CObject2D
{
public:

	//�萔�̏�����
	static const int BULLET_SIZE = 30;
	static const int BULLET_LIFE = 120;

	//�����o�֐�
	CBullet();					//�R���X�g���N�^
	~CBullet() override;		//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�e�̐���

private:
	int m_Life;					//����
};

#endif