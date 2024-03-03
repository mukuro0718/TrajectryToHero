//===========================================================================
//@brief �v���C���[�N���X / �p��
//===========================================================================
#include"SwordGirl.h"
#include"Common.h"
#include"Timer.h"
#include"Animation.h"
#include"StatusManager.h"
#include"CharacterStatus.h"
#include"BloodParticle.h"
#include<math.h>
const VECTOR  SwordGirl::FIRST_MODEL_SCALE	= VGet(0.2f, 0.2f, 0.2f);//���f���̊g�嗦
const VECTOR  SwordGirl::FIRST_POS			= VGet(-50.0f, 0.0f, 0.0f);
const COLOR_F SwordGirl::CHANGE_DIF_COLOR	= GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�f�B�t���[�Y�J���[
const COLOR_F SwordGirl::CHANGE_SPC_COLOR	= GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�X�y�L�����J���[
const COLOR_F SwordGirl::CHANGE_EMI_COLOR	= GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�G�~�b�V�u�J���[
const COLOR_F SwordGirl::CHANGE_AMB_COLOR	= GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�A���r�G���g�J���[
const int SwordGirl::FONT_COLOR = GetColor(150, 150, 150);
/// <summary>
/// ��������R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
SwordGirl::SwordGirl(const int _modelHandle, const int _frameImage, const int _hpImage, const int _expImage,const int _font)
	: PlayerBase	 (_modelHandle)
	, anim			 (nullptr)
	, stayTimer		 (nullptr)
	, invincibleTimer(nullptr)
	, isMove		 (false)
	, isChangeColor	 (false)
	, isAvoidance	 (false)
	, frameImage	 (_frameImage)
	, hpImage		 (_hpImage)
	, expImage		 (_expImage)
	, materialNum	 (0)
	, playerDir		 (ORIGIN_POS)
	, font			 (_font)
	, animPlayTime	 { 0.8f,0.6f,0.6f,0.8f,0.8f,0.8f }
	, isKnockBack	 (false)
	, knockBackMoveVec(ORIGIN_POS)
	, knockBackFrameCount(0)
	, multSpeed(1.0f)
{
	//����
	Create();
	//������
	Init();
	//�X�P�[���̃Z�b�g
	MV1SetScale(modelHandle, scale);
	//��]�l�̃Z�b�g
	MV1SetRotationXYZ(modelHandle, rotate);
	//�A�j���[�V�����̒ǉ�
	anim->Add(MV1LoadModel("Data/Animation/Player/RunAnim.mv1"		), 3);//����A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player/AttackAnim.mv1"	), 3);//�U���A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player/KnockBackAnim.mv1"), 1);//���݃A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player/AvoidAnim.mv1"	), 1);//����A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player/IdleAnim.mv1"		), 3);//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Player/DeathAnim.mv1"	), 3);//���S�A�j���[�V����
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
	nowHP.y = 30;
	prevHP.y = 30;
	prevHP.x = 300;
	nowEXP.y = 30;
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
	blood->UpdateGravity();
	switch (status->GetAgiUpCount())
	{
	case 1:
		multSpeed = 2.0f;
		break;
	case 2:
		animPlayTime[static_cast<int>(AnimationType::ATTACK)] = 0.7f;
		break;
	case 3:
		animPlayTime[static_cast<int>(AnimationType::ATTACK)] = 0.8f;
		break;
	case 4:
		animPlayTime[static_cast<int>(AnimationType::ATTACK)] = 0.9f;
		break;
	case 5:
		animPlayTime[static_cast<int>(AnimationType::ATTACK)] = 1.0f;
		break;
	}
	if (isInvincible)
	{
		blood->Init(bloodBaseDir, pos);
	}
	if (status->GetHp() > 0)
	{
		//�ړ��ʂ����W�ɑ���
		pos = VAdd(pos, moveVec);
	}
	//�X�e�[�W�͈̔͂����ƂɈʒu��␳����
	if (pos.x >= PLAYER_RANGE_OF_ACTION.LX)
	{
		pos.x = PLAYER_RANGE_OF_ACTION.LX;
	}
	if (pos.x <= PLAYER_RANGE_OF_ACTION.RX)
	{
		pos.x = PLAYER_RANGE_OF_ACTION.RX;
	}
	if (pos.z >= PLAYER_RANGE_OF_ACTION.LZ)
	{
		pos.z = PLAYER_RANGE_OF_ACTION.LZ;
	}
	if (pos.z <= PLAYER_RANGE_OF_ACTION.RZ)
	{
		pos.z = PLAYER_RANGE_OF_ACTION.RZ;
	}
	//�̗͂̉�
	//status->CalcExp
	//���S����
	Death();
	//���f���̐ݒ�
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, pos);
	blood->Update(15);
	ChangeColor();//���f���̐F��ς���
	//�A�j���[�V�����̍Đ�
	anim->Play(&modelHandle, animPlayTime[anim->GetAnim()]);
}
/// <summary>
/// �X�e�[�^�X�X�V
/// </summary>
void SwordGirl::StatusUpdate(const VECTOR _bonfirePos)
{
	VECTOR fireToPlayer = VSub(_bonfirePos,pos);
	float vecSize = VSize(fireToPlayer);
	bool isShowMenu = false;
	if(vecSize < 30.0f)
	{
		isShowMenu = true;
	}
	status->Update(isShowMenu);
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
/// �F�̕ύX
/// </summary>
void SwordGirl::ChangeColor()
{
	if (isInvincible)
	{
		if (!isChangeColor)
		{
			//�}�e���A���̐����擾
			materialNum = MV1GetMaterialNum(modelHandle);
			//�����̃}�e���A����ۑ����Ă���
			for (int i = 0; i < materialNum; i++)
			{
				difColorInfo.push_back(MV1GetMaterialDifColor(modelHandle, i));
				spcColorInfo.push_back(MV1GetMaterialSpcColor(modelHandle, i));
				emiColorInfo.push_back(MV1GetMaterialEmiColor(modelHandle, i));
				ambColorInfo.push_back(MV1GetMaterialAmbColor(modelHandle, i));
			}
			//�ԐF�ɂȂ�悤�Ƀ}�e���A���̐F��������
			for (int i = 0; i < materialNum; i++)
			{
				MV1SetMaterialDifColor(modelHandle, i, CHANGE_DIF_COLOR);
				MV1SetMaterialSpcColor(modelHandle, i, CHANGE_SPC_COLOR);
				MV1SetMaterialEmiColor(modelHandle, i, CHANGE_EMI_COLOR);
				MV1SetMaterialAmbColor(modelHandle, i, CHANGE_AMB_COLOR);
			}
			//�F�ύX�t���O�𗧂Ă�
			isChangeColor = true;
		}
	}
	else
	{
		//�F��ύX���Ă�����
		if (isChangeColor)
		{
			//�}�e���A���̐F�����Ƃɖ߂�
			for (int i = 0; i < materialNum; i++)
			{
				MV1SetMaterialDifColor(modelHandle, i, difColorInfo[i]);
				MV1SetMaterialSpcColor(modelHandle, i, spcColorInfo[i]);
				MV1SetMaterialEmiColor(modelHandle, i, emiColorInfo[i]);
				MV1SetMaterialAmbColor(modelHandle, i, ambColorInfo[i]);
			}
			//�x�N�^�[�̗v�f���O�ɂ���
			difColorInfo.clear();
			spcColorInfo.clear();
			emiColorInfo.clear();
			ambColorInfo.clear();
			//�t���O������
			isChangeColor = false;
		}
	}
}
/// <summary>
/// �ړ�
/// </summary>
void SwordGirl::Move(const VECTOR _cameraToPlayer)
{
	if (isAvoidance && anim->GetIsChangeAnim())
	{
		isAvoidance = false;
	}

	if (status->GetHp() > 0)
	{
		cameraToPlayer = _cameraToPlayer;
		moveVec = ORIGIN_POS;
		// �U���܂��͔�e�����Ă��Ȃ�������
		if (!isAttack && !isInvincible && !isKnockBack && !isAttackReadying)
		{
			/*���*/
			int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
			//B��������Ă�����U��
			if (input & PAD_INPUT_2)
			{
				isAvoidance = true;
				speed = multSpeed * 1.3f;
			}
			if (!isAvoidance)
			{
				/*��]�ƈړ�*/
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
					//���f���p�x�̌v�Z(�v���C���[�̑O�����x�N�g������X�e�B�b�N�̌X������o�����x�N�g���̊p�x���o��)
					rotate.y = (-atan2(cameraToPlayer.z, cameraToPlayer.x) - atan2(stickDirectionNormalize.z, stickDirectionNormalize.x)) - DX_PI_F;
					//�ړ��x�N�g���v�Z
					moveVec.x += -sinf(rotate.y) * multSpeed;
					moveVec.z += -cosf(rotate.y) * multSpeed;
					playerDir = VNorm(playerDir);
				}
				else
				{
					isMove = false;
				}
			}
			else
			{
				moveVec.x += -sinf(rotate.y) * multSpeed;
				moveVec.z += -cosf(rotate.y) * multSpeed;
			}
		}
		if (isKnockBack)
		{
			KnockBack();
		}
	}
}
const void SwordGirl::OnKnockBack(const VECTOR _targetPos)
{
	isKnockBack = true;
	knockBackMoveVec = VSub(pos, _targetPos);
	knockBackMoveVec = VNorm(knockBackMoveVec);
	knockBackMoveVec = VScale(knockBackMoveVec, 5.0f);
}
void SwordGirl::KnockBack()
{
	if (isKnockBack)
	{
		knockBackFrameCount++;
		moveVec = knockBackMoveVec;
		if (knockBackFrameCount >= 3)
		{
			knockBackFrameCount = 0;
			knockBackMoveVec = ORIGIN_POS;
			isKnockBack = false;
		}
	}
}
/// <summary>
/// �U��
/// </summary>
/// <param name="_isAttack">�U�������Ă��邩</param>
void SwordGirl::Attack()
{
	clsDx();
	printfDx("%d", isAttack);
	if (!isInvincible)
	{
		//�U�������Ă��Ȃ�
		if (!isAttackReadying)
		{
			int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
			//X��������Ă�����U��
			if (input & PAD_INPUT_3)
			{
				//isAttack = true;
				isAttackReadying = true;
				attackNum++;
			}
		}
		//�U���A�j���[�V�������I��������t���O������
		else
		{
			waitAttackFrameCount++;
			if (waitAttackFrameCount >= 30 && waitAttackFrameCount <= 40)
			{
				
				isAttack = true;
			}
			else
			{
				isAttack = false;
			}
		}
		if (isAttackReadying && anim->GetPlayTime() == FIRST_ANIM_PLAY_TIME)
		{
			waitAttackFrameCount = 0;
			isAttack = false;
			isAttackReadying = false;
		}
	}
	else
	{
		waitAttackFrameCount = 0;
		isAttackReadying = false;
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
	if (isAttack || isAttackReadying)
	{
		anim->SetAnim(static_cast<int>(AnimationType::ATTACK));//�U��
	}
	else if (isInvincible)
	{
		isAvoidance = false;
		anim->SetAnim(static_cast<int>(AnimationType::FRIGHTENING));//����
	}
	else if (isAvoidance)
	{
		anim->SetAnim(static_cast<int>(AnimationType::AVOIDANCE));//���
	}
	else if (isMove)
	{
		anim->SetAnim(static_cast<int>(AnimationType::RUN));//����
	}
	//�ҋ@����������
	else if (!isMove && !isAttack)
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));//�ҋ@
	}
	//HP���O��������
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));//���S
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
/// <summary>
/// UI�̍X�V
/// </summary>
void SwordGirl::UpdateUI()
{
	//�ő�HP�����߂�
	//���݂�HP�����߂�
	//�w��������i���F���݂�HP/�ő�HP * 100�j
	nowHP.x = static_cast<int>(status->GetHp()/ status->GetMaxHP() * 300.0f);
	nowEXP.x = static_cast<int>(status->GetExp() / status->GetNeedExp() * 300.0f);
	if (nowHP.x < 0)
	{
		nowHP.x = 0;
	}

}
/// <summary>
/// UI�̕`��
/// </summary>
void SwordGirl::DrawUI()
{
	//�e�L�X�g�̕\��
	DrawFormatStringToHandle(25, 20, FONT_COLOR, font, "LV %d", static_cast<int>(status->GetLv()));
	DrawStringToHandle(20, 60, "HP", FONT_COLOR, font);
	DrawStringToHandle(20, 100, "EXP", FONT_COLOR, font);
	//�t���[���̕`��
	DrawExtendGraph(static_cast<int>(HP_FRAME_POS.LX),  static_cast<int>(HP_FRAME_POS.LZ),  static_cast<int>(HP_FRAME_POS.RX),  static_cast<int>(HP_FRAME_POS.RZ),  frameImage, TRUE);
	DrawExtendGraph(static_cast<int>(EXP_FRAME_POS.LX), static_cast<int>(EXP_FRAME_POS.LZ), static_cast<int>(EXP_FRAME_POS.RX), static_cast<int>(EXP_FRAME_POS.RZ), frameImage, TRUE);
	//HP�o�[�̕\��
	DrawExtendGraph(HP_BAR_POS.x, HP_BAR_POS.y, HP_BAR_POS.x + nowHP.x, HP_BAR_POS.y + nowHP.y, hpImage, TRUE);
	DrawExtendGraph(EXP_BAR_POS.x, EXP_BAR_POS.y, EXP_BAR_POS.x + nowEXP.x, EXP_BAR_POS.y + nowEXP.y, expImage, TRUE);
}
void SwordGirl::ReSpawn()
{
	pos = ORIGIN_POS;
	status->PhysicalRecovery();
	isDeath = false;
}
void SwordGirl::PhysicalRecovery()
{
	status->PhysicalRecovery();
}
const int SwordGirl::GetAtkUpCount()const
{
	return status->GetAtkUpCount();
}
const int SwordGirl::GetAgiUpCount()const
{
	return status->GetAgiUpCount();
}
const int SwordGirl::GetDefUpCount()const
{
	return status->GetDefUpCount();
}
const bool SwordGirl::GetIsBonfireMenu()const
{
	return status->GetIsBonfireMenu();
}
