////===========================================================================
////@brief �{�X�G�l�~�[�N���X/�p��
////===========================================================================
//#pragma once
//#include"DxLib.h"
//#include"EnemyBase.h"
//class Timer;
//class Animation;
//class StatusInit;
//
//class Boss :public EnemyBase
//{
//public:
//	Boss() {};				//�R���X�g���N�^
//	Boss(int _modelHandle);//��������R���X�g���N�^
//	~Boss();				//�f�X�g���N�^
//
//	void   Update(VECTOR _playerPos)override;		//�X�V
//	void   Init  ()override;	//������
//	VECTOR Move  (VECTOR _playerPos)override;		//�ړ�
//private:
//	//�萔
//	enum class AnimationType//�A�j���[�V����
//	{
//		WALK,
//		NORMAL_ATTACK,	//�ʏ�U���A�j���[�V����
//		ROTATE_ATTACK,	//�ʏ�U���A�j���[�V����
//		JUMP_ATTACK,	//�W�����v�U���A�j���[�V����
//		JUMP_IDLE,		//�W�����v��ҋ@�A�j���[�V����
//		IDLE,			//�ҋ@�A�j���[�V����
//		DEATH,			//���S�A�j���[�V����
//	};
//	static constexpr float	RADIUS		   = 10.0f;	//���a
//	static constexpr int	RANDOM_X_RANGE = -100;	//�G�̐������Ɍ��߂�X���W�͈̔�
//	static const	 VECTOR MODEL_SCALE;			//���f���̊g�嗦
//	static const	 VECTOR MODEL_ROTATE;			//���f���̉�]�l
//	static const	 VECTOR INIT_POS;				//�������W
//	//�N���X
//	Animation*	anim;						//�A�j���[�V�����N���X
//	Timer*		invincibleTimer;			//���G���ԃN���X
//	Timer*		restTimeAfterAttack;		//�U����x�e���ԃN���X
//	StatusInit* statusInit;					//�X�e�[�^�X�������N���X
//	//���������֐�
//	float ChangeRotate(VECTOR _playerPos);	//�p�x�̕ύX
//	void  Final();							//�ŏI����
//	//�ϐ�
//	int  attackAnimLoopCount;	//�U���A�j���[�V�������[�v����
//	bool isRestTime;			//�x�e�ɓ��邩�ǂ���
//	VECTOR jumpAttackTargetPos;//�W�����v�A�^�b�N���̖ڕW���W
//	Timer* waitBeforeJunpAttack;//�W�����v�U���ҋ@����
//	Timer* waitBeforeRotateAttack;//��]�U���ҋ@����
//	Timer* rotateAttackLoopTime;//��]�U�����[�v����
//	bool isJumpAttack;//�W�����v�A�^�b�N�������邩�ǂ����itrue:������ false:�����Ȃ��j
//	bool isRotateAttack;//�W�����v�A�^�b�N�������邩�ǂ����itrue:������ false:�����Ȃ�
//	int attackType;//�U���̃^�C�v
//	bool isJumpIdle;//�W�����v�A�C�h���A�j���[�V�������Đ����Ă��邩�ǂ���(true:�Đ����Ă��� false:�Đ����Ă��Ȃ�)
//
//
//};
//
//
