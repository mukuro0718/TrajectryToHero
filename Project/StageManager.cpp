//===========================================================================
//@brief �X�e�[�W�}�l�[�W���[/�Ǘ�
//===========================================================================

#include"StageManager.h"
#include"FarmStage.h"
#include"Bonfire.h"
#include"Load.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
StageManager::StageManager()
	: farm(nullptr)
	, bonfire(nullptr)
{
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
	bonfire = new Bonfire();
}
/// <summary>
/// �X�V
/// </summary>
void StageManager::Update(const int _playerLv)
{
	farm->Update(_playerLv);
}
/// <summary>
/// �Ǘ����邷�ׂẴI�u�W�F�N�g��`��
/// </summary>
void StageManager::Draw(const bool _isFarm)
{
	farm->Draw(_isFarm);
	bonfire->Draw();
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
const VECTOR StageManager::GetBonfirePos()const
{
	return bonfire->GetPos();
}
const bool StageManager::GetIsShowGate()const
{
	return farm->GetIsShowGate();
}
const VECTOR StageManager::GetGatePos()const
{
	return farm->GetGatePos();
}
