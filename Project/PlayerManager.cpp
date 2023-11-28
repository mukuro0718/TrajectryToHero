//===========================================================================
//@brief �I�u�W�F�N�g�x�[�X�N���X / ���
//===========================================================================
#include"PlayerManager.h"
#include"SwordGirl.h"
#include"Common.h"
#include"Load.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerManager::PlayerManager()
{
	auto& load = Load::GetInstance();
	load.GetPlayerData(&model);
	player = new SwordGirl(model);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerManager::~PlayerManager()
{
	Final();
}
void PlayerManager::Init()
{
	//�v���C���[�̃X�e�[�^�X�̐ݒ�
	player->Init();
}
/// <summary>
/// �X�V
/// </summary>
void PlayerManager::Update(const VECTOR _cameraToPlayer)
{
	player->Attack();
	player->Move(_cameraToPlayer);
	player->Update();
}
/// <summary>
/// �`��
/// </summary>
void PlayerManager::Draw()
{
	player->Draw();
}
/// <summary>
/// �폜
/// </summary>
void PlayerManager::Final()
{
	// �R�c���f���̕`��
	delete(player);
}
/// <summary>
/// ���x���A�b�v���j���[���\������Ă�����ق��̍X�V�������~�߂�
/// </summary>
/// <returns>true/false</returns>
//bool PlayerManager::IsStoppingUpdate()
//{
//	return player->IsStoppingUpdate();
//}