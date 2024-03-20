//===========================================================================
//@brief �{�X�G�l�~�[�N���X/�p��
//===========================================================================
#pragma once
#include"DxLib.h"
#include"EnemyBase.h"
class Timer;
class Animation;

class BossEnemy :public EnemyBase
{
public:
	BossEnemy(const VECTOR _spawnPos,const int _modelHandle,const int _frameImage, const int _hpImage,const int _font);//��������R���X�g���N�^
	~BossEnemy();				//�f�X�g���N�^

	const void Update()override;						//�X�V
	const void Init  ()override;						//������
	const void Move  (const VECTOR _playerPos)override;	//�ړ�

	const void Attack(const float _targetVecSize,const VECTOR _targetPos);	//�U��
	const void Rest();														//�x�e
	const void UpdateUI();													//UI�̍X�V
	const void DrawUI();													//UI�̕`��
	const void Flagging() { isInvincible = false; }							//�t���O������
	const void PhysicalRecovery();											//�̗͂̉�
	/*getter*/
	const float GetRadius()const { return RADIUS; }
	const bool GetIsMeteoAttack() { return isMeteoAttack; }
	const bool GetIsExplosionAttack() { return isExplosionAttack; }
private:
	/*�\���́E�񋓑�*/
	struct RangeOfAction//�s���\�͈�
	{
		float LX = 0;
		float LZ = 0;
		float RX = 0;
		float RZ = 0;
	};
	enum class AnimationType//�A�j���[�V����
	{
		WALK,			//�����A�j���[�V����
		NORMAL_ATTACK,	//�ʏ�U���A�j���[�V����
		STRONG_ATTACK,	//�����U���A�j���[�V����
		ROTATE_ATTACK,	//��]�U���A�j���[�V����
		JUMP_ATTACK,	//�W�����v�U���A�j���[�V����
		METEO_ATTACK,	//覐΍U��
		EXPLOSION_ATTACK,//�����U��
		IDLE,			//�ҋ@�A�j���[�V����
		DEATH,			//���S�A�j���[�V����
	};
	enum class AttackType//�U���̎��
	{
		NORMAL,
		STRONG,
		ROTATE,
		JUMP,
		METEO,
		EXPLOSION,
	};
	/*�ÓI�萔*/
	static constexpr RangeOfAction	HP_FRAME_POS			   = { 100,990,1100,1010 };	//HP�t���[�����W
	static constexpr VEC2D			HP_BAR_POS				   = { 100,990 };			//HP�t���[�����W
	static constexpr float			CLOSE_ATTACK_RANGE		   = 50.0f;					//�ߋ����U���͈�
	static constexpr float			MIDDLE_ATTACK_RANGE		   = 150.0f;				//�������U���͈�
	static constexpr float			RADIUS					   = 15.0f;					//���a
	static constexpr float			LONG_ATTACK_RANGE		   = 300.0f;				//�������U���͈�
	static constexpr float			HEIGHT					   = 30.0f;					//Boss�̍���
	static constexpr int			RANDOM_RANGE_CLOSE_ATTACK  = 10;					//�ߋ����U���p�����_���͈�
	static constexpr int			NORMAL_ATTACK_RANGE		   = 5;						//�ʏ�U���͈̔�
	static constexpr int			STRONG_ATTACK_RANGE		   = 8;						//�����U���͈̔�
	static constexpr int			RANDOM_RANGE_MIDDLE_ATTACK = 1;						//�������U���p�����_���͈�
	static constexpr int			RANDOM_X_RANGE			   = -100;					//�G�̐������Ɍ��߂�X���W�͈̔�
	static constexpr int			TOTAL_ANIM_NUM			   = 9;						//�A�j���[�V�������v��

	static const VECTOR MODEL_ROTATE;	//���f���̉�]�l
	static const VECTOR INIT_POS;		//�������W
	static const VECTOR MODEL_SCALE;	//���f���̊g�嗦
	static const int FONT_COLOR;		//�t�H���g�J���[
	static const int CAPSULE_COLOR;		//�����蔻��p�J�v�Z���̐F
	/*�N���X*/
	Animation*	anim;					//�A�j���[�V�����N���X
	Timer*		invincibleTimer;		//���G���ԃN���X
	Timer*		restTimeAfterAttack;	//�U����x�e���ԃN���X
	Timer*		rotateAttackLoopTime;	//��]�U�����[�v����

	/*���������֐�*/
	void Create();								//�쐬
	float ChangeRotate(const VECTOR _playerPos);//�p�x�̕ύX
	void ChangeAnim();							//�A�j���[�V�����̕ύX
	void Delete();								//�ŏI����
	/*�����o�ϐ�*/
	bool isJumpAttack;					//�W�����v�A�^�b�N�������邩�ǂ����itrue:������ false:�����Ȃ��j
	bool isRotateAttack;				//�W�����v�A�^�b�N�������邩�ǂ����itrue:������ false:�����Ȃ�
	bool isMeteoAttack;					//覐΍U�������邩
	bool isExplosionAttack;				//�����U�������邩
	bool isNormalAttack;				//�ʏ�U��
	bool isStrongAttack;				//�����U��
	bool isFly;							//�W�����v�U���Ŕ��
	bool isOnGround;					//���n���Ă��邩
	int flyFrameCount;					//���t���[������Ԃ�
	float attackRadius;					//�U�����a
	float jumpAtttackFlySpeed;			//�W�����v�U���̔�ԑ���
	float animPlayTime[TOTAL_ANIM_NUM];	//�A�j���[�V�����Đ�����
	int  attackAnimLoopCount;			//�U���A�j���[�V�������[�v����
	bool isRestTime;					//�x�e�ɓ��邩�ǂ���
	int attackType;						//�U���̃^�C�v
	bool isJumpIdle;					//�W�����v�A�C�h���A�j���[�V�������Đ����Ă��邩�ǂ���(true:�Đ����Ă��� false:�Đ����Ă��Ȃ�)
	VECTOR jumpAttackTargetPos;			//�W�����v�U�����W
	VECTOR spherePos;					//�����W
	VEC2D nowHP;						//���݂�HP
	VEC2D prevHP;						//�O��HP
	int font;							//�t�H���g�n���h��
	int frameImage;						//�t���[���摜
	int hpImage;						//HP�摜
};


