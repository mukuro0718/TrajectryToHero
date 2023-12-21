//===========================================================================
//@brief �����Ԃ��p�[�e�B�N���N���X
// �U���̕��������ƂɌ����Ԃ��̕��������߂�
// ���̕��������ƂɁA�����_���Ȋp�x�Ői�ޕ��������߂�
// Billboard���g�p���ĉ摜��`�悷��
// �摜�̓����_���Ŋg��k��������
// �ʒu�X�V�̑��x�������_���ő���������
// �d�͂���
//===========================================================================
#pragma once
#include<DxLib.h>
class BloodParticleBase
{
public:
	BloodParticleBase();//�R���X�g���N�^
	~BloodParticleBase();//�f�X�g���N�^
	void Init(const VECTOR _targetDir);//������
	void Update();//�X�V
private:
	/*�ÓI�萔*/
	static constexpr float Y_DEG = 90.0f;//Y����]�x��
	static constexpr float Z_DEG = 45.0f;//z����]�x��
	static constexpr int RANDOM_OFFSET_RANGE = 30;//�����_���ŏo���I�t�Z�b�g�͈̔�
	static constexpr int RANDOM_SPEED_RANGE = 5;//�����_���ŏo���X�s�[�h�͈̔�
	static constexpr int RANDOM_SCALE_RANGE = 10;//�����_���ŏo���X�P�[���͈̔�
	/*���������֐�*/
	void SetScale();						//�X�P�[���̐ݒ�
	void SetSpeed();						//�����̐ݒ�
	void SetDir(const VECTOR _targetDir);	//�����̐ݒ�
	/*�����o�ϐ�*/
	VECTOR particleDir;	//�p�[�e�B�N���̕���(�P�ʃx�N�g���ɂ���)
	VECTOR moveDir;		//�ړ�����(�P�ʃx�N�g���ɂ���)
	VECTOR pos;			//���W	
	VECTOR scale;		//�g�嗦
	float  speed;		//�G�t�F�N�g�̔�ԑ���
};

