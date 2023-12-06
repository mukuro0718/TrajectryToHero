//===========================================================================
//@brief �I�u�W�F�N�g�x�[�X�N���X / ���
//===========================================================================
#include"PlayerBase.h"
#include"CharacterStatus.h"
#include"math.h"
#include"Timer.h"
const int PlayerBase::CAPSULE_COLOR = GetColor(255, 0, 0);
const int PlayerBase::SPHERE_COLOR = GetColor(200, 0, 0);
const VECTOR PlayerBase::SPHERE_POS_OFFSET = VGet(-10.0f,30.0f,0.0f);
const VECTOR PlayerBase::CENTER_POS_OFFSET = VGet(0.0f, 20.0f, 0.0f);
/// <summary>
/// ��������R���X�g���N�^
/// </summary>
/// <param name="modelHandle">�v���C���[���f���n���h��</param>
PlayerBase::PlayerBase(const int _modelHandle)
	:status(nullptr)
	,attackLatency(nullptr)
	, cameraToPlayer(ORIGIN_POS)
	, degrees(INIT_DEGREES)
	, centerPos(ORIGIN_POS)
{
	status = new CharacterStatus();
	attackLatency = new Timer();
	attackLatency->Init(5);
	//���f���̃��[�h
	modelHandle = MV1DuplicateModel(_modelHandle);
	if (modelHandle < INIT_MODELHANDLE)
	{
		printfDx("Player�f�[�^�ǂݍ��݂Ɏ��s");
	}
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBase::~PlayerBase()
{
	Delete();
}
/// <summary>
/// �`��
/// </summary>
void PlayerBase::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);
#ifdef _DEBUG
	SetUpCapsule(pos, CAPSULE_HEIGHT, CAPSULE_RADIUS, CAPSULE_COLOR,false);
	DrawCapsule(capsuleInfo);

	
	//�U�����ł���Γ����蔻��p�X�t�B�A��`�悷��
	if (isAttack)
	{
		if (!attackLatency->getIsStartTimer())
		{
			attackLatency->StartTimer();
		}
		if (attackLatency->CountTimer())
		{
			VECTOR spherePos = pos;

			spherePos.x += -sinf(rotate.y) * 15.0f;
			spherePos.z += -cosf(rotate.y) * 15.0f;
			spherePos.y = 30.0f;
			//�X�t�B�A���̍\�z
			SetUpSphere(spherePos, SPHERE_RADIUS, SPHERE_COLOR, false);
			//�X�t�B�A�̕`��
			DrawSphere(sphereInfo);
		}
	}
	else
	{
		attackLatency->EndTimer();
	}
#endif // _DEBUG

	
}
/// <summary>
/// �ŏI����
/// </summary>
void PlayerBase::Delete()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(modelHandle);
}
/// <summary>
/// ���x���A�b�v���j���[���\������Ă�����ق��̍X�V�������~�߂�
/// </summary>
/// <returns>true/false</returns>
//bool PlayerBase::IsStoppingUpdate()
//{
//	if (statusManager->GetIsShowMenu())
//	{
//		return true;
//	}
//	return false;
//}
/// <summary>
/// HP�v�Z
/// </summary>
void PlayerBase::CalcHP( const float _atk)
{
	//HP�v�Z
	status->CalcHP(_atk);
	isInvincible = true;
}
/// <summary>
/// ���x���A�b�v����
/// </summary>
void PlayerBase::CalcExp(const float _expToGive)
{
	status->CalcExp(_expToGive);
}
const float PlayerBase::GetAtk()
{
	return status->GetAtk();
}
const float PlayerBase::GetHp()
{
	return status->GetHp();
}