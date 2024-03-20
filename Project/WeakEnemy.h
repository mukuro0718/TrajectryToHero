//===========================================================================
//@brief �E�B�[�N�G�l�~�[�N���X/�p��
//===========================================================================

#pragma once
#include"DxLib.h"
#include"EnemyBase.h"

class Timer;
class Animation;


class WeakEnemy :public EnemyBase
{
public:
	WeakEnemy(const VECTOR _spawnPos,const int _modelHandle);				//��������R���X�g���N�^
	~WeakEnemy();							//�f�X�g���N�^

	const void Update()override;						//�X�V
	const void Init()override;							//������
	const void Move(const VECTOR _playerPos)override;	//�ړ�
	const void NewStatus(const float _playerLv);		//�V�����X�e�[�^�X�����߂�

	const void SetSpawnPos(const VECTOR _spawnPos) { spawnPos = _spawnPos; }//�X�|�[���ʒu�����߂�
	/*getter*/
	const float GetRadius()const { return RADIUS; }
private:
	/*�萔*/
	enum class AnimationType
	{
		RUN,			//����A�j���[�V����
		COMBO_ATTACK,	//�U���A�j���[�V����
		NORMAL_ATTACK,	//�U���A�j���[�V����
		IDLE,			//�ҋ@�A�j���[�V����
		DEATH,			//���S�A�j���[�V����
		WALK,			//����
		FRIGHTENING,	//���݃A�j���[�V����
	};
	enum class AttackType
	{
		COMBO_ATTACK,		//�U���A�j���[�V����
		NORMAL_ATTACK,
	};
	/*�ÓI�萔*/
	static constexpr int TOTAL_ANIM_NUM	   = 7;		//�A�j���[�V�����̍��v
	static constexpr float	RADIUS		   = 10.0f;	//���a
	static constexpr float	HEIGHT		   = 30.0f;	//�J�v�Z���̍���
	static constexpr float	SPHERE_RADIUS  = 3.0f;	//���̔��a

	static const	 VECTOR MODEL_SCALE;	//�������f���̊g�嗦
	static const	 VECTOR MODEL_ROTATE;	//�������f���̉�]�l
	static const	 int	CAPSULE_COLOR;	//�J�v�Z���̐F
	static const	 int	SPHERE_COLOR;	//���̐F

	/*���������֐�*/
	void   Create();								//�쐬
	void   Delete();								//�ŏI����
	void   ChangeAnim();							//�A�j���[�V�����̕ύX
	void   RandomWalk();							//�����_���ɕ���
	double ChangeRotate(const VECTOR _playerPos);	//�p�x�̕ύX

	/*�����o�ϐ�*/
	Animation*	anim;					//�A�j���[�V�����N���X
	Timer*		invincibleTimer;		//���G����
	Timer*		restTimeAfterAttack;	//�U����x�e����

	float animPlayTime[TOTAL_ANIM_NUM];	//�A�j���[�V�����Đ�����
	int  attackAnimLoopCount;			//�U���Ǐ]�\����
	bool isRestTime;					//�x�e�ɓ��邩�ǂ���
	bool isWalk;						//�����Ă��邩
	bool isRandomWalk;					//�����_���ňړ����Ă��邩
	bool isRandomRest;					//�����_���ړ���ɋx�e���Ă��邩
	int attackType;						//�U���̎��
	VECTOR randomWalkTargetPos;			//�����_���ŕ�������
	Timer* randomRest;					//�����_���x�e����

};


