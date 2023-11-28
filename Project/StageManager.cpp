//===========================================================================
//@brief �X�e�[�W�}�l�[�W���[/�Ǘ�
//===========================================================================

#include"StageManager.h"
#include"Ground.h"
#include"Load.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
StageManager::StageManager()
{
	ground = nullptr;
	//���f���̃��[�h
	auto& load = Load::GetInstance();
	load.GetStageData(&model);
	CreateStage();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
StageManager::~StageManager()
{
	DestroyStage();
}
/// <summary>
/// ����
/// </summary>
void StageManager::CreateStage()
{
	//�C���X�^���X�̐���
	ground = new Ground(model);
}
/// <summary>
/// �X�V
/// </summary>
void StageManager::Update()
{
	ground->Update();
}
/// <summary>
/// �Ǘ����邷�ׂẴI�u�W�F�N�g��`��
/// </summary>
void StageManager::Draw()
{
	ground->Draw();
}
/// <summary>
/// �폜
/// </summary>
void StageManager::DestroyStage()
{
	delete(ground);//�n�ʂ̍폜
}