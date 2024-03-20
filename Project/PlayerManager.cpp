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
const void PlayerManager::Init()
{
	//�v���C���[�̃X�e�[�^�X�̐ݒ�
	player->Init();
}
/// <summary>
/// �X�V
/// </summary>
const void PlayerManager::Update()
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
const void PlayerManager::Move(const VECTOR _cameraToPlayer)
{
	player->Move(_cameraToPlayer);
}
/// <summary>
/// �U��
/// </summary>
const void PlayerManager::Attack()
{
	player->Attack();
}
/// <summary>
/// �`��
/// </summary>
const void PlayerManager::Draw(const VECTOR _bonfirePos)
{
	player->Draw();
	player->DrawUI();
	opeUI->Draw(_bonfirePos,player->GetPos());
}
const void PlayerManager::DrawMenu()
{
	player->DrawMenu();
}
/// <summary>
/// �폜
/// </summary>
const void PlayerManager::Final()
{
	// �R�c���f���̕`��
	delete(player);
}
/// <summary>
/// �ړ��ʕ␳
/// </summary>
const void PlayerManager::FixMoveVec(const VECTOR _fixVec)
{
	player->FixMoveVec(_fixVec);
}
/// <summary>
/// HP�v�Z
/// </summary>
const void PlayerManager::CalcHP(const float _atk,const VECTOR _attackerPos)
{
	//HP�v�Z
	player->CalcHP(_atk,_attackerPos);
}
/// <summary>
/// ���x���A�b�v����
/// </summary>
const void PlayerManager::CalcExp(const float _expToGive)
{
	player->CalcExp(_expToGive);
}
/// <summary>
/// �X�e�[�^�X�X�V
/// </summary>
const void PlayerManager::StatusUpdate(const VECTOR _bonfirePos)
{
	player->StatusUpdate(_bonfirePos);
}
const void PlayerManager::DrawShadow(const int _stageModelHandle)
{
	player->DrawShadow(_stageModelHandle,player->GetPos(),SHADOW_HEIGHT,SHADOW_SIZE);
}
const void PlayerManager::ReSpawn()
{
	player->ReSpawn();
}
const void PlayerManager::PhysicalRecovery()
{
	player->PhysicalRecovery();
}
const void PlayerManager::InitPos() const
{
	player->InitPos();
}
