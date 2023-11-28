#include "Skydome.h"
#include"Load.h"

const VECTOR Skydome::SCALE = VGet(1.5f,1.5f,1.5f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
Skydome::Skydome()
{
	Init();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Skydome::~Skydome()
{

}
/// <summary>
/// ������
/// </summary>
void Skydome::Init()
{
	pos = ORIGIN_POS;
	modelHandle = 0;
	auto& load = Load::GetInstance();
	load.GetSkydomeData(&modelHandle);
	MV1SetPosition(modelHandle, pos);
	MV1SetScale(modelHandle,SCALE);
}
/// <summary>
/// �`��
/// </summary>
void Skydome::Draw()
{
	MV1DrawModel(modelHandle);
}