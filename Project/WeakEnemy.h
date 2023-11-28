////===========================================================================
////@brief �E�B�[�N�G�l�~�[�N���X/�p��
////===========================================================================
//
//#pragma once
//#include"DxLib.h"
//#include"EnemyBase.h"
//
//class Timer;
//class Animation;
//class StatusInit;
//
//class WeakEnemy :public EnemyBase
//{
//public:
//	WeakEnemy() {};							//�R���X�g���N�^
//	WeakEnemy(int _modelHandle);				//��������R���X�g���N�^
//	~WeakEnemy();							//�f�X�g���N�^
//
//	void Update(VECTOR _playerPos)override;	//�X�V
//	void Init()override;	//������
//	VECTOR Move(VECTOR playerPos)override;	//�ړ�
//private:
//	/*�萔*/
//	enum class AnimationType
//	{
//		RUN,        //����A�j���[�V����
//		ATTACK,		//�U���A�j���[�V����
//		IDLE,       //�ҋ@�A�j���[�V����
//		DEATH,      //���S�A�j���[�V����
//	};
//	/*�ÓI�萔*/
//	static constexpr float RADIUS		= 10.0f;	//���a
//	static constexpr int RANDOM_X_RANGE = -100;		//�G�̐������Ɍ��߂�X���W�͈̔�
//	static const VECTOR MODEL_SCALE;				//�������f���̊g�嗦
//	static const VECTOR MODEL_ROTATE;				//�������f���̉�]�l
//	/*���������֐�*/
//	void   Final();							//�ŏI����
//	double ChangeRotate(VECTOR playerPos);	//�p�x�̕ύX
//	/*�����o�ϐ�*/
//	Animation*	anim;					//�A�j���[�V�����N���X
//	StatusInit* statusInit;             //�X�e�[�^�X�������N���X
//	Timer*		invincibleTimer;		//���G����
//	Timer*		restTimeAfterAttack;	//�U����x�e����
//
//	int  attackAnimLoopCount;	//�U���Ǐ]�\����
//	bool isRestTime;			//�x�e�ɓ��邩�ǂ���
//};
//
//