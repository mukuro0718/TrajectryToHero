//===========================================================================
//@brief �g�U����G�t�F�N�g�N���X
// �G�t�F�N�g�̏������ƈʒu�X�V�ƕ`����s��
//===========================================================================
#pragma once
#include<DxLib.h>
#include"EffectBase.h"

class SpreadEffect:public EffectBase
{
public:
	SpreadEffect(){}				//�R���X�g���N�^
	SpreadEffect(int _modelHandle);	//��������R���X�g���N�^
	~SpreadEffect();				//�f�X�g���N�^

	void Init(VECTOR _pos, VECTOR _direction)override;	//�X�V
	void Update()override;								//�X�V
private:
	/*�萔*/
	static constexpr int	SPHERE_RADIUS = 10;	//���̔��a
	static const	 int	SPHERE_COLOR;		//���̐F
	static const	 VECTOR SPHERE_SCALE;		//���̃T�C�Y
	/*�ϐ�*/
	VECTOR initPos;	//�����`����W
};