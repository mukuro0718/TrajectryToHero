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

	void SetSpawnPos(const VECTOR _spawnPos) { spawnPos = _spawnPos; }
	const float GetRadius()const { return RADIUS; }
	const void NewStatus(const float _playerLv);

private:
	/*�萔*/
	enum class AnimationType
	{
		RUN,        //����A�j���[�V����
		ATTACK,		//�U���A�j���[�V����
		IDLE,       //�ҋ@�A�j���[�V����
		DEATH,      //���S�A�j���[�V����
	};
	/*�ÓI�萔*/
	static constexpr float	RADIUS		  = 10.0f;	//���a
	static constexpr float	HEIGHT		  = 30.0f;	//�J�v�Z���̍���
	static constexpr float	SPHERE_RADIUS = 3.0f;	//���̔��a
	static const	 VECTOR MODEL_SCALE;			//�������f���̊g�嗦
	static const	 VECTOR MODEL_ROTATE;			//�������f���̉�]�l
	static const	 int	CAPSULE_COLOR;			//�J�v�Z���̐F
	static const	 int	SPHERE_COLOR;			//���̐F

	/*���������֐�*/
	void   Create();						//�쐬
	void   Final();							//�ŏI����
	void   ChangeAnim();					//�A�j���[�V�����̕ύX
	double ChangeRotate(VECTOR playerPos);	//�p�x�̕ύX
	void   RandomWalk();//�����_���ɕ���
	
	/*�����o�ϐ�*/
	Animation* anim;								//�A�j���[�V�����N���X
	Timer* restTimeAfterAttack;						//�U����x�e����
	Timer* invincibleTimer;							//���G����
	Timer* preliminaryOperation;
	static constexpr int TOTAL_ANIM_NUM = 4;
	float animPlayTime[TOTAL_ANIM_NUM];
	int attackAnimLoopCount;//�U����
	bool isRestTime;		//�x�e�ɓ��邩�ǂ���
	bool isPreliminaryOperation;
	bool isRandomWalk;			//���Q���Ă��邩�ǂ���
	bool isRandomRest;			//���Q��A�x�e���Ă��邩�ǂ���
	VECTOR randomWalkTargetPos;	//���Q��ڕW���W
	Timer* randomRest;			//���Q�x�e����

};


