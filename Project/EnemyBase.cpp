//===========================================================================
//@brief �G�l�~�[�x�[�X�N���X / ���
//===========================================================================
#include"EnemyBase.h"
#include"Common.h"
#include"Timer.h"

const VECTOR  EnemyBase::DESTROY_POS = VGet(500.0f, 500.0f, 500.0f);
const COLOR_F EnemyBase::CHANGE_DIF_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�f�B�t���[�Y�J���[
const COLOR_F EnemyBase::CHANGE_SPC_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�X�y�L�����J���[
const COLOR_F EnemyBase::CHANGE_EMI_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�G�~�b�V�u�J���[
const COLOR_F EnemyBase::CHANGE_AMB_COLOR = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);//�A���r�G���g�J���[

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="humanModelHandle">�R�s�[���郂�f���n���h��</param>
EnemyBase::EnemyBase(int _modelHandle)
	:changeColorTimer(nullptr)
	, status(nullptr)
	, isChangeColor(false)
	,isPrevColorChange(false)
	,materialNum(0)
	,spawnPos(ORIGIN_POS)
	,bloodBaseDir(ORIGIN_POS)
{
	changeColorTimer = new Timer();
	changeColorTimer->Init(2);
	status = new CharacterStatus();
	//effectManager = new EffectManager();
	maxHP = 0;
	//���f���̃R�s�[
	modelHandle = MV1DuplicateModel(_modelHandle);
	if (modelHandle < 0)
	{
		printfDx("Enemy�f�[�^�ǂݍ��݂Ɏ��s");
	}
	isFarmBossEnemyPos = true;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBase::~EnemyBase()
{
	Final();
}
/// <summary>
/// �ړ��ʂ̕␳
/// </summary>
void EnemyBase::FixMoveVec(const VECTOR _fixVec)
{
	//�ړ��ʂ�␳����
	moveVec = VAdd(moveVec, _fixVec);
}

/// <summary>
/// �폜
/// </summary>
void EnemyBase::Final()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(modelHandle);
}
/// <summary>
/// �`��
/// </summary>
void EnemyBase::Draw(VECTOR playerPos)
{
#ifdef _DEBUG
	DrawCapsule(capsuleInfo);
	DrawSphere(sphereInfo);
#endif // _DEBUG
	//�v���C���[�ƃG�l�~�[�̋���
	float distance = VSize(VSub(playerPos, pos));
	//�G�t�F�N�g�̕`��
	//effectManager->SpreadEffectManager(pos, isInvincible);
	MV1DrawModel(modelHandle);
	//printfDx("X:%f Y:%f Z:%f\n", MV1GetPosition(modelHandle).x, MV1GetPosition(modelHandle).y, MV1GetPosition(modelHandle).z);
}
float EnemyBase::CalcHP(const float _atk, const VECTOR _attackerPos)
{
	isInvincible = true;
	bloodBaseDir = VSub(pos, _attackerPos);
	//HP�v�Z
	return status->CalcHP(_atk);
}
void EnemyBase::InitExpToGive()
{
	status->InitExpToGive();
}
/// <summary>
/// �F�̕ύX
/// </summary>
void EnemyBase::ChangeColor()
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
