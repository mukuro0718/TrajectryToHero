//===========================================================================
//@brief �E�B�[�N�G�l�~�[�N���X/�p��
//===========================================================================

#include"WeakEnemy.h"
#include<math.h>
#include"Animation.h"
//#include"CharacterStatus.h"
#include"Timer.h"
//���f���ݒ�
 const VECTOR WeakEnemy::MODEL_SCALE = VGet(0.2f, 0.2f, 0.2f);//���f���̊g�嗦
 const VECTOR WeakEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//���f���̉�]�l
 
/// <summary>
/// �R���X�g���N�^
/// </summary>
WeakEnemy::WeakEnemy(const VECTOR _spawnPos,const int _modelHandle)
 :EnemyBase(_modelHandle)
{
	Create();
	spawnPos = _spawnPos;
	Init();
	//�X�P�[���̃Z�b�g
	MV1SetScale(modelHandle, scale);
	//��]�l�̃Z�b�g
	MV1SetRotationXYZ(modelHandle, rotate);
	//�A�j���[�V�����̒ǉ�
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/RunAnim.mv1"), 1);				//����A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/AttackAnim.mv1"), 1);		//�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/IdleAnim.mv1"), 1);			//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/DeathAnim.mv1"), 1);		//���S�A�j���[�V����
	//�A�^�b�`����A�j���[�V����
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//�A�j���[�V�����̃A�^�b�`
	anim->Attach(&modelHandle);
}
/// <summary>
/// ����
/// </summary>
void WeakEnemy::Create()
{
	//�C���X�^���X�̏�����
	statusInit = NULL;
	invincibleTimer = NULL;
	restTimeAfterAttack = NULL;
	anim = NULL;
	//�C���X�^���X�̐���
	invincibleTimer = new Timer();
	restTimeAfterAttack = new Timer();
	anim = new Animation();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
WeakEnemy::~WeakEnemy()
{
	Final();
}
/// <summary>
/// ������
/// </summary>
void WeakEnemy::Init()
{
	//�K�v��Init�N���X�̌Ăяo��
	invincibleTimer->Init(9);
	restTimeAfterAttack->Init(20);
	//�V�������W�̐���
	pos			= spawnPos;
	rotate		= MODEL_ROTATE;
	scale		= MODEL_SCALE;
	isAttack	= false;
	isDeath		= false;
	isHit		= false;
	isRestTime	= false;
	//�ő�HP�̐ݒ�
	//pos.y = 10.0f;
	status->InitWeakEnemyStatus();
	maxHP = status->GetHp();
}
/// <summary>
/// �X�V
/// </summary>
void WeakEnemy::Update()
{
	//���G�t���O�������Ă�����
	if (isInvincible)
	{
		//�^�C�}�[���n�߂�
		invincibleTimer->StartTimer();
		if (invincibleTimer->CountTimer())
		{
			invincibleTimer->EndTimer();
			isInvincible = false;
		}
	}
	
	//����HP������HP���O�ɂȂ�����
	if (status->GetHp() <= 0)
	{
		//���݂̃A�j���[�V���������ꂽ�A�j���[�V�����ɂ���
		if(anim->GetAnim() == static_cast<int>(AnimationType::DEATH) && anim->GetPlayTime() == 0.0f)
		{
			isDeath = true;
			pos = DESTROY_POS;
		}
	}
	else
	{
		pos = VAdd(pos, moveVec);//�ړ�
		MV1SetRotationXYZ(modelHandle, rotate);//��]�l�̐ݒ�
	}
	ChangeAnim();
	//pos.y = 10.0f;
	MV1SetPosition(modelHandle, pos);//�ʒu�̐ݒ�
	//�A�j���[�V�����Đ����Ԃ��Z�b�g
	anim->Play(&modelHandle);
}
/// <summary>
/// �ړ�
/// </summary>
void WeakEnemy::Move(VECTOR playerPos)
{
	moveVec = ORIGIN_POS;
	//�ڕW�܂ł̃x�N�g��
	VECTOR targetPos = ORIGIN_POS;
	//���K�������x�N�g��
	VECTOR normalizePos = ORIGIN_POS;
	//�Ԃ�l�Ƃ��ĕԂ��ړ�����W�i�p�x�L�j
	VECTOR outPutPos = ORIGIN_POS;
	float vectorSize = 0.0f;
	//�v���C���[�Ǝ����̍��W�̃x�N�g���̍������߂�(�ڕW�܂ł̃x�N�g��)
	targetPos = VSub(pos, playerPos);
	//���̃x�N�g���̑傫�������߂�
	vectorSize = VSize(targetPos);
	//�ڕW�܂ł̃x�N�g���𐳋K������
	normalizePos = VNorm(targetPos);
	//�����x�N�g���T�C�Y���萔�ȉ���������U������
	if (vectorSize <= 80.0f)
	{
		//���łɍU�����Ă��Ȃ��A�x�e���ł͂Ȃ�
		if (!isAttack && !isRestTime)
		{
			attackAnimLoopCount = 100;
			isAttack = true;
			isMove = false;
		}
	}
	//80�ȏゾ������
	else
	{
		//�U����x�e�����Ă��Ȃ�������
		if (!isAttack && !isRestTime)
		{
			//�����x�N�g���T�C�Y���萔�ȉ���������v���C���[�Ɍ����đ���
			if (vectorSize <= 100.0f)
			{
				isMove = true;
				isAttack = false;
			}
			//�����藣��Ă�����
			else
			{
				isMove = false;
				isAttack = false;
			}
		}
	}
	//�U���A�j���[�V���������A�j���[�V�����ύX�t���O�������Ă�����
	if (isAttack)
	{
		//�U���񐔂��O�ɂȂ�����x�e����
		if (attackAnimLoopCount == 0 || vectorSize <= 0)
		{
			attackAnimLoopCount = 0;
			restTimeAfterAttack->StartTimer();
			isAttack = false;
			isMove = false;
			isRestTime = true;
		}
		//0����Ȃ���΍U���񐔂����炷
		else
		{
			attackAnimLoopCount--;
		}
	}
	//�����x�e����������
	else if (isRestTime)
	{
		//�^�C�}�[���I�����Ă�����
		if (restTimeAfterAttack->CountTimer())
		{
			isRestTime = false;
			restTimeAfterAttack->EndTimer();
		}
	}
	if (isMove && vectorSize >= 20 || isAttack && vectorSize >=20)
	{
		// �����U�����ɐ��K�������l���[�ɂȂ��Ă����琳�K�������l�Ɉړ��X�s�[�h�������Ĉړ��ʂ�Ԃ�
		moveVec = VScale(normalizePos, status->GetAgi() * -1);
		//�p�x��ς���
		rotate = VGet(0.0f, (float)ChangeRotate(playerPos), 0.0f);
	}
}
/// <summary>
///	�p�x�̕ύX(���f���������Ă��鏉��������z���O)
/// </summary>
double WeakEnemy::ChangeRotate(VECTOR playerPos)
{
	//2�_�Ԃ̃x�N�g�����o��(�G�l�~�[����v���C���[)
	VECTOR EP_Vector = VSub(pos, playerPos);
	//2�_�̍��W���烉�W�A�������߂�
	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}
/// <summary>
///	�A�j���[�V�����̕ύX
/// </summary>
void WeakEnemy::ChangeAnim()
{
	//�U�����ړ������Ă��Ȃ��܂��͋x�e����������
	if (!isAttack && !isMove || isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
	//�U������������
	else if (isAttack && !isMove && !isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
	}
	//�ړ�����������
	else if (!isAttack && isMove && !isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));
	}
	//����HP��0�ȉ��ɂȂ�����
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}
}
/// <summary>
/// �ŏI����
/// </summary>
void WeakEnemy::Final()
{
	if (invincibleTimer)
	{
		delete(invincibleTimer);
		invincibleTimer = NULL;
	}
	if (restTimeAfterAttack)
	{
		delete(restTimeAfterAttack);
		restTimeAfterAttack = NULL;
	}
	if (anim)
	{
		delete(anim);
		anim = NULL;
	}
}
