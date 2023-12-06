//===========================================================================
//@brief �{�X�G�l�~�[�N���X/�p��
//===========================================================================

#include"Boss.h"
#include<math.h>
#include"Animation.h"
#include"CharacterStatus.h"
#include"Timer.h"
//���f���ݒ�
const VECTOR Boss::MODEL_SCALE = VGet(0.4f, 0.4f, 0.4f);//���f���̊g�嗦
const VECTOR Boss::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//���f���̉�]�l
const VECTOR Boss::INIT_POS = VGet(0.0f, 0.0f, 500.0f);//���f���̉�]�l

/// <summary>
/// �R���X�g���N�^
/// </summary>
Boss::Boss(const VECTOR _spawnPos,const int _modelHandle)
	:EnemyBase(_modelHandle)
{
	//�C���X�^���X�̏�����
	invincibleTimer		= NULL;
	restTimeAfterAttack = NULL;
	anim				= NULL;
	//�C���X�^���X�̐���
	invincibleTimer		= new Timer();
	restTimeAfterAttack = new Timer();
	anim				= new Animation();
	spawnPos = _spawnPos;
	Init();
	//���f���ݒ�
	MV1SetScale(modelHandle, scale);
	//��]�l�̃Z�b�g
	MV1SetRotationXYZ(modelHandle, rotate);
	//�R���W���������\�z
	MV1SetupCollInfo(modelHandle, -1, 1, 1, 1);
	//�A�j���[�V�����̒ǉ�
	anim->Add(MV1LoadModel("Data/Animation/Boss_Walk.mv1"), 0);
	anim->Add(MV1LoadModel("Data/Animation/Boss_StronglAttackAnim.mv1"), 0);	//�ʏ�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Boss_RotateAttackAnim.mv1"), 0);	//��]�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Boss_JumpAttackAnim.mv1"), 0);		//�W�����v�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Boss_JumpIdleAnim.mv1"), 0);			//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Boss_IdleAnim.mv1"), 0);			//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Boss_DeathAnim.mv1"), 0);			//���S�A�j���[�V����
	//�A�^�b�`����A�j���[�V����
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//�A�j���[�V�����̃A�^�b�`�i�ŏ��͖����I�ɌĂяo���ăA�j���[�V�������A�^�b�`����K�v������j
	anim->Attach(&modelHandle);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Boss::~Boss()
{
	Final();
}
/// <summary>
/// ������
/// </summary>
void Boss::Init()
{
	waitBeforeJunpAttack	= new Timer();
	waitBeforeRotateAttack	= new Timer();
	rotateAttackLoopTime	= new Timer();
	attackType				= 0;
	jumpAttackTargetPos		= ORIGIN_POS;
	attackAnimLoopCount		= 0;
	pos						= spawnPos;
	rotate					= MODEL_ROTATE;
	scale					= MODEL_SCALE;
	waitBeforeJunpAttack->Init(10);
	waitBeforeRotateAttack->Init(10);
	rotateAttackLoopTime->Init(50);
	//�K�v��Init�N���X�̌Ăяo��
	invincibleTimer->Init(9);	
	restTimeAfterAttack->Init(20);
	status->InitBossEnemyStatus();
	//�ő�HP�̐ݒ�
	maxHP = status->GetHp();
	isJumpAttack	= false;
	isJumpIdle		= false;
	isAttack		= false;
	isDeath			= false;
	isHit			= false;
	isRestTime		= false;
}
/// <summary>
/// �ŏI����
/// </summary>
void Boss::Final()
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
/// <summary>
/// �X�V
/// </summary>
void Boss::Update()
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
	//�R���W���������X�V
	MV1RefreshCollInfo(modelHandle, -1);

	//�����v���C���[�ɓ������Ă�����
	if (status->GetHp() < 0)
	{
		//���݂̃A�j���[�V���������ꂽ�A�j���[�V�����ɂ���
		if (!isDeath)
		{
			anim->SetAnim(static_cast<int>(AnimationType::DEATH));
		}
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
	pos = VGet(pos.x, 0.0f, pos.z);
	MV1SetPosition(modelHandle, pos);//�ʒu�̐ݒ�
	//�A�j���[�V�����Đ����Ԃ��Z�b�g
	anim->Play(&modelHandle);
}
/// <summary>
/// �ړ�
/// </summary>
void Boss::Move(const VECTOR _playerPos)
{
	//�ڕW�܂ł̃x�N�g��
	VECTOR targetPos = ORIGIN_POS;
	//���K�������x�N�g��
	VECTOR normalizePos = ORIGIN_POS;
	float vectorSize = 0.0f;
	//�����U�����ł͂Ȃ�������U��������
	if (!isAttack)
	{
		//�����x�e���ł͂Ȃ���΍U���p�^�[�������߂Ȃ���
		if (!isRestTime)
		{
			//�v���C���[�Ǝ����̍��W�̃x�N�g���̍������߂�(�ڕW�܂ł̃x�N�g��)
			targetPos = VSub(pos, _playerPos);
			//���̃x�N�g���̑傫�������߂�
			vectorSize = VSize(targetPos);
			if (vectorSize <= 11)
			{
				attackType = 1;
			}
			else
			{
				attackType = GetRand(1) + 2;
			}
			switch (attackType)
			{
			case 1://�ʏ�
				anim->SetAnim(static_cast<int>(AnimationType::NORMAL_ATTACK));
				attackAnimLoopCount = 1;
				break;
			case 2://��]
				anim->SetAnim(static_cast<int>(AnimationType::ROTATE_ATTACK));
				waitBeforeRotateAttack->StartTimer();
				isRotateAttack = false;
				break;
			case 3://�W�����v
				anim->SetAnim(static_cast<int>(AnimationType::JUMP_ATTACK));
				jumpAttackTargetPos = _playerPos;//�ڕW���W��ݒ�
				waitBeforeJunpAttack->StartTimer();
				isJumpAttack = false;
				break;
			default:
				break;
			}
			isAttack = true;
		}
	}
	//�U������������
	else
	{
		//�W�����v�A�^�b�N����
		/*�W�����v�A�^�b�N��
		�U���J�n���ɖڕW���W��ݒ肵�A���̍��W�Ɍ������Ĕ��
		�ǔ��Ȃ��̑���ɁA�ړ����x������*/
		if (attackType == static_cast<int>(AnimationType::JUMP_ATTACK))
		{
			//�^�C�}�[���X�^�[�g���Ă��āA�ڕW���ԂɒB���Ă�����
			if (waitBeforeJunpAttack->getIsStartTimer() && waitBeforeJunpAttack->CountTimer())
			{
				//�W�����v�A�^�b�N��������
				isJumpAttack = true;
				//�^�C�}�[���I��������
				waitBeforeJunpAttack->EndTimer();
			}
			//������Ă�����
			if (isJumpAttack)
			{
				//�v���C���[�Ǝ����̍��W�̃x�N�g���̍������߂�(�ڕW�܂ł̃x�N�g��)
				targetPos = VSub(pos, jumpAttackTargetPos);
				//���̃x�N�g���̑傫�������߂�
				vectorSize = VSize(targetPos);
				//�T�C�Y���萔�����������Ȃ�����
				if (vectorSize <= 5)
				{
					//�x�e�t���O�𗧂Ă�
					isRestTime = true;
					//�U���t���O������
					isAttack = false;
				}
				else
				{
					//�ڕW�܂ł̃x�N�g���𐳋K������
					normalizePos = VNorm(targetPos);
					// �����U�����ɐ��K�������l���[�ɂȂ��Ă����琳�K�������l�Ɉړ��X�s�[�h�������Ĉړ��ʂ�Ԃ�
					moveVec = VScale(normalizePos, status->GetAgi() * -3);
					//�p�x��ς���
					rotate = VGet(0.0f, (float)ChangeRotate(jumpAttackTargetPos), 0.0f);
				}
			}
		}
		else
		{
			/*��]�U��*/
			if (attackType == static_cast<int>(AnimationType::ROTATE_ATTACK))
			{
				//�^�C�}�[���X�^�[�g���Ă��āA�ڕW���ԂɒB���Ă�����
				if (waitBeforeRotateAttack->getIsStartTimer() && waitBeforeRotateAttack->CountTimer())
				{
					//��]�A�^�b�N��������
					isRotateAttack = true;
					//�^�C�}�[���I��������
					waitBeforeRotateAttack->EndTimer();
				}
				//������Ă�����
				if (isRotateAttack)
				{
					//��]�U���p�����Ԃ��X�^�[�g���Ă��Ȃ�������
					if (!rotateAttackLoopTime->getIsStartTimer())
					{
						//�^�C�}�[���X�^�[�g����
						rotateAttackLoopTime->StartTimer();
					}
					//�X�^�[�g���Ă�����
					else
					{
						//�����^�C�}�[���ڕW���ԂɒB������
						if (rotateAttackLoopTime->CountTimer())
						{
							//�x�e�t���O�𗧂Ă�
							isRestTime = true;
							//�U���t���O������
							isAttack = false;
						}
					}
				}
				//�v���C���[�Ǝ����̍��W�̃x�N�g���̍������߂�(�ڕW�܂ł̃x�N�g��)
				targetPos = VSub(pos, _playerPos);
				//���̃x�N�g���̑傫�������߂�
				vectorSize = VSize(targetPos);
				//�ڕW�܂ł̃x�N�g���𐳋K������
				normalizePos = VNorm(targetPos);
				moveVec = VScale(normalizePos, status->GetAgi() * -1);
			}
			//�����ʏ�U�������A�j���[�V�����ύX�t���O����������
			if (attackType == static_cast<int>(AnimationType::NORMAL_ATTACK) && anim->GetIsChangeAnim())
			{
				//�x�e�t���O�𗧂Ă�
				isRestTime = true;
				//�U���t���O������
				isAttack = false;
			}
			//�p�x��ς���
			rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);

		}
	}
	//�x�e�t���O�������Ă��āA�^�C�}�[���X�^�[�g���Ă��Ȃ�������X�^�[�g����
	if (isRestTime && !restTimeAfterAttack->getIsStartTimer())
	{
		//�^�C�}�[���X�^�[�g
		restTimeAfterAttack->StartTimer();
		//�A�j���[�V�������W�����v�A�^�b�N��������
		if (attackType == static_cast<int>(AnimationType::JUMP_ATTACK))
		{
			anim->SetAnim(static_cast<int>(AnimationType::JUMP_IDLE));
		}
		else
		{
			anim->SetAnim(static_cast<int>(AnimationType::IDLE));
		}
	}
	//�X�^�[�g���Ă���Ȃ�
	else
	{
		//�����^�C�}�[���ڕW���ԂɒB������
		if (restTimeAfterAttack->CountTimer())
		{
			isRestTime = false;
			restTimeAfterAttack->EndTimer();
		}
	}
}
/// <summary>
///	�p�x�̕ύX
/// </summary>
float Boss::ChangeRotate(VECTOR playerPos)
{
	//2�_�Ԃ̃x�N�g�����o��(�G�l�~�[����v���C���[)
	VECTOR EP_Vector = VSub(pos, playerPos);
	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}

