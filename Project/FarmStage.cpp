//===========================================================================
//@brief �n�ʃN���X/�p��
//===========================================================================
#include"FarmStage.h"
#include"Common.h"
const VECTOR FarmStage::SCALE = VGet(0.3f, 0.3f, 0.3f);
const VECTOR FarmStage::INIT_STAGE_POS = VGet(0.0f, 0.0f, -150.0f);
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="humanModelHandle">���f���n���h��</param>
FarmStage::FarmStage(std::vector<int> _data)
	:portalRotate(0.0f)
	,isShowGate(false)
{
	//���f���̃��[�h
	for (int i = 0; i < MODEL_NUM; i++)
	{
		model.push_back(MV1DuplicateModel(_data[i]));
	}
	Init();
}
const void FarmStage::Init()
{
	//���W�̏�����
	for (int i = 0; i < MODEL_NUM; i++)
	{
		rotate.push_back(ORIGIN_POS);
		scale.push_back(SCALE);
		pos.push_back(INIT_STAGE_POS);
	}

	//���W�̃Z�b�g
	pos[static_cast<int>(FARM::GATE)] = VGet(0.0f, -20.0f, 500.0f);
	pos[static_cast<int>(FARM::PORTAL)] = VGet(0.0f, 40.0f, 550.0f);
	for (int i = 0; i < MODEL_NUM; i++)
	{
		MV1SetPosition(model[i], pos[i]);
		MV1SetRotationXYZ(model[i], rotate[i]);
		MV1SetScale(model[i], scale[i]);
	}

}
/// <summary>
/// �f�X�g���N�^
/// </summary>
FarmStage::~FarmStage()
{
	Delete();
}
/// <summary>
/// �ŏI����
/// </summary>
const void FarmStage::Delete()
{
	pos.clear();
	model.clear();
	// ���f���̃A�����[�h.
	//MV1DeleteModel(model[static_cast<int>(FARM::GROUND)]);
	//MV1DeleteModel(model[static_cast<int>(FARM::GATE)]);
	//MV1DeleteModel(model[static_cast<int>(FARM::PORTAL)]);
}
/// <summary>
/// �`��
/// </summary>
const void FarmStage::Update(const int _playerLv)
{
	if (_playerLv > 5)
	{
		isShowGate = true;
	}
	portalRotate += 1.0f;
	rotate[static_cast<int>(FARM::PORTAL)] = VGet( 0.0f, 0.0f,portalRotate * (DX_PI_F / 180.0f));
	MV1SetRotationXYZ(model[static_cast<int>(FARM::PORTAL)], rotate[static_cast<int>(FARM::PORTAL)]);
}
/// <summary>
/// �`��
/// </summary>
const void FarmStage::Draw(const bool _isFarm)
{
	MV1DrawModel(model[static_cast<int>(FARM::GROUND)]);
	if (_isFarm)
	{
		if (isShowGate)
		{
			MV1DrawModel(model[static_cast<int>(FARM::GATE)]);
			MV1DrawModel(model[static_cast<int>(FARM::PORTAL)]);
		}
	}
}

