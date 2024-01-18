//===========================================================================
//@brief �X�e�[�W�}�l�[�W���[/�Ǘ�
//===========================================================================

#include"StageManager.h"
#include"FarmStage.h"
#include"Load.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
StageManager::StageManager()
{
	farm = NULL;
	//���f���̃��[�h
	auto& load = Load::GetInstance();
	load.GetStageData(&farmStageData);
	Create();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
StageManager::~StageManager()
{
	Delete();
}
/// <summary>
/// ����
/// </summary>
void StageManager::Create()
{
	//�C���X�^���X�̐���
	farm = new FarmStage(farmStageData);
}
/// <summary>
/// �X�V
/// </summary>
void StageManager::Update()
{
	farm->Update();
}
/// <summary>
/// �Ǘ����邷�ׂẴI�u�W�F�N�g��`��
/// </summary>
void StageManager::Draw()
{
	farm->Draw();
}
/// <summary>
/// �폜
/// </summary>
void StageManager::Delete()
{
	delete(farm);//�n�ʂ̍폜
}
const int StageManager::GetModelHandle()const 
{
	return farm->GetModelHandle();
}