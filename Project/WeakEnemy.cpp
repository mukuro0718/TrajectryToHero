//===========================================================================
//@brief �E�B�[�N�G�l�~�[�N���X/�p��
//===========================================================================

#include"WeakEnemy.h"
#include<math.h>
#include"Animation.h"
#include"Timer.h"
#include"BloodParticle.h"

//���f���ݒ�
 const VECTOR WeakEnemy::MODEL_SCALE = VGet(0.2f, 0.2f, 0.2f);//���f���̊g�嗦
 const VECTOR WeakEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//���f���̉�]�l
 const int    WeakEnemy::CAPSULE_COLOR = GetColor(0, 255, 0);
 const int	  WeakEnemy::SPHERE_COLOR = GetColor(0, 200, 0);

/// <summary>
/// �R���X�g���N�^
/// </summary>
 WeakEnemy::WeakEnemy(const VECTOR _spawnPos, const int _modelHandle)
	 : EnemyBase(_modelHandle)
	 , invincibleTimer(nullptr)
	 , restTimeAfterAttack(nullptr)
	 , anim(nullptr)
	 , randomRest(nullptr)
	 //, preliminaryOperation(nullptr)
	 //, isPreliminaryOperation(false)
	 , isWalk(false)
	 , animPlayTime{0.8f,0.95f, 0.6f, 0.7f, 0.8f, 0.8f, 0.6f}
	 , attackType(0)
{
	Create();
	spawnPos = _spawnPos;
	Init();
	//�X�P�[���̃Z�b�g
	MV1SetScale(modelHandle, scale);
	//��]�l�̃Z�b�g
	MV1SetRotationXYZ(modelHandle, rotate);
	//�A�j���[�V�����̒ǉ�
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/RunAnim.mv1"), 1);			//����A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/ComboAttack.mv1"), 1);		//�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/AttackAnim.mv1"), 1);		//�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/IdleAnim.mv1"), 1);		//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/DeathAnim.mv1"), 1);		//���S�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/WalkAnim.mv1"), 1);	//�E�֕������[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/KnockBack.mv1"), 1);	//�E�֕������[�V����

	//�A�^�b�`����A�j���[�V����
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//�A�j���[�V�����̃A�^�b�`
	anim->Attach(&modelHandle);
}
/// <summary>
/// �쐬
/// </summary>
void WeakEnemy::Create()
{
	//�C���X�^���X�̐���
	invincibleTimer		= new Timer();
	restTimeAfterAttack = new Timer();
	randomRest			= new Timer();
	//preliminaryOperation= new Timer();
	anim				= new Animation();
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
	invincibleTimer->Init(8);
	restTimeAfterAttack->Init(5);
	randomRest->Init(20);
	//preliminaryOperation->Init(12);
	//�V�������W�̐���
	pos			= spawnPos;
	rotate		= MODEL_ROTATE;
	scale		= MODEL_SCALE;
	isAttack	= false;
	isDeath		= false;
	isHit		= false;
	isRestTime	= false;
	isRandomWalk = false;
	isRandomRest = false;
	//�ő�HP�̐ݒ�
	status->InitWeakEnemyStatus(1.0f);
	maxHP = status->GetHp();
}
const void WeakEnemy::NewStatus(const float _playerLv)
{
	status->InitWeakEnemyStatus(_playerLv);
	maxHP = status->GetHp();
}
/// <summary>
/// �X�V
/// </summary>
void WeakEnemy::Update()
{
	if (isHit)
	{
		frameCount++;
		if (frameCount == 60)
		{
			isHit = false;
			frameCount = 0;
		}
	}
	blood->UpdateGravity();
	if (isInvincible)
	{
		blood->Init(bloodBaseDir, pos);
	}

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
		if (anim->GetAnim() == static_cast<int>(AnimationType::DEATH) && anim->GetPlayTime() == 0.0f)
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
	//�A�j���[�V�����̕ύX
	ChangeAnim();
	//�ʒu�̐ݒ�
	MV1SetPosition(modelHandle, pos);

	SetUpCapsule(pos, HEIGHT, RADIUS, CAPSULE_COLOR, false);
	//�U�������蔻��p�X�t�B�A���W�̐ݒ�
	VECTOR framePos33 = MV1GetFramePosition(modelHandle, 33);
	VECTOR framePos46 = MV1GetFramePosition(modelHandle, 46);
	VECTOR framePos33to46 = VSub(framePos46, framePos33);
	framePos33to46 = VNorm(framePos33to46);
	framePos33to46 = VScale(framePos33to46, 10.0f);
	VECTOR attackSphereCenterPos = VAdd(framePos46, framePos33to46);
	SetUpSphere(attackSphereCenterPos, SPHERE_RADIUS, SPHERE_COLOR, false);
	blood->Update(50);
	//�F�̕ύX
	ChangeColor();
	//�A�j���[�V�����Đ����Ԃ��Z�b�g
	anim->Play(&modelHandle, animPlayTime[anim->GetAnim()]);
}
/// <summary>
/// �ړ�
/// </summary>
void WeakEnemy::Move(VECTOR _playerPos)
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
	targetPos = VSub(pos, _playerPos);
	//���̃x�N�g���̑傫�������߂�
	vectorSize = VSize(targetPos);
	//�ڕW�܂ł̃x�N�g���𐳋K������
	normalizePos = VNorm(targetPos);
	//�����x�N�g���T�C�Y���萔�ȉ���������U������
	if (vectorSize <= 20.0f)
	{
		//���łɍU�����Ă��Ȃ��A�x�e���ł͂Ȃ�
		if (!isAttack && !isRestTime && !isInvincible)
		{
			//if (!isPreliminaryOperation)
			//{
			//	preliminaryOperation->StartTimer();
			//}
			//else
			//{
			attackType = GetRand(1);
			attackAnimLoopCount = 100;
			isAttack = true;
			isMove = false;
			isRandomWalk = false;
			isRandomRest = false;
			isWalk = false;
			//}
		}
	}
	//80�ȏゾ������
	else if (vectorSize <= 50.0f)
	{
		//���łɍU�����Ă��Ȃ��A�x�e���ł͂Ȃ�
		if (!isAttack && !isRestTime)
		{
			isWalk = true;
			isMove = false;
			isAttack = false;
			isRandomWalk = false;
			isRandomRest = false;
		}
	}
	else
	{
		//�U����x�e�����Ă��Ȃ�������
		if (!isAttack && !isRestTime)
		{
			//�����x�N�g���T�C�Y���萔�ȉ���������v���C���[�Ɍ����đ���
			if (vectorSize <= 200.0f)
			{
				isMove = true;
				isAttack = false;
				isRandomWalk = false;
				isRandomRest = false;
				isWalk = false;
			}
			//�����藣��Ă�����
			else
			{
				RandomWalk();
				isWalk = false;
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
			isRandomWalk = false;
			//isPreliminaryOperation = false;
			isRestTime = true;
			isWalk = false;
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
	if (isMove && vectorSize >= 20 && !isInvincible)
	{
		// �����U�����ɐ��K�������l���[�ɂȂ��Ă����琳�K�������l�Ɉړ��X�s�[�h�������Ĉړ��ʂ�Ԃ�
		moveVec = VScale(normalizePos, status->GetAgi() * -1);
	}
	else if (isWalk && !isInvincible)
	{
		// �����U�����ɐ��K�������l���[�ɂȂ��Ă����琳�K�������l�Ɉړ��X�s�[�h�������Ĉړ��ʂ�Ԃ�
		moveVec = VScale(normalizePos, status->GetAgi() * -0.5f);
	}
	if (isMove && vectorSize >= 20 && !isInvincible || isAttack && vectorSize >= 20 && !isInvincible || isWalk && !isInvincible)
	{
		//�p�x��ς���
		rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
	}

	//if (preliminaryOperation->getIsStartTimer())
	//{
	//	if (preliminaryOperation->CountTimer())
	//	{
	//		preliminaryOperation->EndTimer();
	//		isPreliminaryOperation = true;
	//	}
	//}
}
/// <summary>
/// �����_���ɕ���
/// </summary>
void WeakEnemy::RandomWalk()
{
	//�ڕW�܂ł̃x�N�g��
	VECTOR targetVec = ORIGIN_POS;
	//���K�������x�N�g��
	VECTOR normalizeVec = ORIGIN_POS;
	//�x�N�g���̃T�C�Y
	float vectorSize = 0.0f;
	targetVec = VSub(randomWalkTargetPos, pos);
	if (isRandomWalk == false)
	{
		randomWalkTargetPos = spawnPos;
		/*TODO*/
		//�����X�|�[���ʒu����萔�ȏ㗣��Ă�����X�|�[���ʒu�X�|�[���ʒu�Ɍ������Đi��
		//�����łȂ���΃����_���ō��W���o���āA�i�ޕ��������߂�A�x�N�g���̃T�C�Y���o���āA�O�ɂȂ�܂Ői��
		// �����_���ŏo�����W�̓X�|�[���ʒu����X,Z���W�����Ɂ{�萔�͈̔͂ŏo��
		//�����i��ł���r���ɃX�|�[���ʒu����萔�ȏ㗣�ꂽ��~�܂�
		randomWalkTargetPos.x += static_cast<float>(GetRand(200) - 100);
		randomWalkTargetPos.z += static_cast<float>(GetRand(200) - 100);
		isRandomWalk = true;
		targetVec = VSub(randomWalkTargetPos, pos);
	}
	//���̃x�N�g���̑傫�������߂�
	else if (VSize(targetVec) < 10.0f)
	{
		randomRest->StartTimer();
		isRandomRest = true;
	}
	if (randomRest->CountTimer())
	{
		randomRest->EndTimer();
		isRandomWalk = false;
		isRandomRest = false;
	}
	if (!randomRest->getIsStartTimer())
	{
		normalizeVec = VNorm(targetVec);
		// �����U�����ɐ��K�������l���[�ɂȂ��Ă����琳�K�������l�Ɉړ��X�s�[�h�������Ĉړ��ʂ�Ԃ�
		moveVec = VScale(normalizeVec, status->GetAgi());
		moveVec.y = 0.0f;
		//�p�x��ς���
		rotate = VGet(0.0f, (float)ChangeRotate(randomWalkTargetPos), 0.0f);
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
	if (isInvincible)
	{
	anim->SetAnim(static_cast<int>(AnimationType::FRIGHTENING));//����
	}
	//�U�����ړ������Ă��Ȃ��܂��͋x�e����������
	else if (!isAttack && !isMove && !isRandomWalk && !isWalk|| isRestTime || isRandomRest)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
	//�U������������
	else if (isAttack && !isMove && !isRestTime)
	{
		if (attackType == static_cast<int>(AttackType::COMBO_ATTACK))
		{
			anim->SetAnim(static_cast<int>(AnimationType::COMBO_ATTACK));
		}
		else
		{
			anim->SetAnim(static_cast<int>(AnimationType::NORMAL_ATTACK));
		}
	}
	//�ړ�����������
	else if (!isAttack && isMove && !isRestTime || !isAttack && isRandomWalk && !isRestTime)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));
	}
	else if (isWalk)
	{
		anim->SetAnim(static_cast<int>(AnimationType::WALK));
	}
	//����HP��0�ȉ��ɂȂ�����
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}
	//else if (preliminaryOperation->getIsStartTimer() && !isRestTime)
	//{
	//	anim->SetAnim(static_cast<int>(AnimationType::BEFORE_ATTACK));
	//}
}
/// <summary>
/// �ŏI����
/// </summary>
void WeakEnemy::Final()
{
	if (invincibleTimer)
	{
		delete(invincibleTimer);
		invincibleTimer = nullptr;
	}
	if (restTimeAfterAttack)
	{
		delete(restTimeAfterAttack);
		restTimeAfterAttack = nullptr;
	}
	if (anim)
	{
		delete(anim);
		anim = nullptr;
	}
}
