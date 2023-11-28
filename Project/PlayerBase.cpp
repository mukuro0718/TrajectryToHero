//===========================================================================
//@brief �I�u�W�F�N�g�x�[�X�N���X / ���
//===========================================================================
#include"PlayerBase.h"
#include"CharacterStatus.h"

const int PlayerBase::CAPSULE_COLOR = GetColor(255, 0, 0);

/// <summary>
/// ��������R���X�g���N�^
/// </summary>
/// <param name="modelHandle">�v���C���[���f���n���h��</param>
PlayerBase::PlayerBase(const int _modelHandle)
{
	status = NULL;
	status = new CharacterStatus();
	modelHandle = INIT_MODELHANDLE;	//���f���n���h���̏�����
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