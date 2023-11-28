//===========================================================================
//@brief �v���C���[�N���X / �p��
//===========================================================================
#include"SwordGirl.h"
#include"Common.h"
#include"Timer.h"
#include"Animation.h"
#include"StatusManager.h"
#include"CharacterStatus.h"
#include<math.h>
const VECTOR SwordGirl::FIRST_MODEL_SCALE	= VGet(0.2f, 0.2f, 0.2f);//���f���̊g�嗦
const VECTOR SwordGirl::FIRST_POS = VGet(-50.0f, 0.0f, 0.0f);

/// <summary>
/// ��������R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
SwordGirl::SwordGirl(const int _modelHandle)
	: PlayerBase(_modelHandle)
{
	//����
	Create();
	//������
	Init();
	//�X�P�[���̃Z�b�g
	MV1SetScale(modelHandle, scale);
	//��]�l�̃Z�b�g
	MV1SetRotationXYZ(modelHandle, rotate);
	//�R���W���������\�z
	MV1SetupCollInfo(modelHandle, PLAYER_COLL_INFO.frameIndex, PLAYER_COLL_INFO.xDivNum, PLAYER_COLL_INFO.yDivNum, PLAYER_COLL_INFO.zDivNum);
	//�A�j���[�V�����̒ǉ�
	anim->Add(MV1LoadModel("Data/Animation/Player_RunAnim.mv1"), 0);			//����A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player_StrongAttackAnim.mv1"), 0);	//�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player_StayIdleAnim.mv1"), 0);		//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/1_DeathAnim_public.mv1"), 0);		//���S�A�j���[�V����
	//�A�^�b�`����A�j���[�V����
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//�A�j���[�V�����̃A�^�b�`
	anim->Attach(&modelHandle);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
SwordGirl::~SwordGirl()
{
}
/// <summary>
/// ����
/// </summary>
void SwordGirl::Create()
{
	anim			= NULL;
	stayTimer		= NULL;
	invincibleTimer = NULL;
	anim			= new Animation();
	stayTimer		= new Timer();
	invincibleTimer = new Timer();
}
/// <summary>
/// ������
/// </summary>
void SwordGirl::Init()
{
	stayTimer->Init(STAY_TIMER_TARGET_TIME);
	invincibleTimer->Init(INVINCIBLE_TIMER_TARGET_TIME);
	pos		= ORIGIN_POS;
	rotate		= ORIGIN_POS;
	scale		= FIRST_MODEL_SCALE;
	status->InitPlayerStatus();
	prevLv = static_cast<int>(status->GetLv());
	isMove = false;//�ړ����Ă��邩�ǂ���

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="cameraToPlayer">�J��������v���C���[�̌����x�N�g��</param>
void SwordGirl::Update()
{
	//�R���W���������X�V
	MV1RefreshCollInfo(modelHandle, PLAYER_COLL_INFO.frameIndex);
	//���f���̐ݒ�
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, pos);
	//�A�j���[�V�����̍Đ�
	anim->Play(&modelHandle);
}
void SwordGirl::Move(const VECTOR cameraToPlayer)
{
	/////////////////////////////////////////////////////////
	// ��]�ƈړ�
	/////////////////////////////////////////////////////////
	// �U�������Ă��Ȃ�������
	if (!isAttack)
	{
		//���X�e�B�b�N�̌X�����擾
		GetJoypadAnalogInput(&inputLeftStick.XBuf, &inputLeftStick.YBuf, DX_INPUT_KEY_PAD1);
		//�A�i���O�X�e�B�b�N�̌X�����x�N�g���ɓ����
		//const VECTOR stickDirection = VGet((float)-inputLeftStick.XBuf, 0.0f, (float)inputLeftStick.YBuf);
		VECTOR stickDirection = ORIGIN_POS;
		stickDirection.x = static_cast<float>(-inputLeftStick.XBuf);
		stickDirection.z = static_cast<float>(inputLeftStick.YBuf);
		//�X�e�B�b�N���͂�����΂��̌�̏������s��
		if (inputLeftStick.YBuf != NONE_INPUT_VALUE.XBuf || inputLeftStick.XBuf != NONE_INPUT_VALUE.YBuf)
		{
			isMove = true;
			//���K������
			const VECTOR stickDirectionNormalize = VNorm(stickDirection);
			//���f���p�x�̌v�Z
			rotate.y = (-atan2(cameraToPlayer.z, cameraToPlayer.x) - atan2(stickDirectionNormalize.z, stickDirectionNormalize.x)) - 180.0f * DX_PI_F / 180.0f;
			//���W�v�Z
			pos.x += -sinf(rotate.y) * status->GetAgi();
			pos.z += -cosf(rotate.y) * status->GetAgi();
		}
		else
		{
			isMove = false;
		}
		pos.y = PLAYETR_Y_POS;
		if (pos.x >= PLAYER_RANGE_OF_ACTION.LX)
		{
			pos.x = PLAYER_RANGE_OF_ACTION.LX;
		}
		if (pos.x <= PLAYER_RANGE_OF_ACTION.LZ)
		{
			pos.x = PLAYER_RANGE_OF_ACTION.LZ;
		}
		if (pos.z >= PLAYER_RANGE_OF_ACTION.RX)
		{
			pos.z = PLAYER_RANGE_OF_ACTION.RX;
		}
		if (pos.z <= PLAYER_RANGE_OF_ACTION.RZ)
		{
			pos.z = PLAYER_RANGE_OF_ACTION.RZ;
		}
	}
}

/// <summary>
/// �U��
/// </summary>
/// <param name="_isAttack">�U�������Ă��邩</param>
void SwordGirl::Attack()
{
	//�U�������Ă��Ȃ�
	if (!isAttack)
	{
		int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		//B��������Ă�����U��
		if (input & PAD_INPUT_3)
		{
			anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
			isAttack = true;
		}
		else
		{
			isMove = false;
		}
	}
	//�U���A�j���[�V�������I��������t���O������
	else if (isAttack && anim->GetPlayTime() == FIRST_ANIM_PLAY_TIME)
	{
		isAttack = false;
	}
}

void SwordGirl::AnimChange()
{
	/////////////////////////////////////////////////////////
	// �A�j���[�V�����̕ω�
	/////////////////////////////////////////////////////////
	//�ړ����Ă�����
	if (isMove && !isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));
	}
	//�ҋ@����������
	else if (!isMove && !isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
	//HP���O��������
	if (status->GetHp() < 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}

}