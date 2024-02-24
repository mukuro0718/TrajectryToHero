//===========================================================================
//@brief �{�X�G�l�~�[�N���X/�p��
//===========================================================================

#include"BossEnemy.h"
#include<math.h>
#include"Animation.h"
#include"Timer.h"
#include"BloodParticle.h"

//���f���ݒ�
const VECTOR BossEnemy::MODEL_SCALE = VGet(0.4f, 0.4f, 0.4f);//���f���̊g�嗦
const VECTOR BossEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//���f���̉�]�l
const VECTOR BossEnemy::INIT_POS = VGet(0.0f, 0.0f, 500.0f);//���f���̉�]�l
const int    BossEnemy::CAPSULE_COLOR = GetColor(0, 255, 0);
const int	 BossEnemy::FONT_COLOR = GetColor(150, 150, 150);

/// <summary>
/// �R���X�g���N�^
/// </summary>
BossEnemy::BossEnemy(const VECTOR _spawnPos,const int _modelHandle, const int _frameImage, const int _hpImage, const int _font)
	:EnemyBase(_modelHandle)
	,font(_font)
	,frameImage(_frameImage)
	,hpImage(_hpImage)
	, preliminaryOperation(nullptr)
	, isPreliminaryOperation(false)
	, isAttackPreparation(false)
{
	Create();
	spawnPos = _spawnPos;
	nowHP.y = 20;
	Init();
	//���f���ݒ�
	MV1SetScale(modelHandle, scale);
	//��]�l�̃Z�b�g
	MV1SetRotationXYZ(modelHandle, rotate);
	//�A�j���[�V�����̒ǉ�
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/WalkAnim.mv1"), 0);
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/StronglAttackAnim.mv1"), 0);	//�ʏ�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/RotateAttackAnim.mv1"), 0);	//��]�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/JumpAttackAnim.mv1"), 0);		//�W�����v�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/JumpIdleAnim.mv1"), 0);			//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/IdleAnim.mv1"), 0);			//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/DeathAnim.mv1"), 0);			//���S�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/BeforeAttackAnim.mv1"), 0);//�U���O���[�V����
	//�A�^�b�`����A�j���[�V����
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//�A�j���[�V�����̃A�^�b�`�i�ŏ��͖����I�ɌĂяo���ăA�j���[�V�������A�^�b�`����K�v������j
	anim->Attach(&modelHandle);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemy::~BossEnemy()
{
	Final();
}
/// <summary>
/// �쐬
/// </summary>
void BossEnemy::Create()
{
	//�C���X�^���X�̏�����
	invincibleTimer		= nullptr;
	restTimeAfterAttack = nullptr;
	anim				= nullptr;
	//�C���X�^���X�̐���
	invincibleTimer			= new Timer();
	restTimeAfterAttack		= new Timer();
	anim					= new Animation();
	waitBeforeJumpAttack	= new Timer();
	waitBeforeRotateAttack	= new Timer();
	rotateAttackLoopTime	= new Timer();
	preliminaryOperation = new Timer();

}
/// <summary>
/// ������
/// </summary>
void BossEnemy::Init()
{
	//�K�v��Init�N���X�̌Ăяo��
	waitBeforeJumpAttack  ->Init(20);
	waitBeforeRotateAttack->Init(10);
	rotateAttackLoopTime  ->Init(50);
	invincibleTimer		  ->Init(8);	
	restTimeAfterAttack   ->Init(30);
	preliminaryOperation->Init(12);
	//�ő�HP�̐ݒ�
	status->InitBossEnemyStatus();
	maxHP = status->GetHp();
	attackType				= 0;
	attackAnimLoopCount		= 0;
	pos						= spawnPos;
	rotate					= MODEL_ROTATE;
	scale					= MODEL_SCALE;
	jumpAttackTargetPos		= ORIGIN_POS;
	spherePos = MV1GetFramePosition(modelHandle, 11);;
	isJumpAttack	= false;
	isJumpIdle		= false;
	isAttack		= false;
	isDeath			= false;
	isHit			= false;
	isRestTime		= false;
	isPreliminaryOperation = false;
	isAttackPreparation = false;
	SetUpCapsule(pos, HEIGHT, RADIUS, CAPSULE_COLOR, false);
	SetUpSphere(spherePos, 10.0f, CAPSULE_COLOR, false);
}
/// <summary>
/// �ŏI����
/// </summary>
void BossEnemy::Final()
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
	if (waitBeforeJumpAttack)
	{
		delete(waitBeforeJumpAttack);
		waitBeforeJumpAttack = nullptr;
	}
	if (waitBeforeRotateAttack)
	{
		delete(waitBeforeRotateAttack);
		waitBeforeRotateAttack = nullptr;
	}

	if (rotateAttackLoopTime)
	{
		delete(rotateAttackLoopTime);
		rotateAttackLoopTime = nullptr;
	}

}
/// <summary>
/// �X�V
/// </summary>
void BossEnemy::Update()
{
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
			//isInvincible = false;
		}
	}
	//�����v���C���[�ɓ������Ă�����
	if (status->GetHp() < 0)
	{
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
	SetUpCapsule(pos, HEIGHT, RADIUS,CAPSULE_COLOR,false);
	SetUpSphere(spherePos, 10.0f, CAPSULE_COLOR, false);
	blood->Update(45);
	//�F�̕ύX
	ChangeColor();
	//�A�j���[�V�����Đ����Ԃ��Z�b�g
	anim->Play(&modelHandle, 0.8f);
}
/// <summary>
/// �ړ�
/// </summary>
void BossEnemy::Move(const VECTOR _playerPos)
{
	moveVec = ORIGIN_POS;
	//�ڕW�܂ł̃x�N�g��
	VECTOR targetPos = ORIGIN_POS;
	//���K�������x�N�g��
	VECTOR normalizePos = ORIGIN_POS;
	//�Ԃ�l�Ƃ��ĕԂ��ړ�����W�i�p�x�L�j
	VECTOR outPutPos = ORIGIN_POS;
	//�x�N�g���̑傫��
	float vectorSize = 0.0f;
	//�ڕW�܂ł̃x�N�g��
	targetPos = VSub(pos, _playerPos);
	//���̃x�N�g���̑傫�������߂�
	vectorSize = VSize(targetPos);
	//printfDx("size %f", vectorSize);
	//�ڕW�܂ł̃x�N�g���𐳋K������
	normalizePos = VNorm(targetPos);
	//�U�����x�e�����Ă��Ȃ�������
	if (!isAttackPreparation && !isRestTime)
	{
		//�U���t���O�𗧂Ă�
		//isAttack = true;
		isAttackPreparation = true;
		if (vectorSize <= 20)
		{
			attackType = static_cast<int>(AnimationType::NORMAL_ATTACK);
		}
		else
		{
			attackType = GetRand(1) + 2;
		}
	}
	if (!isRestTime)
	{
			//�p�x��ς���
			rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
		//������]�U���^�C�}�[���n�܂��Ă���
		if (rotateAttackLoopTime->getIsStartTimer())
		{
			//�ڕW���ԂɒB������
			if (rotateAttackLoopTime->CountTimer())
			{
				//�x�e�^�C�}�[���X�^�[�g������
				restTimeAfterAttack->StartTimer();
				isRestTime = true;
				isPreliminaryOperation = false;
				isAttack = false;
				//��]�U���^�C�}�[���I��点��
				rotateAttackLoopTime->EndTimer();
			}
			else
			{
				//�ڕW�܂ł̃x�N�g��
				targetPos = VSub(pos, _playerPos);
				//���̃x�N�g���̑傫�������߂�
				vectorSize = VSize(targetPos);
				//�ڕW�܂ł̃x�N�g���𐳋K������
				normalizePos = VNorm(targetPos);
				moveVec = VScale(normalizePos, status->GetAgi() * -1);
			}
		}
		//�����W�����v�U���^�C�}�[���n�܂��Ă���
		if (waitBeforeJumpAttack->getIsStartTimer())
		{
			//�ڕW���ԂɒB������
			if (waitBeforeJumpAttack->CountTimer())
			{
				jumpAttackTargetPos = _playerPos;
				isJumpAttack = true;
				isAttack = true;
				waitBeforeJumpAttack->EndTimer();
			}
		}
		if (isJumpAttack)
		{
			//�ڕW�܂ł̃x�N�g��
			targetPos = VSub(pos, jumpAttackTargetPos);
			//���̃x�N�g���̑傫�������߂�
			vectorSize = VSize(targetPos);
			//�ڕW�܂ł̃x�N�g���𐳋K������
			normalizePos = VNorm(targetPos);
			//�x�N�g���̑傫�����萔�l�ȉ��ɂȂ�����
			if (vectorSize <= 20)
			{
				//�x�e�^�C�}�[���n�߂�
				restTimeAfterAttack->StartTimer();
				isRestTime = true;
				isAttack = false;
			}
			else
			{
				moveVec = VScale(normalizePos, status->GetAgi() * -3);
				//�p�x��ς���
				rotate = VGet(0.0f, (float)ChangeRotate(jumpAttackTargetPos), 0.0f);
			}
		}

	}
	//�����x�e���ԃ^�C�}�[���n�܂��Ă���
	else if (restTimeAfterAttack->getIsStartTimer())
	{
		//�ڕW���ԂɒB������
		if (restTimeAfterAttack->CountTimer())
		{
			restTimeAfterAttack->EndTimer();
			isRestTime = false;
			isAttackPreparation = false;
		}
	}
}
/// <summary>
/// �A�j���[�V�����̕ύX
/// </summary>
void BossEnemy::ChangeAnim()
{
	//���S�A�j���[�V����
	if (status->GetHp() < 0)
	{
		if (!isDeath)
		{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));

		}
	}
	else
	{
		if (!isRestTime)
		{
			switch (attackType)
			{
			case 1://�ʏ�
				if (isAttack)
				{


					anim->SetAnim(static_cast<int>(AnimationType::NORMAL_ATTACK));
					spherePos = MV1GetFramePosition(modelHandle, 11);
					attackAnimLoopCount = 1;
				}
				break;
			case 2://��]
					if (!isPreliminaryOperation)
					{
						preliminaryOperation->StartTimer();
					}
					else
					{
						isAttack = true;
						anim->SetAnim(static_cast<int>(AnimationType::ROTATE_ATTACK));
						spherePos = MV1GetFramePosition(modelHandle, 31);
						rotateAttackLoopTime->StartTimer();
					}
					if (preliminaryOperation->getIsStartTimer())
					{
						anim->SetAnim(static_cast<int>(AnimationType::BEFORE_ATTACK));
						if (preliminaryOperation->CountTimer())
						{
							preliminaryOperation->EndTimer();
							isPreliminaryOperation = true;
						}
					}
				
				break;
			case 3://�W�����v
				if (isAttack || isAttackPreparation)
				{
					anim->SetAnim(static_cast<int>(AnimationType::JUMP_ATTACK));
					spherePos = MV1GetFramePosition(modelHandle, 7);
					if (!isJumpAttack)
					{
						waitBeforeJumpAttack->StartTimer();
					}
				}
				break;
			default:
				break;
			}
		}
		if (isRestTime)
		{
			spherePos = MV1GetFramePosition(modelHandle, 7);
			if (anim->GetAnim() == static_cast<int>(AnimationType::JUMP_IDLE) && anim->GetPlayTime() == 0.0f)
			{
				anim->SetAnim(static_cast<int>(AnimationType::IDLE));
				attackType = 0;
				isJumpAttack = false;
			}
			//�A�j���[�V�������W�����v�A�^�b�N��������
			else if (attackType == static_cast<int>(AnimationType::JUMP_ATTACK))
			{
				anim->SetAnim(static_cast<int>(AnimationType::JUMP_IDLE));
			}
			else
			{
				anim->SetAnim(static_cast<int>(AnimationType::IDLE));
			}
		}
	}
}
/// <summary>
///	�p�x�̕ύX
/// </summary>
float BossEnemy::ChangeRotate(VECTOR playerPos)
{
	//2�_�Ԃ̃x�N�g�����o��(�G�l�~�[����v���C���[)
	VECTOR EP_Vector = VSub(pos, playerPos);
	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}
/// <summary>
/// UI�̍X�V
/// </summary>
void BossEnemy::UpdateUI()
{
	//�ő�HP�����߂�
	//���݂�HP�����߂�
	//�w��������i���F���݂�HP/�ő�HP * 100�j
	nowHP.x = static_cast<int>(status->GetHp() / status->GetMaxHP() * 1000.0f);

	if (nowHP.x <  0)
	{
		nowHP.x = 0;
	}
}
/// <summary>
/// UI�̕`��
/// </summary>
void BossEnemy::DrawUI()
{
	//�e�L�X�g�̕\��
	DrawStringToHandle(50, 980, "HP", FONT_COLOR, font);
	//�t���[���̕`��
	DrawExtendGraph(static_cast<int>(HP_FRAME_POS.LX), static_cast<int>(HP_FRAME_POS.LZ), static_cast<int>(HP_FRAME_POS.RX), static_cast<int>(HP_FRAME_POS.RZ), frameImage, TRUE);
	//HP�o�[�̕\��
	DrawExtendGraph(HP_BAR_POS.x, HP_BAR_POS.y, HP_BAR_POS.x + nowHP.x, HP_BAR_POS.y + nowHP.y, hpImage, TRUE);
}
const void BossEnemy::PhysicalRecovery()
{
	status->PhysicalRecovery();
}
