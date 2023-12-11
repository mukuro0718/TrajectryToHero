//===========================================================================
//@brief �v���C���[�N���X / �p��
//===========================================================================
#include"SwordGirl.h"
#include"Common.h"
#include"Timer.h"
#include"Animation.h"
#include"StatusManager.h"
#include"CharacterStatus.h"
#include"BlurScreen.h"
#include<math.h>
const VECTOR SwordGirl::FIRST_MODEL_SCALE	= VGet(0.2f, 0.2f, 0.2f);//���f���̊g�嗦
const VECTOR SwordGirl::FIRST_POS = VGet(-50.0f, 0.0f, 0.0f);

/// <summary>
/// ��������R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
SwordGirl::SwordGirl(const int _modelHandle)
	: PlayerBase(_modelHandle)
	, anim(nullptr)
	, stayTimer(nullptr)
	, invincibleTimer(nullptr)
	, isMove(false)
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
	anim->Add(MV1LoadModel("Data/Animation/Player/RunAnim.mv1"), 3);			//����A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player/AttackAnim.mv1"), 3);	//�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player/IdleAnim.mv1"), 3);		//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player/DeathAnim.mv1"), 3);		//���S�A�j���[�V����
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
	anim			= new Animation();
	stayTimer		= new Timer();
	invincibleTimer = new Timer();
	scale = FIRST_MODEL_SCALE;
}
/// <summary>
/// ������
/// </summary>
void SwordGirl::Init()
{
	stayTimer->Init(STAY_TIMER_TARGET_TIME);
	invincibleTimer->Init(INVINCIBLE_TIMER_TARGET_TIME);
	status->InitPlayerStatus();
	prevLv = static_cast<int>(status->GetLv());
}
/// <summary>
/// �ړ��ʂ̕␳
/// </summary>
void SwordGirl::FixMoveVec(const VECTOR _fixVec)
{
	//�ړ��ʂ�␳����
	moveVec = VAdd(moveVec, _fixVec);
}
/// <summary>
/// �X�V
/// </summary>
void SwordGirl::Update()
{
	//�ړ��ʂ����W�ɑ���
	pos = VAdd(pos, moveVec);
	//�X�e�[�W�͈̔͂����ƂɈʒu��␳����
	/*pos.y = PLAYETR_Y_POS;*/
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
	//clsDx();
	//printfDx("HP:%f", status->GetHp());
	Death();
	//�R���W���������X�V
	MV1RefreshCollInfo(modelHandle, PLAYER_COLL_INFO.frameIndex);
	//���f���̐ݒ�
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, pos);
	//�A�j���[�V�����̍Đ�
	anim->Play(&modelHandle);
}
/// <summary>
/// �X�e�[�^�X�X�V
/// </summary>
void SwordGirl::StatusUpdate()
{
	status->Update();
	status->ShowInfo();
}
/// <summary>
/// ���G�t���O�̌v��
/// </summary>
void SwordGirl::CountInvincibleTimer()
{
	//���G�t���O�������Ă�����
	if (isInvincible)
	{
		//�܂��^�C�}�[���n�܂��Ă��Ȃ�������
		if (!invincibleTimer->getIsStartTimer())
		{
			invincibleTimer->StartTimer();
		}
		if (invincibleTimer->CountTimer())
		{
			isInvincible = false;
			invincibleTimer->EndTimer();
		}
	}
}
/// <summary>
/// �ړ�
/// </summary>
void SwordGirl::Move(const VECTOR _cameraToPlayer)
{
	cameraToPlayer = _cameraToPlayer;
	moveVec = ORIGIN_POS;
	/////////////////////////////////////////////////////////
	// ��]�ƈړ�
	/////////////////////////////////////////////////////////
	// �U�������Ă��Ȃ�������
	if (!isAttack)
	{
		//���X�e�B�b�N�̌X�����擾
		GetJoypadAnalogInput(&inputLeftStick.XBuf, &inputLeftStick.YBuf, DX_INPUT_KEY_PAD1);
		//�ϐ��ɓ����
		VECTOR stickDirection = ORIGIN_POS;
		stickDirection.x = static_cast<float>(-inputLeftStick.XBuf);
		stickDirection.z = static_cast<float>(inputLeftStick.YBuf);
		//�X�e�B�b�N���͂�����΂��̌�̏������s��
		if (inputLeftStick.YBuf != NONE_INPUT_VALUE.XBuf || inputLeftStick.XBuf != NONE_INPUT_VALUE.YBuf)
		{
			//���[�u�t���O�𗧂Ă�
			isMove = true;
			//���K������
			const VECTOR stickDirectionNormalize = VNorm(stickDirection);
			//���f���p�x�̌v�Z
			rotate.y = (-atan2(cameraToPlayer.z, cameraToPlayer.x) - atan2(stickDirectionNormalize.z, stickDirectionNormalize.x)) - DX_PI_F;
			//���W�v�Z
			moveVec.x += -sinf(rotate.y) * status->GetAgi();
			moveVec.z += -cosf(rotate.y) * status->GetAgi();
		}
		else
		{
			isMove = false;
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
			isAttack = true;
		}
	}
	//�U���A�j���[�V�������I��������t���O������
	else if (isAttack && anim->GetPlayTime() == FIRST_ANIM_PLAY_TIME)
	{
		isAttack = false;
	}
}
/// <summary>
/// ���S����
/// </summary>
void SwordGirl::Death()
{
	//���S�A�j���[�V�������I��������
	if (anim->GetAnim() == static_cast<int>(AnimationType::DEATH))
	{
		if (anim->GetPlayTime() == 0.0f)
		{
			isDeath = true;
		}
	}
}
/// <summary>
/// �A�j���[�V�����̕ύX
/// </summary>
void SwordGirl::AnimChange()
{
	/////////////////////////////////////////////////////////
	// �A�j���[�V�����̕ω�
	/////////////////////////////////////////////////////////
	//�ړ����Ă�����
	if (isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::ATTACK));
	}
	else if (isMove && !isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));
	}
	//�ҋ@����������
	else if (!isMove && !isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
	//HP���O��������
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}
}
/// <summary>
/// ���j���[�̕`��
/// </summary>
void SwordGirl::DrawMenu()
{
	status->Draw();
}
/// <summary>
/// �X�e�[�^�X�N���X��isShowMenu��Ԃ�
/// </summary>
/// <returns></returns>
const bool SwordGirl::GetIsShowStatusMenu()
{
	return status->GetIsShowMenu();
}