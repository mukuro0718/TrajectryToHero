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

	void Update()override;		//�X�V
	void Init  ()override;	//������
	void Move  (const VECTOR _playerPos)override;		//�ړ�
	void UpdateUI();//UI�̍X�V
	void DrawUI();//UI�̕`��

	const float GetRadius()const { return RADIUS; }

private:
	struct RangeOfAction//�s���\�͈�
	{
		float LX = 0;
		float LZ = 0;
		float RX = 0;
		float RZ = 0;
	};
	/*�萔*/
	enum class AnimationType//�A�j���[�V����
	{
		WALK,
		NORMAL_ATTACK,	//�ʏ�U���A�j���[�V����
		ROTATE_ATTACK,	//�ʏ�U���A�j���[�V����
		JUMP_ATTACK,	//�W�����v�U���A�j���[�V����
		JUMP_IDLE,		//�W�����v��ҋ@�A�j���[�V����
		IDLE,			//�ҋ@�A�j���[�V����
		DEATH,			//���S�A�j���[�V����
	};
	/*�ÓI�萔*/
	static constexpr float	RADIUS		   = 15.0f;	//���a
	static constexpr int	RANDOM_X_RANGE = -100;	//�G�̐������Ɍ��߂�X���W�͈̔�
	static constexpr float HEIGHT = 30.0f;//Boss�̍���
	static constexpr RangeOfAction HP_FRAME_POS = { 100,990,1100,1010 };//HP�t���[�����W
	static constexpr VEC2D HP_BAR_POS = { 100,990 };//HP�t���[�����W
	static const	 VECTOR MODEL_SCALE;			//���f���̊g�嗦
	static const	 VECTOR MODEL_ROTATE;			//���f���̉�]�l
	static const	 VECTOR INIT_POS;				//�������W
	static const	 int FONT_COLOR;//�t�H���g�J���[
	static const	 int CAPSULE_COLOR;//�����蔻��p�J�v�Z���̐F
	/*�N���X*/
	Animation*	anim;					//�A�j���[�V�����N���X
	Timer*		invincibleTimer;		//���G���ԃN���X
	Timer*		restTimeAfterAttack;	//�U����x�e���ԃN���X
	Timer*		waitBeforeJumpAttack;	//�W�����v�U���ҋ@����
	Timer*		waitBeforeRotateAttack;	//��]�U���ҋ@����
	Timer*		rotateAttackLoopTime;	//��]�U�����[�v����
	/*���������֐�*/
	void Create();//�쐬
	float ChangeRotate(VECTOR _playerPos);	//�p�x�̕ύX
	void ChangeAnim();//�A�j���[�V�����̕ύX
	void  Final();							//�ŏI����
	/*�����o�ϐ�*/
	int  attackAnimLoopCount;	//�U���A�j���[�V�������[�v����
	bool isRestTime;			//�x�e�ɓ��邩�ǂ���
	bool isJumpAttack;//�W�����v�A�^�b�N�������邩�ǂ����itrue:������ false:�����Ȃ��j
	bool isRotateAttack;//�W�����v�A�^�b�N�������邩�ǂ����itrue:������ false:�����Ȃ�
	int attackType;//�U���̃^�C�v
	bool isJumpIdle;//�W�����v�A�C�h���A�j���[�V�������Đ����Ă��邩�ǂ���(true:�Đ����Ă��� false:�Đ����Ă��Ȃ�)
	VECTOR jumpAttackTargetPos;
	VECTOR spherePos;
	VEC2D nowHP;
	VEC2D prevHP;
	int font;	//�t�H���g�n���h��
	int frameImage;
	int hpImage;

};


