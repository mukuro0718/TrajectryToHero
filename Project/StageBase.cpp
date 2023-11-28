//===========================================================================
//@brief �X�e�[�W�x�[�X�N���X / ���
//===========================================================================
#include"StageBase.h"
#include"Common.h"
const VECTOR StageBase::SCALE = VGet(0.3f, 0.2f, 0.3f);
const VECTOR StageBase::INIT_STAGE_POS = VGet(0.0f,-9.0f,-150.0f);
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="humanModelHandle">���f���n���h��</param>
StageBase::StageBase(int modelHandle)
{
	//���f���n���h���̏�����
	this->modelHandle = 0;
	//���f���̃��[�h
	this->modelHandle = MV1DuplicateModel(modelHandle);
	if (this->modelHandle < 0)
	{
		printfDx("stage�f�[�^�ǂݍ��݂Ɏ��s");
	}
	//���f���̊g�嗦�̑傫��
	MV1SetScale(this->modelHandle, SCALE);
	//���W�̏�����
	pos = INIT_STAGE_POS;
	// ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
	MV1SetupCollInfo(this->modelHandle, -1);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
StageBase::~StageBase()
{
	Delete();
}
/// <summary>
/// �ŏI����
/// </summary>
void StageBase::Delete()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(modelHandle);
}
/// <summary>
/// �`��
/// </summary>
void StageBase::Update()
{
	MV1SetPosition(modelHandle, pos);
}
/// <summary>
/// �`��
/// </summary>
void StageBase::Draw()
{
#ifdef _DEBUG
	DrawSphere3D(ORIGIN_POS, 2, 16, GetColor(255, 255, 0), GetColor(0, 255, 255), FALSE);
#endif
	MV1DrawModel(modelHandle);
}

