////===========================================================================
////@brief �E�B�[�N�G�l�~�[�N���X/�p��
////===========================================================================
//
//#include"WeakEnemy.h"
//#include<math.h>
//#include"Animation.h"
//#include"CharacterStatus.h"
//#include"Timer.h"
////���f���ݒ�
// const VECTOR WeakEnemy::MODEL_SCALE = VGet(0.2f, 0.2f, 0.2f);//���f���̊g�嗦
// const VECTOR WeakEnemy::MODEL_ROTATE = VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//���f���̉�]�l
// 
///// <summary>
///// �R���X�g���N�^
///// </summary>
//WeakEnemy::WeakEnemy(int modelHandle)
// :EnemyBase(modelHandle)
//{
//	//�C���X�^���X�̏�����
//	statusInit = NULL;
//	invincibleTimer = NULL;
//	restTimeAfterAttack = NULL;
//	anim = NULL;
//	//�C���X�^���X�̐���
//	statusInit = new StatusInit();
//	invincibleTimer = new Timer();
//	restTimeAfterAttack = new Timer();
//	anim = new Animation();
//	Init();
//	//�X�P�[���̃Z�b�g
//	MV1SetScale(base.modelHandle, base.scale);
//	//��]�l�̃Z�b�g
//	MV1SetRotationXYZ(base.modelHandle, base.rotate);
//	//�R���W���������\�z
//	MV1SetupCollInfo(base.modelHandle, -1, 1, 1, 1);
//	//�A�j���[�V�����̒ǉ�
//	anim->Add(MV1LoadModel("Data/Animation/WeakEnemy_RunAnim.mv1"), 1);				//����A�j���[�V����
//	anim->Add(MV1LoadModel("Data/Animation/WeakEnemy_StrongAttack.mv1"), 1);		//�U���A�j���[�V����
//	anim->Add(MV1LoadModel("Data/Animation/Enemy_IdleAnim_publi.mv1"), 1);			//�ҋ@�A�j���[�V����
//	anim->Add(MV1LoadModel("Data/Animation/Enemy_DeathAnim_public.mv1"), 1);		//���S�A�j���[�V����
//	//�A�^�b�`����A�j���[�V����
//	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//	//�A�j���[�V�����̃A�^�b�`
//	anim->Attach(&base.modelHandle);
//}
///// <summary>
///// �f�X�g���N�^
///// </summary>
//WeakEnemy::~WeakEnemy()
//{
//	Final();
//}
///// <summary>
///// ������
///// </summary>
//void WeakEnemy::Init()
//{
//	//�K�v��Init�N���X�̌Ăяo��
//	invincibleTimer->Init(9);
//	restTimeAfterAttack->Init(20);
//	status = statusInit->InitWeakEnemyStatus();
//	//�V�������W�̐���
//	base.pos = NewRandomPos();
//	base.rotate		  = MODEL_ROTATE;
//	base.scale		  = MODEL_SCALE;
//	base.radius		  = 8.0f;
//	base.isAttack	  = false;
//	base.isDeath	  = false;
//	base.isHit		  = false;
//	isRestTime		  = false;
//	//�ő�HP�̐ݒ�
//	maxHP = status.HP;
//	base.pos.y = 10.0f;
//}
///// <summary>
///// �X�V
///// </summary>
//void WeakEnemy::Update(VECTOR playerPos)
//{
//	//���G�t���O�������Ă�����
//	if (status.isInvincible)
//	{
//		//�^�C�}�[���n�߂�
//		invincibleTimer->StartTimer();
//		if (invincibleTimer->CountTimer())
//		{
//			invincibleTimer->EndTimer();
//			status.isInvincible = false;
//		}
//	}
//	//�R���W���������X�V
//	MV1RefreshCollInfo(base.modelHandle, -1);
//	
//	//����HP������HP���O�ɂȂ�����
//	if (status.HP <0)
//	{
//		//���݂̃A�j���[�V���������ꂽ�A�j���[�V�����ɂ���
//		if (!base.isDeath)
//		{
//			anim->SetAnim(static_cast<int>(AnimationType::DEATH));
//		}
//		if(anim->GetAnim() == static_cast<int>(AnimationType::DEATH) && anim->GetPlayTime() == 0.0f)
//		{
//			base.isDeath = true;
//			base.pos = DESTROY_POS;
//		}
//	}
//	else
//	{
//		base.pos = VAdd(base.pos, Move(playerPos));//�ړ�
//		MV1SetRotationXYZ(base.modelHandle, base.rotate);//��]�l�̐ݒ�
//	}
//	base.pos.y = 10.0f;
//	MV1SetPosition(base.modelHandle, base.pos);//�ʒu�̐ݒ�
//	//�A�j���[�V�����Đ����Ԃ��Z�b�g
//	anim->Play(&base.modelHandle);
//
//}
///// <summary>
///// �ړ�
///// </summary>
//VECTOR WeakEnemy::Move(VECTOR playerPos)
//{
//	//�ڕW�܂ł̃x�N�g��
//	VECTOR targetPos = ORIGIN_POS;
//	//���K�������x�N�g��
//	VECTOR normalizePos = ORIGIN_POS;
//	//�Ԃ�l�Ƃ��ĕԂ��ړ�����W�i�p�x�L�j
//	VECTOR outPutPos = ORIGIN_POS;
//	float vectorSize = 0.0f;
//	//�v���C���[�Ǝ����̍��W�̃x�N�g���̍������߂�(�ڕW�܂ł̃x�N�g��)
//	targetPos = VSub(base.pos, playerPos);
//	//���̃x�N�g���̑傫�������߂�
//	vectorSize = VSize(targetPos);
//	//�ڕW�܂ł̃x�N�g���𐳋K������
//	normalizePos = VNorm(targetPos);
//	//�����x�N�g���T�C�Y��80�ȉ���������U������
//	if (vectorSize <= 80.0f)
//	{
//		if (!base.isAttack && !isRestTime)
//		{
//			anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
//			attackAnimLoopCount = 100;
//			base.isAttack = true;
//		}
//	}
//	else
//	{
//		if (!base.isAttack && !isRestTime)
//		{
//			//�����x�N�g���T�C�Y��200�ȉ���������v���C���[�Ɍ����đ���
//			if (vectorSize <= 100.0f)
//			{
//				anim->SetAnim(static_cast<int>(AnimationType::RUN));
//			}
//			//�����藣��Ă�����
//			else
//			{
//				anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//			}
//		}
//	}
//	//�U���A�j���[�V���������A�j���[�V�����ύX�t���O�������Ă�����
//	if (base.isAttack)
//	{
//		//�U���񐔂��O�ɂȂ�����x�e����
//		if (attackAnimLoopCount == 0 || vectorSize <= 0)
//		{
//			attackAnimLoopCount = 0;
//			restTimeAfterAttack->StartTimer();
//			base.isAttack = false;
//			isRestTime = true;
//			anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//		}
//		//0����Ȃ���΍U���񐔂����炷
//		else
//		{
//			attackAnimLoopCount--;
//		}
//	}
//	//�����x�e����������
//	else if (isRestTime)
//	{
//		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
//		//�^�C�}�[���I�����Ă�����
//		if (restTimeAfterAttack->CountTimer())
//		{
//			isRestTime = false;
//			restTimeAfterAttack->EndTimer();
//		}
//	}
//	if (anim->GetAnim() != static_cast<int>(AnimationType::IDLE) && vectorSize >=20 &&!isRestTime)
//	{
//		// �����U�����ɐ��K�������l���[�ɂȂ��Ă����琳�K�������l�Ɉړ��X�s�[�h�������Ĉړ��ʂ�Ԃ�
//		outPutPos = VScale(normalizePos, status.AGI * -1);
//		//�p�x��ς���
//		base.rotate = VGet(0.0f, (float)ChangeRotate(playerPos), 0.0f);
//	}
//	return outPutPos;
//}
///// <summary>
/////	�p�x�̕ύX(���f���������Ă��鏉��������z���O)
///// </summary>
//double WeakEnemy::ChangeRotate(VECTOR playerPos)
//{
//	//2�_�Ԃ̃x�N�g�����o��(�G�l�~�[����v���C���[)
//	VECTOR EP_Vector = VSub(base.pos, playerPos);
//	//2�_�̍��W���烉�W�A�������߂�
//	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
//}
//
///// <summary>
///// �m�b�N�o�b�N����
///// </summary>
//void WeakEnemy::Final()
//{
//	if (statusInit)
//	{
//		delete(statusInit);
//		statusInit = NULL;
//	}
//	if (invincibleTimer)
//	{
//		delete(invincibleTimer);
//		invincibleTimer = NULL;
//	}
//	if (restTimeAfterAttack)
//	{
//		delete(restTimeAfterAttack);
//		restTimeAfterAttack = NULL;
//	}
//	if (anim)
//	{
//		delete(anim);
//		anim = NULL;
//	}
//}
