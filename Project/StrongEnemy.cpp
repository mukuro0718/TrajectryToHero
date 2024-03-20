#include"StrongEnemy.h"
#include<math.h>
#include"Animation.h"
#include"CharacterStatus.h"
#include"Timer.h"
#include"BloodParticle.h"
#include"SpawnParticle.h"
#include"Explosion.h"

//���f���ݒ�
const VECTOR   StrongEnemy::MODEL_SCALE	= VGet(0.3f, 0.3f, 0.3f);//���f���̊g�嗦
const VECTOR   StrongEnemy::MODEL_ROTATE	= VGet(0.0f, 90 * DX_PI_F / 180.0f, 0.0f);//���f���̉�]�l
const int      StrongEnemy::CAPSULE_COLOR = GetColor(0, 255, 0);
const int	   StrongEnemy::HOMING_MAGIC_COLOR = GetColor(100, 100, 200);
const int	   StrongEnemy::EXPLOSION_MAGIC_COLOR = GetColor(200, 100, 0);
const VERTEX3D StrongEnemy::INIT_MAGIC_CIRCLE_VERTEX
{
	ORIGIN_POS				,
	VGet(0.0f,1.0f,0.0f)	,
	GetColorU8(255,255,255,150),
	GetColorU8(0,0,0,0),
	1.0f,
	1.0f,
	1.0f,
	1.0f
};
const VECTOR StrongEnemy::MAGIC_CIRCLE_VERTEX_OFFSET[MAGIC_CIRCLE_VERTEX_NUM]
{
		{ 50.0f,1.0f, 50.0f},
		{ 50.0f,1.0f,-50.0f},
		{-50.0f,1.0f,-50.0f},
		{-50.0f,1.0f, 50.0f},
};
const VECTOR StrongEnemy::MAGIC_CIRCLE_VERTEX_OFFSET_2[MAGIC_CIRCLE_VERTEX_NUM]
{
		{ 30.0f,1.0f, 30.0f},
		{ 30.0f,1.0f,-30.0f},
		{-30.0f,1.0f,-30.0f},
		{-30.0f,1.0f, 30.0f},
};
const VERTEX3D StrongEnemy::INIT_VERTEX_FOR_HOMING_MAGIC
{
	ORIGIN_POS				,
	VGet(0.0f,1.0f,0.0f)	,
	GetColorU8(100,100,255,255),
	GetColorU8(100,100,255,255),
	0.0f,
	0.0f,
	0.0f,
	0.0f
};
const VECTOR StrongEnemy::VERTEX_OFFSET_FOR_HOMING_MAGIC[HOMING_MAGIC_VERTEX_NUM]
{
		{  0.0f, 40.0f ,  0.0f},
		{ 15.0f, 25.0f ,  0.0f},
		{  0.0f, 25.0f , 15.0f},
		{-15.0f, 25.0f ,  0.0f},
		{  0.0f, 25.0f ,-15.0f},
		{ 10.0f, 0.0f  ,  0.0f},
		{  0.0f, 0.0f  , 10.0f},
		{-10.0f, 0.0f  ,  0.0f},
		{  0.0f, 0.0f  ,-10.0f},
};
/// <summary>
/// �R���X�g���N�^
/// </summary>
StrongEnemy::StrongEnemy(const VECTOR _spawnPos,const int _modelHandle)
	: EnemyBase(_modelHandle)
	, invincibleTimer(nullptr)
	, restTimeAfterAttack(nullptr)
	, anim(nullptr)
	, randomRest(nullptr)
	, explosion(nullptr)
	, animPlayTime{0.8f,0.5f,0.3f,0.8f,0.8f}
	, attackType(0)
	, homingMoveVec(ORIGIN_POS)
	, explosionMagicRadius(0.0f)
	, magicWaitFrameCount(0)
	, isInitMagicExp(false)
	, magicCircleTexture(0)
	, magicCircleTexture2(0)
{
	//�C���X�^���X�̐���
	Create();
	spawnPos = _spawnPos;
	Init();
	//���f���ݒ�
	MV1SetScale(modelHandle, scale);
	//��]�l�̃Z�b�g
	MV1SetRotationXYZ(modelHandle, rotate);
	//�A�j���[�V�����̒ǉ�
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/RunAnim.mv1")		, 0);			//����A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/HomingMagic.mv1")	, 0);		//�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/ExplosionMagic.mv1"), 0);		//�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/IdleAnim.mv1")		, 0);			//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Strong/DeathAnim.mv1")		, 1);		//���S�A�j���[�V����
	magicCircleTexture = LoadGraph("Data/Texture/Enemy/magicCircle2.png");
	magicCircleTexture2 = LoadGraph("Data/Texture/Enemy/magicCircle.png");
	//�A�^�b�`����A�j���[�V����
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//�A�j���[�V�����̃A�^�b�`
	anim->Attach(&modelHandle);
	for (int i = 0; i < MAGIC_CIRCLE_VERTEX_NUM; i++)
	{
		magicCircleVertex[i] = INIT_MAGIC_CIRCLE_VERTEX;
		magicCircleVertex2[i] = INIT_MAGIC_CIRCLE_VERTEX;
	}
	for (int i = 0; i < HOMING_MAGIC_VERTEX_NUM; i++)
	{
		homingMagicVertex[i] = INIT_VERTEX_FOR_HOMING_MAGIC;
	}
	magicCircleVertex[0].u = 0.0f;
	magicCircleVertex[0].v = 0.0f;
	magicCircleVertex[1].u = 1.0f;
	magicCircleVertex[1].v = 0.0f;
	magicCircleVertex[2].u = 1.0f;
	magicCircleVertex[2].v = 1.0f;
	magicCircleVertex[3].u = 0.0f;
	magicCircleVertex[3].v = 1.0f;

	magicCircleVertex2[0].u = 0.0f;
	magicCircleVertex2[0].v = 0.0f;
	magicCircleVertex2[1].u = 1.0f;
	magicCircleVertex2[1].v = 0.0f;
	magicCircleVertex2[2].u = 1.0f;
	magicCircleVertex2[2].v = 1.0f;
	magicCircleVertex2[3].u = 0.0f;
	magicCircleVertex2[3].v = 1.0f;
}
/// <summary>
/// �쐬
/// </summary>
void StrongEnemy::Create()
{
	//�C���X�^���X�̐���
	invincibleTimer		= new Timer();
	restTimeAfterAttack = new Timer();
	randomRest			= new Timer();
	anim				= new Animation();
	explosion			= new Explosion();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StrongEnemy::~StrongEnemy()
{
	Final();
}
/// <summary>
/// ������
/// </summary>
const void StrongEnemy::Init()
{
	//�K�v��Init�N���X�̌Ăяo��
	invincibleTimer->Init(8);
	restTimeAfterAttack->Init(20);
	randomRest->Init(20);
	status->InitStrongEnemyStatus(1.0f);
	//�V�������W�̐���
	pos = spawnPos;
	rotate = MODEL_ROTATE;
	scale = MODEL_SCALE;
	isAttack = false;
	isDeath = false;
	isHit = false;
	isRestTime = false;
	isRandomWalk = false;
	isRandomRest = false;
	isSpawn = true;//�X�|�[��������
	//�ő�HP�̐ݒ�
	maxHP = status->GetHp();
}
const void StrongEnemy::NewStatus(const float _playerLv)
{
	status->InitStrongEnemyStatus(_playerLv);
	maxHP = status->GetHp();
}

/// <summary>
/// �X�V
/// </summary>
const void StrongEnemy::Update()
{
	if (isSpawn)
	{
		spawnFrameCount++;
		if (spawnFrameCount >= 120)
		{
			isSpawn = false;
			spawnFrameCount = 0;
		}
	}
	else
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
		blood->Update(50);
		//�F�̕ύX
		ChangeColor();
		//�A�j���[�V�����Đ����Ԃ��Z�b�g
		anim->Play(&modelHandle, animPlayTime[anim->GetAnim()]);
	}
	spawnParticle->Init(spawnPos, isSpawn);
	spawnParticle->Update();
}
const void StrongEnemy::DrawAttackRange()
{
	if (isAttack)
	{
		switch (attackType)
		{
			//�z�[�~���O
		case static_cast<int>(AttackType::HOMING_MAGIC):
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawPolygonIndexed3D(magicCircleVertex2, MAGIC_CIRCLE_VERTEX_NUM, MAGIC_CIRCLE_INDEX, MAGIC_CIRCLE_POLYGON_NUM, magicCircleTexture2, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;
			//����
		case static_cast<int>(AttackType::EXPROSION_MAGIC):
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawPolygonIndexed3D(magicCircleVertex, MAGIC_CIRCLE_VERTEX_NUM, MAGIC_CIRCLE_INDEX, MAGIC_CIRCLE_POLYGON_NUM, magicCircleTexture, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;
		}
	}
}
void StrongEnemy::Attack(const VECTOR _playerPos)
{
	VECTOR spherePos = ORIGIN_POS;
	int sphereColor = 0;
	float sphereRadius = 0.0f;
	//�U���t���O�������Ă�����
	if (isAttack)
	{
		magicWaitFrameCount++;
		switch (attackType)
		{
			//�z�[�~���O
		case static_cast<int>(AttackType::HOMING_MAGIC):
			if (magicWaitFrameCount <= BEFORE_HOMING_MAGIC_WAIT_FRAME_COUNT)
			{
				for (int i = 0; i < HOMING_MAGIC_VERTEX_NUM; i++)
				{
					homingMagicVertex[i].pos = VAdd(_playerPos, VERTEX_OFFSET_FOR_HOMING_MAGIC[i]);
				}
				for (int i = 0; i < MAGIC_CIRCLE_VERTEX_NUM; i++)
				{
					magicCircleVertex2[i].pos = VAdd(_playerPos, MAGIC_CIRCLE_VERTEX_OFFSET_2[i]);
				}
				isInitMagicExp = true;
			}
			else if (magicWaitFrameCount > AFTER_HOMING_MAGIC_WAIT_FRAME_COUNT)
			{
				//���݂̃A�j���[�V�������I�����Ă�����
				if (anim->GetAnim() == static_cast<int>(AnimationType::HOMING) && anim->GetPlayTime() == 0.0f)
				{
					//�K�v�ȕϐ�������������
					magicWaitFrameCount = 0;
					spherePos = VGet(0.0f, 500.0f, 0.0f);
					isAttack = false;
					restTimeAfterAttack->StartTimer();
					isRestTime = true;
				}

				spherePos = homingMagicVertex[0].pos;
				spherePos.y = 5.0f;
			}
			sphereColor = HOMING_MAGIC_COLOR;
			sphereRadius = SPHERE_RADIUS;
			break;
			//����
		case static_cast<int>(AttackType::EXPROSION_MAGIC):
			if (magicWaitFrameCount <= BEFORE_EXPLOSION_MAGIC_WAIT_FRAME_COUNT)
			{
				if (!isInitMagicExp)
				{
					for (int i = 0; i < MAGIC_CIRCLE_VERTEX_NUM; i++)
					{
						magicCircleVertex[i].pos = VAdd(pos, MAGIC_CIRCLE_VERTEX_OFFSET[i]);
					}
					isInitMagicExp = true;
				}
			}
			else
			{

				//�X�t�B�A�̒��S���W�����߂�
				spherePos = explosion->GetSphereInfo().centerPos;
				sphereColor = EXPLOSION_MAGIC_COLOR;
				sphereRadius = explosion->GetSphereInfo().radius;

				//���݂̃A�j���[�V���������ꂽ�A�j���[�V�����ɂ���
				if (anim->GetAnim() == static_cast<int>(AnimationType::EXPLOSION) && anim->GetPlayTime() == 0.0f)
				{
					//�K�v�ȕϐ�������������
					magicWaitFrameCount = 0;
					spherePos = VGet(0.0f, 500.0f, 0.0f);
					isAttack = false;
					explosionMagicRadius = 0.0f;
					sphereRadius = explosionMagicRadius;
					restTimeAfterAttack->StartTimer();
					isRestTime = true;
					isInitMagicExp = false;
				}
				explosion->Update(isInitMagicExp, pos);
			}
			break;
		}
	}
	SetUpSphere(spherePos, sphereRadius, sphereColor, true);
}
const void StrongEnemy::DrawMagicSphere()
{
	if (attackType == static_cast<int>(AttackType::EXPROSION_MAGIC))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawSphere(sphereInfo);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		explosion->Draw();
	}
	else
	{
		if (magicWaitFrameCount > AFTER_HOMING_MAGIC_WAIT_FRAME_COUNT)
		{
			DrawSphere(sphereInfo);
			DrawPolygonIndexed3D(homingMagicVertex, HOMING_MAGIC_VERTEX_NUM, HOMING_MAGIC_INDEX, HOMING_MAGIC_POLYGON_NUM, DX_NONE_GRAPH, TRUE);
		}
	}
}
/// <summary>
/// �ړ�
/// </summary>
const void StrongEnemy::Move(VECTOR _playerPos)
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
	targetPos = VSub(_playerPos,pos);
	//���̃x�N�g���̑傫�������߂�
	vectorSize = VSize(targetPos);
	//�ڕW�܂ł̃x�N�g���𐳋K������
	normalizePos = VNorm(targetPos);
		//���łɍU�����Ă��Ȃ��A�x�e���ł͂Ȃ�
	if (!isAttack && !isRestTime)
	{
		//�����x�N�g���T�C�Y���萔�ȉ���������U������
		if (vectorSize <= 50.0f)
		{
			attackType = static_cast<int>(AttackType::EXPROSION_MAGIC);
			attackNum++;
			isAttack = true;
			isMove = false;
			isRandomWalk = false;
			isRandomRest = false;
		}
		else if (vectorSize <= 100.0f)
		{
			attackType = static_cast<int>(AttackType::HOMING_MAGIC);
			isAttack = true;
			isMove = false;
			isRandomWalk = false;
			isRandomRest = false;
		}
		//�����藣��Ă�����
		else
		{
			RandomWalk();
			isMove = false;
			isAttack = false;
		}
	}
	//�U���A�j���[�V���������A�j���[�V�����ύX�t���O�������Ă�����
	if (isAttack)
	{
		Attack(_playerPos);
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
	if (isMove && vectorSize >= 20)
	{
		// �����U�����ɐ��K�������l���[�ɂȂ��Ă����琳�K�������l�Ɉړ��X�s�[�h�������Ĉړ��ʂ�Ԃ�
		moveVec = VScale(normalizePos, status->GetAgi() * -1);
		//�p�x��ς���
		rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
	}
	else if (isAttack && vectorSize >= 20)
	{
		//�p�x��ς���
		rotate = VGet(0.0f, (float)ChangeRotate(_playerPos), 0.0f);
	}
}
/// <summary>
/// �����_���ɕ���
/// </summary>
void StrongEnemy::RandomWalk()
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
///	�p�x�̕ύX
/// </summary>
double StrongEnemy::ChangeRotate(VECTOR playerPos)
{
	//2�_�Ԃ̃x�N�g�����o��(�G�l�~�[����v���C���[)
	VECTOR EP_Vector = VSub(pos, playerPos);
	//2�_�̍��W���烉�W�A�������߂�

	return static_cast<float>(atan2(static_cast<double>(EP_Vector.x), static_cast<double>(EP_Vector.z)));
}
/// <summary>
///	�A�j���[�V�����̕ύX
/// </summary>
void StrongEnemy::ChangeAnim()
{
	//�U�����ړ������Ă��Ȃ��܂��͋x�e����������
	if (!isAttack && !isMove && !isRandomWalk || isRestTime || isRandomRest)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
		sphereInfo.centerPos = VGet(0.0f,500.0f,0.0f);
	}
	//�U������������
	else if (isAttack && !isMove && !isRestTime)
	{
		if (attackType == static_cast<int>(AttackType::HOMING_MAGIC))
		{
			anim->SetAnim(static_cast<int>(AnimationType::HOMING));
		}
		else if (attackType == static_cast<int>(AttackType::EXPROSION_MAGIC))
		{
			anim->SetAnim(static_cast<int>(AnimationType::EXPLOSION));
		}
	}
	//�ړ�����������
	else if (!isAttack && isMove && !isRestTime || !isAttack && isRandomWalk && !isRestTime)
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
void StrongEnemy::Final()
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
