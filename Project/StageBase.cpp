#include"StageBase.h"
#include"Common.h"
const VECTOR StageBase::SCALE = VGet(0.3f, 0.2f, 0.3f);
const VECTOR StageBase::INIT_STAGE_POS = VGet(0.0f,0.0f,-150.0f);
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="humanModelHandle">���f���n���h��</param>
StageBase::StageBase(std::vector<int> _data)
{
	//���f���̃��[�h
	model.push_back(MV1DuplicateModel(_data[static_cast<int>(FARM::GROUND)]));
	model.push_back(MV1DuplicateModel(_data[static_cast<int>(FARM::VILLAGE)]));
	model.push_back(MV1DuplicateModel(_data[static_cast<int>(FARM::GATE)]));
	model.push_back(MV1DuplicateModel(_data[static_cast<int>(FARM::PORTAL)]));
	//���f���̊g�嗦�̑傫��
	MV1SetScale(model[static_cast<int>(FARM::GROUND)], SCALE);
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
const void StageBase::Delete()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(model[static_cast<int>(FARM::GROUND)]);
}
/// <summary>
/// �`��
/// </summary>
const void StageBase::Update()
{
	MV1SetPosition(model[static_cast<int>(FARM::GROUND)], pos);
}
/// <summary>
/// �`��
/// </summary>
const void StageBase::Draw()
{
	MV1DrawModel(model[static_cast<int>(FARM::GROUND)]);
}

