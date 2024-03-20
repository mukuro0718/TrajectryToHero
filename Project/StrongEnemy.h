//===========================================================================
//@brief �X�g�����O�G�l�~�[�N���X/�p��
// ���@�ōU��������
//===========================================================================

#pragma once
#include"DxLib.h"
#include"EnemyBase.h"
class Timer;
class Animation;
class Explosion;

class StrongEnemy :public EnemyBase
{
public:
	StrongEnemy(const VECTOR _spawnPos,const int modelHandle);	//��������R���X�g���N�^
	~StrongEnemy();												//�f�X�g���N�^

	const void Update()override;						//�X�V
	const void Init()override;							//������
	const void Move(const VECTOR playerPos)override;	//�ړ�

	const void DrawAttackRange();				//�U���͈͂̕`��
	const void NewStatus(const float _playerLv);//�V�����X�e�[�^�X�̐ݒ�
	const void DrawMagicSphere();				//���@�w�̕`��
	/*getter/setter*/
	const float GetRadius()const { return RADIUS; }
	void SetSpawnPos(const VECTOR _spawnPos) { spawnPos = _spawnPos; }
private:
	/*�萔*/
	enum class AnimationType
	{
		RUN,        //����A�j���[�V����
		HOMING,		//�z�[�~���O���@
		EXPLOSION,  //�������@
		IDLE,       //�ҋ@�A�j���[�V����
		DEATH,      //���S�A�j���[�V����
	};
	enum class AttackType
	{
		HOMING_MAGIC,
		EXPROSION_MAGIC
	};
	/*�ÓI�萔*/
	static constexpr int			MAGIC_CIRCLE_VERTEX_NUM					= 4;		//���@�w�p�|���S�����_��
	static constexpr int			MAGIC_CIRCLE_POLYGON_NUM				= 2;		//���@�w�p�|���S����
	static constexpr int			TOTAL_ANIM_NUM							= 5;		//�A�j���[�V������
	static constexpr int			HOMING_MAGIC_VERTEX_NUM					= 9;		//�z�[�~���O���@�p���_��
	static constexpr int			HOMING_MAGIC_POLYGON_NUM				= 12;		//�|���S����
	static constexpr int			BEFORE_HOMING_MAGIC_WAIT_FRAME_COUNT	= 80;		//�U���O�ҋ@����
	static constexpr int			AFTER_HOMING_MAGIC_WAIT_FRAME_COUNT		= 120;		//�U����ҋ@����
	static constexpr float			MAX_EXPLOSION_MAGIC_RADIUS				= 50.0f;	//�������@�ő唼�a
	static constexpr float			BEFORE_EXPLOSION_MAGIC_WAIT_FRAME_COUNT = 100;		//�U���O�ҋ@�J�E���g
	static constexpr float			RADIUS									= 8.0f;		//���a
	static constexpr float			HEIGHT									= 30.0f;	//�J�v�Z���̍���
	static constexpr float			SPHERE_RADIUS							= 10.0f;	//���̔��a
	static constexpr unsigned short MAGIC_CIRCLE_INDEX[MAGIC_CIRCLE_POLYGON_NUM * 3] =	//�|���S���C���f�b�N�X
	{
		0, 1, 2,
		0, 2, 3,
	};
	static constexpr unsigned short HOMING_MAGIC_INDEX[HOMING_MAGIC_POLYGON_NUM * 3] =	//�|���S���C���f�b�N�X
	{
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,1,
		1,4,8,
		1,8,5,
		2,1,5,
		2,5,6,
		3,2,6,
		3,6,7,
		4,3,7,
		4,7,8,
	};
	static const VERTEX3D INIT_MAGIC_CIRCLE_VERTEX;									//�������p���_
	static const VERTEX3D INIT_VERTEX_FOR_HOMING_MAGIC;								//�������p���_
	static const VECTOR	  VERTEX_OFFSET_FOR_HOMING_MAGIC[HOMING_MAGIC_VERTEX_NUM];	//���@��\�����邽�߂̒��_�␳�l
	static const VECTOR	  MODEL_SCALE;												//�������f���̊g�嗦
	static const VECTOR   MODEL_ROTATE;												//�������f���̉�]�l
	static const VECTOR   MAGIC_CIRCLE_VERTEX_OFFSET[MAGIC_CIRCLE_VERTEX_NUM];		//���@�w���_�␳�l
	static const VECTOR   MAGIC_CIRCLE_VERTEX_OFFSET_2[MAGIC_CIRCLE_VERTEX_NUM];	//���@�w���_�␳�l
	static const int	  CAPSULE_COLOR;											//�J�v�Z���̐F
	static const int	  HOMING_MAGIC_COLOR;										//�z�[�~���O���@�̐F
	static const int	  EXPLOSION_MAGIC_COLOR;									//�������@�̐F
	/*���������֐�*/
	void	Create();						//�쐬
	void	Final();						//�ŏI����
	void	ChangeAnim();					//�A�j���[�V�����̕ύX
	double	ChangeRotate(VECTOR playerPos);	//�p�x�̕ύX
	void	RandomWalk();					//�����_���ɕ���
	void	Attack(const VECTOR _playerPos);//�U��
	/*�����o�ϐ�*/
	Animation*	anim;				//�A�j���[�V�����N���X
	Explosion*	explosion;			//�������@
	Timer*		restTimeAfterAttack;//�U����x�e����
	Timer*		invincibleTimer;	//���G����
	Timer*		randomRest;			//���Q�x�e����

	VERTEX3D magicCircleVertex[MAGIC_CIRCLE_VERTEX_NUM];	//���_���
	VERTEX3D magicCircleVertex2[MAGIC_CIRCLE_VERTEX_NUM];	//���_���
	VERTEX3D homingMagicVertex[HOMING_MAGIC_POLYGON_NUM];	//���_���

	VECTOR randomWalkTargetPos;			//���Q��ڕW���W
	VECTOR homingMoveVec;				//�z�[�~���O�ړ��x�N�g��
	float animPlayTime[TOTAL_ANIM_NUM];	//�A�j���[�V�����Đ�����
	float explosionMagicRadius;			//�������@���a
	bool isRestTime;					//�x�e�ɓ��邩�ǂ���
	bool isRandomWalk;					//���Q���Ă��邩�ǂ���
	bool isRandomRest;					//���Q��A�x�e���Ă��邩�ǂ���
	bool isInitMagicExp;				//�������@��������������
	int magicCircleTexture;				//���@�w�e�N�X�`��
	int attackType;						//�U���̎��
	int attackAnimLoopCount;			//�U����
	int magicCircleTexture2;			//���@�w�e�N�X�`��
	int magicWaitFrameCount;			//���@�ҋ@�t���[����
};


