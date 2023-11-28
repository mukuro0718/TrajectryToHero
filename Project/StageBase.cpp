#include"StageBase.h"
#include"Common.h"
const VECTOR StageBase::SCALE = VGet(0.3f, 0.2f, 0.3f);
const VECTOR StageBase::INIT_STAGE_POS = VGet(0.0f,-9.0f,-150.0f);
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="humanModelHandle">���f���n���h��</param>
StageBase::StageBase(int _modelHandle)
{
	//���f���n���h���̏�����
	modelHandle = 0;
	//���f���̃��[�h
	modelHandle = MV1DuplicateModel(_modelHandle);
	if (modelHandle < 0)
	{
		printfDx("stage�f�[�^�ǂݍ��݂Ɏ��s");
	}
	//���f���̊g�嗦�̑傫��
	MV1SetScale(modelHandle, SCALE);
	//���W�̏�����
	pos = INIT_STAGE_POS;
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
	MV1DrawModel(modelHandle);
}

