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
BossEnemy::BossEnemy(const VECTOR _spawnPos, const int _modelHandle, const int _frameImage, const int _hpImage, const int _font)
	:EnemyBase(_modelHandle)
	, font(_font)
	, frameImage(_frameImage)
	, hpImage(_hpImage)
	, jumpAtttackFlySpeed(0.0f)
	, animPlayTime{ 0.8f,0.6f,0.6f,0.6f,0.6f,0.6f,0.6f,0.8f,0.8f }
	, flyFrameCount(0)
	, isOnGround(false)
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
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/WalkAnim.mv1")			, 0);//����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/MeleeAnim.mv1")			, 0);//�ʏ�U��
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/StrongAttackAnim.mv1")	, 0);//�����U��
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/RotateAttackAnim.mv1")	, 0);//��]�U��
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/JumpAttackAnim.mv1")		, 0);//�W�����v�U��
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/MeteoAttackAnim.mv1")		, 0);//覐΍U��
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/ExplosionAttackAnim.mv1")	, 0);//�����U��
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/IdleAnim.mv1")			, 0);//�ҋ@
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Boss/DeathAnim.mv1")			, 0);//���S
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
	rotateAttackLoopTime	= new Timer();
}
/// <summary>
/// ������
/// </summary>
const void BossEnemy::Init()
{
	//�K�v��Init�N���X�̌Ăяo��
	rotateAttackLoopTime  ->Init(50);
	invincibleTimer		  ->Init(8);	
	restTimeAfterAttack   ->Init(20);
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
	SetUpCapsule(pos, HEIGHT, RADIUS, CAPSULE_COLOR, false);
	SetUpSphere(spherePos, 10.0f, CAPSULE_COLOR, false);
}
/// <summary>
/// �ŏI����
/// </summary>
void BossEnemy::Delete()
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
	if (rotateAttackLoopTime)
	{
		delete(rotateAttackLoopTime);
		rotateAttackLoopTime = nullptr;
	}

}
/// <summary>
/// �X�V
/// </summary>
const void BossEnemy::Update()
{
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
	SetUpSphere(spherePos, attackRadius, CAPSULE_COLOR, false);
	blood->Update(45);
	//�F�̕ύX
	ChangeColor();
	//�A�j���[�V�����Đ����Ԃ��Z�b�g
	anim->Play(&modelHandle, animPlayTime[anim->GetAnim() ]);
}
const void BossEnemy::Attack(const float _targetVecSize, const VECTOR _targetPos)
{
	//�U�������Ă��Ȃ�������
	if (!isAttack)
	{
		//�e�U���t���O������������
		isJumpAttack = false;
		isRotateAttack = false;
		isMeteoAttack = false;
		isExplosionAttack = false;
		isNormalAttack = false;
		isStrongAttack = false;
		isAttack = true;
		isMove = false;
		/*�ڕW�܂ł̃x�N�g�������ƂɍU��������U��*/
		//�x�N�g���T�C�Y���萔�ȉ���������ߋ����p�U��������
		if (_targetVecSize <= CLOSE_ATTACK_RANGE)
		{
			int random = GetRand(RANDOM_RANGE_CLOSE_ATTACK);
			//�ʏ�U��
			if (random <= NORMAL_ATTACK_RANGE)
			{
				isNormalAttack = true;
			}
			//�����U��
			else if (random <= STRONG_ATTACK_RANGE)
			{
				isStrongAttack = true;
			}
			//�����U��
			else
			{
				isExplosionAttack = true;
			}
		}
		//�������U��
		else if (_targetVecSize <= MIDDLE_ATTACK_RANGE)
		{
			int random = GetRand(RANDOM_RANGE_MIDDLE_ATTACK);
			//��]�U��
			if (random == 0)
			{
				isRotateAttack = true;
				rotateAttackLoopTime->StartTimer();
			}
			//�W�����v�U��
			else
			{
				isJumpAttack = true;
				jumpAttackTargetPos = _targetPos;
			}
		}
		//�������U��
		else if (_targetVecSize <= LONG_ATTACK_RANGE)
		{
			isMeteoAttack = true;
		}
		//�����������Ă�����U���t���O�������A�߂Â����߂Ɉړ��t���O�𗧂Ă�
		else
		{
			isAttack = false;
			isMove = true;
		}
	}
	//�U�������Ă����ꍇ�A�U�����I�����邽�߂̏������s��
	else
	{
		//��]�U�������Ă�����
		if (isRotateAttack && rotateAttackLoopTime->getIsStartTimer())
		{
			//�^�C�}�[���ڕW���ԂɒB������
			if (rotateAttackLoopTime->CountTimer())
			{
				//�t���O�𒲐�����
				rotateAttackLoopTime->EndTimer();
				isAttack = false;
				isRotateAttack = false;
				isRestTime = true;
				restTimeAfterAttack->StartTimer();
			}
		}
		else if(isJumpAttack)
		{
			if (anim->GetIsChangeAnim())
			{
				isJumpAttack = false;
				isFly = true;
			}
		}
		//�W�����v�E�ʏ�E�����E�����E覐΍U�������Ă�����
		else if (isMeteoAttack || isExplosionAttack || isNormalAttack || isStrongAttack)
		{
			if (anim->GetIsChangeAnim())
			{
				//�t���O�𒲐�����
				isJumpAttack = false;
				isMeteoAttack = false;
				isExplosionAttack = false;
				isNormalAttack = false;
				isStrongAttack = false;
				isAttack = false;
				isRestTime = true;
				restTimeAfterAttack->StartTimer();
			}
		}
	}
}
const void BossEnemy::Rest()
{
	if (restTimeAfterAttack->CountTimer())
	{
		restTimeAfterAttack->EndTimer();
		isRestTime = false;
	}
}
/// <summary>
/// �ړ�
/// </summary>
const void BossEnemy::Move(const VECTOR _playerPos)
{
	moveVec = ORIGIN_POS;
	//�ڕW�܂ł̃x�N�g��
	VECTOR targetVec = ORIGIN_POS;
	//���K�������x�N�g��
	VECTOR normalizePos = ORIGIN_POS;
	//�Ԃ�l�Ƃ��ĕԂ��ړ�����W�i�p�x�L�j
	VECTOR outPutPos = ORIGIN_POS;
	//�x�N�g���̑傫��
	float vectorSize = 0.0f;
	//�ڕW�܂ł̃x�N�g��
	targetVec = VSub(pos, _playerPos);
	//���̃x�N�g���̑傫�������߂�
	vectorSize = VSize(targetVec);
	//�ڕW�܂ł̃x�N�g���𐳋K������
	normalizePos = VNorm(targetVec);
	//�����x�e���Ă��Ȃ���΍U������
	if (!isRestTime)
	{
		Attack(vectorSize,_playerPos);
		//�p�x��ς���
		rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
		//�ړ��E�p�x�̕ύX���K�v�Ȏ��ɕύX����
		if (isMove || isRotateAttack)
		{
			moveVec = VScale(normalizePos, status->GetAgi() * -1);
		}
		else if (isFly)
		{
			if (!isOnGround)
			{
				pos.y = 500.0f;
			}
			//�ڕW�܂ł̃x�N�g��
			targetVec = VSub(pos, _playerPos);
			//���̃x�N�g���̑傫�������߂�
			vectorSize = VSize(targetVec);
			//�ڕW�܂ł̃x�N�g���𐳋K������
			normalizePos = VNorm(targetVec);

			
			if (vectorSize >= 501.0f)
			{
				moveVec = VScale(normalizePos, status->GetAgi() * -30);
			}
			else
			{
				isOnGround = true;
				pos.y = 0.0f;
				frameCount++;
				if (frameCount == 10)
				{
					frameCount = 0;
					isFly = false;
					isAttack = false;
					isRestTime = true;
					isOnGround = false;
					restTimeAfterAttack->StartTimer();
				}
			}
		}
	}
	//�����x�e���Ă���΁A�x�e���I�����锻����s��
	else
	{
		Rest();
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
		//�����U������������
		if (isAttack)
		{
			//�ʏ�U��
			if (isNormalAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::NORMAL_ATTACK));
				spherePos = MV1GetFramePosition(modelHandle, 15);
				attackRadius = 10.0f;
			}
			//�����U��
			else if (isStrongAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::STRONG_ATTACK));
				spherePos = MV1GetFramePosition(modelHandle, 11);
				attackRadius = 10.0f;
			}
			//��]�U��
			else if (isRotateAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::ROTATE_ATTACK));
				spherePos = MV1GetFramePosition(modelHandle, 30);
				attackRadius = 10.0f;
			}
			//�W�����v�U��
			else if (isJumpAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::JUMP_ATTACK));
				spherePos = pos;
				attackRadius = 30.0f;
			}
			//覐΍U��
			else if (isMeteoAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::METEO_ATTACK));
				spherePos = VGet(0.0f, 500.0f, 0.0f);
				attackRadius = 20.0f;
			}
			//�����U��
			else if (isExplosionAttack)
			{
				anim->SetAnim(static_cast<int>(AnimationType::EXPLOSION_ATTACK));
				spherePos = VGet(0.0f, 500.0f, 0.0f);
				attackRadius = 20.0f;
			}
			else if (isFly)
			{
				spherePos = pos;
				anim->SetAnim(static_cast<int>(AnimationType::IDLE));
			}
		}
		else if (isRestTime)
		{
			anim->SetAnim(static_cast<int>(AnimationType::IDLE));
		}
		else if (isMove)
		{
			spherePos = VGet(0.0f, 500.0f, 0.0f);
			anim->SetAnim(static_cast<int>(AnimationType::WALK));
		}
	}
}
/// <summary>
///	�p�x�̕ύX
/// </summary>
float BossEnemy::ChangeRotate(const VECTOR _playerPos)
{
	//2�_�Ԃ̃x�N�g�����o��(�G�l�~�[����v���C���[)
	VECTOR EP_Vector = VSub(pos, _playerPos);
	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}
/// <summary>
/// UI�̍X�V
/// </summary>
const void BossEnemy::UpdateUI()
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
const void BossEnemy::DrawUI()
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
