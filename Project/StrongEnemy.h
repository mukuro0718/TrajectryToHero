//===========================================================================
//@brief �X�g�����O�G�l�~�[�N���X/�p��
//===========================================================================

#pragma once
#include"DxLib.h"
#include"EnemyBase.h"
class Timer;
class Animation;
class StrongEnemy :public EnemyBase
{
public:
	StrongEnemy(const VECTOR _spawnPos,const int modelHandle);	//��������R���X�g���N�^
	~StrongEnemy();					//�f�X�g���N�^

	void Update()override;	//�X�V
	void Init()override;	//������
	void Move(const VECTOR playerPos)override;	//�ړ�

private:
	//�萔
	enum class AnimationType
	{
		RUN,        //����A�j���[�V����
		ATTACK,		//�U���A�j���[�V����
		IDLE,       //�ҋ@�A�j���[�V����
		DEATH,      //���S�A�j���[�V����
	};
	static constexpr float  RADIUS		   = 10.0f;	//���a
	static constexpr int    RANDOM_X_RANGE = -100;	//�G�̐������Ɍ��߂�X���W�͈̔�
	static const	 VECTOR MODEL_SCALE;				//���f���̊g�嗦
	static const	 VECTOR MODEL_ROTATE;				//���f���̉�]�l
	//�N���X
	Animation* anim;								//�A�j���[�V�����N���X
	Timer* restTimeAfterAttack;						//�U����x�e����
	Timer* invincibleTimer;							//���G����
	//���������֐�
	float ChangeRotate(VECTOR playerPos);			//�p�x�̕ύX
	void Final();									//�ŏI����
	//�ϐ�
	int attackAnimLoopCount;//�U����
	bool isRestTime;		//�x�e�ɓ��邩�ǂ���
};


