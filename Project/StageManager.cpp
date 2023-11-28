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
	ground = NULL;
	//���f���̃��[�h
	auto& load = Load::GetInstance();
	load.GetStageData(&model);
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
void StageManager::Delete()
{
	delete(ground);//�n�ʂ̍폜
}