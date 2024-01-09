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
	BloodParticleBase(const int _imageHandle);//�R���X�g���N�^
	~BloodParticleBase();//�f�X�g���N�^
	void Init(const VECTOR _targetDir, const VECTOR _targetPos);//������
	void Update();//�X�V
	void Draw();//�`��
private:
	/*�ÓI�萔*/
	enum class Sign
	{
		PLUS,//�v���X
		MINUS,//�}�C�i�X
	};
	static constexpr float Y_DEG = 150.0f;//Y����]�x��
	static constexpr float Z_DEG = 45.0f;//z����]�x��
	static constexpr int SIGN_RANGE = 1;//�����͈̔�
	static constexpr int RANDOM_SPEED_RANGE = 10;//�����_���ŏo���X�s�[�h�͈̔�
	static constexpr int RANDOM_DIR_RANGE = 10;
	static constexpr int RANDOM_SCALE_RANGE = 5;//�����_���ŏo���X�P�[���͈̔�
	static constexpr int MAX_ALPHA = 255;
	static constexpr int ALPHA_REDUCED_VALUE = 10;
	static constexpr float GRAVITY = 0.5f;//�d��
	/*���������֐�*/
	void SetScale();						//�X�P�[���̐ݒ�
	void SetSpeed();						//�����̐ݒ�
	void SetMoveDir();	//�����̐ݒ�
	float ReturnRandomFloatValue(const int _range, const bool _useSign);//�w�肵�������_���͈͂Ő������o��
	/*�����o�ϐ�*/
	VECTOR moveDir;		//�ړ�����(�P�ʃx�N�g���ɂ���)
	VECTOR pos;			//���W	
	float scale;		//�g�嗦
	float  speed;		//�p�[�e�B�N���̔�ԑ���
	int imageHandle;	//�摜�n���h��
	int alpha;//�A���t�@
};
//class BloodParticleBase
//{
//public:
//	BloodParticleBase(){}//�R���X�g���N�^
//	BloodParticleBase(const int _imageHandle);//�R���X�g���N�^
//	~BloodParticleBase();//�f�X�g���N�^
//	void Init(const VECTOR _targetDir, const VECTOR _targetPos);//������
//	void Update();//�X�V
//	void Draw();//�`��
//private:
//	/*�ÓI�萔*/
//	enum class Sign
//	{
//		PLUS,//�v���X
//		MINUS,//�}�C�i�X
//	};
//	static constexpr float Y_DEG = 150.0f;//Y����]�x��
//	static constexpr float Z_DEG = 45.0f;//z����]�x��
//	static constexpr int SIGN_RANGE = 1;//�����͈̔�
//	static constexpr int RANDOM_DEG_RANGE = 30;//�����_���ŏo���p�x�͈̔�
//	static constexpr int RANDOM_SPEED_RANGE = 10;//�����_���ŏo���X�s�[�h�͈̔�
//	static constexpr int RANDOM_SCALE_RANGE = 3;//�����_���ŏo���X�P�[���͈̔�
//	static constexpr int MAX_ALPHA = 255;
//	static constexpr int ALPHA_REDUCED_VALUE = 10;
//	static constexpr float GRAVITY = 0.098f;//�d��
//	/*���������֐�*/
//	void SetScale();						//�X�P�[���̐ݒ�
//	void SetSpeed();						//�����̐ݒ�
//	void SetDir(const VECTOR _targetDir);	//�����̐ݒ�
//	float ReturnRandomFloatValue(const int _range,const bool _useSign);//�w�肵�������_���͈͂Ő������o��
//	/*�����o�ϐ�*/
//	VECTOR particleDir;	//�p�[�e�B�N���̕���(�P�ʃx�N�g���ɂ���)
//	VECTOR moveDir;		//�ړ�����(�P�ʃx�N�g���ɂ���)
//	VECTOR pos;			//���W	
//	float scale;		//�g�嗦
//	float  speed;		//�p�[�e�B�N���̔�ԑ���
//	int imageHandle;	//�摜�n���h��
//	int alpha;//�A���t�@
//};

