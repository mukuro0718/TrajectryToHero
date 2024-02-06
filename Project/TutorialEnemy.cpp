#include "TutorialEnemy.h"
#include"CharacterStatus.h"
#include"Animation.h"
#include"Common.h"
#include"StrongerUI.h"
#include"Shadow.h"
#include"BloodParticle.h"
#include"Load.h"
#include"Timer.h"
const int TutorialEnemy::CAPSULE_COLOR = GetColor(255, 0, 0);
const COLOR_F TutorialEnemy::CHANGE_DIF_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�f�B�t���[�Y�J���[
const COLOR_F TutorialEnemy::CHANGE_SPC_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�X�y�L�����J���[
const COLOR_F TutorialEnemy::CHANGE_EMI_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�G�~�b�V�u�J���[
const COLOR_F TutorialEnemy::CHANGE_AMB_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�A���r�G���g�J���[

/// <summary>
/// �R���X�g���N�^
/// </summary>
TutorialEnemy::TutorialEnemy(const int _modelHandle)
	:pos(INIT_POS)
	, modelHandle(_modelHandle)
	, status(nullptr)
	, anim(nullptr)
	, shadow(nullptr)
	, blood(nullptr)
	, strongerUI(nullptr)
	, isDeath(false)
	, isInvincible(false)
	, frameCount(0)
	, isDamage(false)
	, initCount(0)
	, isRespawn(false)
	,changeColorTimer(nullptr)
	, bloodBaseDir(ORIGIN_POS)
	, isChangeColor(false)
	, isPrevColorChange(false)
	, materialNum(0)
{
	int bloodParticle = 0;
	auto& load = Load::GetInstance();
	load.GetEnemyParticleData(&bloodParticle);
	blood = new BloodParticle(bloodParticle);
	MV1SetScale(modelHandle, SCALE);
	MV1SetRotationXYZ(modelHandle, ROTATE);
	MV1SetPosition(modelHandle, pos);
	status = new CharacterStatus();
	status->InitTutorialStatus(initCount);
	initCount++;
	anim = new Animation();
	shadow = new Shadow();
	strongerUI = new StrongerUI();
	changeColorTimer = new Timer();
	changeColorTimer->Init(2);
	//�A�j���[�V�����̒ǉ�
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/IdleAnim.mv1"), 1);			//�ҋ@�A�j���[�V����
	anim->Add(MV1LoadModel("Data/Animation/Enemy/Weak/DeathAnim.mv1"), 1);		//���S�A�j���[�V����
	//�A�^�b�`����A�j���[�V����
	anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	//�A�j���[�V�����̃A�^�b�`
	anim->Attach(&modelHandle);
	SetUpCapsule();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
TutorialEnemy::~TutorialEnemy()
{
	if (status)
	{
		delete(status);
	}
	if (anim)
	{
		delete(anim);
	}
}
/// <summary>
/// �X�V
/// </summary>
void TutorialEnemy::Update()
{
	blood->UpdateGravity();
	if (isInvincible)
	{
		blood->Init(bloodBaseDir, pos);
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
		isDamage = true;
	}
	ChangeAnim();
	if (!isDeath)
	{
		anim->Play(&modelHandle);
	}
	else
	{
		if (!isRespawn)
		{
			frameCount++;
			if (frameCount > MAX_FRAME_COUNT)
			{
				pos = INIT_POS;
				isDeath = false;
				status->InitTutorialStatus(initCount);
				SetUpCapsule();
				isRespawn = true;
			}
		}
	}
	strongerUI->Update(pos);
	blood->Update(60);
	ChangeColor();
	MV1SetPosition(modelHandle, pos);
}
/// <summary>
/// �`��
/// </summary>
void TutorialEnemy::Draw(const float _playerLv)
{
	MV1DrawModel(modelHandle);
	if (isDamage)
	{
		strongerUI->Draw(_playerLv, status->GetLv());
	}
	if (status->GetHp() >= 0 && !isDamage)
	{
		blood->Draw();
	}
}
const void TutorialEnemy::DrawShadow(const int _stageModelHandle)
{
	shadow->Draw(_stageModelHandle,pos,1000.0f,20.0f);
}
/// <summary>
/// �J�v�Z�����̍\�z
/// </summary>
void TutorialEnemy::SetUpCapsule()
{
	capsule.topPos = pos;
	capsule.topPos.y += 30.0f;
	capsule.underPos = pos;
	capsule.radius = RADIUS;
	capsule.divNum = 16;
	capsule.difColor = CAPSULE_COLOR;
	capsule.spcColor = CAPSULE_COLOR;
	capsule.fillFlag = false;
}
/// <summary>
/// HP�̌v�Z
/// </summary>
float TutorialEnemy::CalcHP(const float _atk, const VECTOR _attackPos)
{
	isInvincible = true;
	bloodBaseDir = VSub(pos, _attackPos);
	return status->CalcHP(_atk);
}
const void TutorialEnemy::InitExpToGive()
{
	status->InitExpToGive();
}
/// <summary>
///	�A�j���[�V�����̕ύX
/// </summary>
void TutorialEnemy::ChangeAnim()
{
	//����HP��0�ȉ��ɂȂ�����
	if (status->GetHp() <= 0)
	{
		anim->SetAnim(static_cast<int>(AnimationType::DEATH));
	}
	else
	{
		anim->SetAnim(static_cast<int>(AnimationType::IDLE));
	}
}
/// <summary>
/// �F�̕ύX
/// </summary>
void TutorialEnemy::ChangeColor()
{
	if (isInvincible)
	{
		if (!isChangeColor && status->GetHp() > 0)
		{
			changeColorTimer->StartTimer();
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
		//�t���O������
		isChangeColor = false;
		isPrevColorChange = false;
		changeColorTimer->EndTimer();
	}
	//�F��ύX���Ă�����
	if (!isPrevColorChange && isChangeColor && changeColorTimer->CountTimer())
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
		isPrevColorChange = true;
	}
}
