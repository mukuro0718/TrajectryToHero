//===========================================================================
//@brief �g�U����G�t�F�N�g�N���X
// �����Ԃ����o��
//===========================================================================
#pragma once
#include<DxLib.h>

class BloodParticle
{
public:
	BloodParticle();				//�R���X�g���N�^
	~BloodParticle();				//�f�X�g���N�^

private:
	/*�萔*/
	static constexpr int	SPHERE_RADIUS = 10;	//���̔��a
	static const	 int	SPHERE_COLOR;		//���̐F
	static const	 VECTOR SPHERE_SCALE;		//���̃T�C�Y
	/*�ϐ�*/
	VECTOR initPos;	//�����`����W
};