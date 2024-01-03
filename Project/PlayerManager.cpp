//===========================================================================
//@brief �I�u�W�F�N�g�x�[�X�N���X / ���
//===========================================================================
#include"PlayerManager.h"
#include"SwordGirl.h"
#include"Common.h"
#include"OperationUI.h"
#include"Load.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerManager::PlayerManager()
	: model(0)
	, frameImage(0)
	, hpImage(0)
	, expImage(0)
	, font(0)
	, player(nullptr)
	, opeUI(nullptr)
	, isDrawImg(false)
{
	auto& load = Load::GetInstance();
	load.GetPlayerData(&model,&frameImage,&hpImage,&expImage,&font);
	player = new SwordGirl(model,frameImage,hpImage,expImage,font);
	opeUI = new OperationUI();
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
	opeUI->Update(player->GetIsMove());
	player->UpdateUI();
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
	player->Draw();
	player->DrawMenu();
	player->DrawUI();
	opeUI->Draw();
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