#include"PlayerManager.h"
#include"SwordGirl.h"
#include"Common.h"
#include"OperationUI.h"
#include"Load.h"
/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
PlayerManager::~PlayerManager()
{
	Final();
}
const void PlayerManager::Init()
{
	//プレイヤーのステータスの設定
	player->Init();
}
/// <summary>
/// 更新
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
/// 移動
/// </summary>
const void PlayerManager::Move(const VECTOR _cameraToPlayer)
{
	player->Move(_cameraToPlayer);
}
/// <summary>
/// 攻撃
/// </summary>
const void PlayerManager::Attack()
{
	player->Attack();
}
/// <summary>
/// 描画
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
/// 削除
/// </summary>
const void PlayerManager::Final()
{
	// ３Ｄモデルの描画
	delete(player);
}
/// <summary>
/// 移動量補正
/// </summary>
const void PlayerManager::FixMoveVec(const VECTOR _fixVec)
{
	player->FixMoveVec(_fixVec);
}
/// <summary>
/// HP計算
/// </summary>
const void PlayerManager::CalcHP(const float _atk,const VECTOR _attackerPos)
{
	//HP計算
	player->CalcHP(_atk,_attackerPos);
}
/// <summary>
/// レベルアップ処理
/// </summary>
const void PlayerManager::CalcExp(const float _expToGive)
{
	player->CalcExp(_expToGive);
}
/// <summary>
/// ステータス更新
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
