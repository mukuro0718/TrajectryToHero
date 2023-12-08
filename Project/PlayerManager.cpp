//===========================================================================
//@brief �I�u�W�F�N�g�x�[�X�N���X / ���
//===========================================================================
#include"PlayerManager.h"
#include"SwordGirl.h"
#include"Common.h"
#include"Load.h"
#include"BlurScreen.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerManager::PlayerManager()
: blur(nullptr)

{
	auto& load = Load::GetInstance();
	load.GetPlayerData(&model);
	player = new SwordGirl(model);
	blur = new BlurScreen();
	blur->Init(240, -2, -2, -2, -2);
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
void PlayerManager::Update()
{
	player->CountInvincibleTimer();
	player->Update();
	player->AnimChange();
}
/// <summary>
/// �ړ�
/// </summary>
void PlayerManager::Move(const VECTOR _cameraToPlayer)
{
	player->Move(_cameraToPlayer);
}
/// <summary>
/// �U��
/// </summary>
void PlayerManager::Attack()
{
	player->Attack();
}
/// <summary>
/// �`��
/// </summary>
void PlayerManager::Draw()
{
	if (player->GetIsAttack())
	{
		blur->PreRenderBlurScreen();
	}
	player->Draw();
	player->DrawMenu();
	if (player->GetIsAttack())
	{
		blur->PostRenderBlurScreen();
	}

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
/// �ړ��ʕ␳
/// </summary>
void PlayerManager::FixMoveVec(const VECTOR _fixVec)
{
	player->FixMoveVec(_fixVec);
}
/// <summary>
/// HP�v�Z
/// </summary>
void PlayerManager::CalcHP(const float _atk)
{
	//HP�v�Z
	player->CalcHP(_atk);
}
/// <summary>
/// ���x���A�b�v����
/// </summary>
void PlayerManager::CalcExp(const float _expToGive)
{
	player->CalcExp(_expToGive);
}
/// <summary>
/// �X�e�[�^�X�X�V
/// </summary>
void PlayerManager::StatusUpdate()
{
	player->StatusUpdate();
}
void PlayerManager::DrawShadow(const int _stageModelHandle)
{
	player->DrawShadow(_stageModelHandle,player->GetPos(),SHADOW_HEIGHT,SHADOW_SIZE);
}