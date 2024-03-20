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
	BloodParticleBase(const int _imageHandle);	//�R���X�g���N�^
	virtual ~BloodParticleBase();				//�f�X�g���N�^

	const void Init(const VECTOR _targetDir, const VECTOR _targetPos);	//������
	const void Update();	//�X�V
	const void Draw();		//�`��
private:
	/*�ÓI�萔*/
	enum class Sign
	{
		PLUS,//�v���X
		MINUS,//�}�C�i�X
	};
	static constexpr float	Y_DEG				= 150.0f;//Y����]�x��
	static constexpr float	Z_DEG				= 45.0f	;//z����]�x��
	static constexpr float	GRAVITY				= 0.065f;//�d��
	static constexpr int	RANDOM_SPEED_RANGE	= 5		;//�����_���ŏo���X�s�[�h�͈̔�
	static constexpr int	RANDOM_SCALE_RANGE	= 5		;//�����_���ŏo���X�P�[���͈̔�
	static constexpr int	ALPHA_REDUCED_VALUE = 5		;//�A���t�@�����l
	static constexpr int	RANDOM_DIR_RANGE	= 10	;//�p�x�͈̔�
	static constexpr int	SIGN_RANGE			= 1		;//�����͈̔�
	static constexpr int	MAX_ALPHA			= 255	;//�ő�A���t�@�l
	/*���������֐�*/
	const void  SetScale();	//�X�P�[���̐ݒ�
	const void  SetSpeed();	//�����̐ݒ�
	const void  SetMoveDir();//�����̐ݒ�
	const float ReturnRandomFloatValue(const int _range, const bool _useSign);//�w�肵�������_���͈͂Ő������o��
	/*�����o�ϐ�*/
	VECTOR	moveDir;		//�ړ�����(�P�ʃx�N�g���ɂ���)
	VECTOR	pos;			//���W	
	float	scale;			//�g�嗦
	float	speed;			//�p�[�e�B�N���̔�ԑ���
	bool	isUpdateGrav;	//�d�͂��g�p���邩
	int		imageHandle;	//�摜�n���h��
	int		alpha;			//�A���t�@
	int		framecount;		//�t���[����
};