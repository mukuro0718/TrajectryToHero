//===========================================================================
//@brief �I�u�W�F�N�g�x�[�X�N���X / ���
//===========================================================================
#include"PlayerBase.h"
#include"CharacterStatus.h"
#include"math.h"
const int PlayerBase::CAPSULE_COLOR = GetColor(255, 0, 0);
const int PlayerBase::SPHERE_COLOR = GetColor(200, 0, 0);
/// <summary>
/// ��������R���X�g���N�^
/// </summary>
/// <param name="modelHandle">�v���C���[���f���n���h��</param>
PlayerBase::PlayerBase(const int _modelHandle)
	:status(nullptr)
	, cameraToPlayer(ORIGIN_POS)
{
	status = new CharacterStatus();
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
#ifdef _DEBUG
	SetUpCapsule(pos, CAPSULE_HEIGHT, CAPSULE_RADIUS, CAPSULE_COLOR,false);
	DrawCapsule(capsuleInfo);
	VECTOR swordPos = MV1GetFramePosition(modelHandle, 47);
	//swordPos.y += 5.0f;
	//swordPos.x += -sinf(rotate.y) * 18.0f;
	//swordPos.z += -cosf(rotate.y) * 18.0f;
	SetUpSphere(swordPos , SPHERE_RADIUS, SPHERE_COLOR, false);
	DrawSphere(sphereInfo);
#endif // _DEBUG

	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);
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