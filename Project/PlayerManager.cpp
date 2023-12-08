//===========================================================================
//@brief オブジェクトベースクラス / 基底
//===========================================================================
#include"PlayerManager.h"
#include"SwordGirl.h"
#include"Common.h"
#include"Load.h"
#include"BlurScreen.h"
/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
PlayerManager::~PlayerManager()
{
	Final();
}
void PlayerManager::Init()
{
	//プレイヤーのステータスの設定
	player->Init();
}
/// <summary>
/// 更新
/// </summary>
void PlayerManager::Update()
{
	player->CountInvincibleTimer();
	player->Update();
	player->AnimChange();
}
/// <summary>
/// 移動
/// </summary>
void PlayerManager::Move(const VECTOR _cameraToPlayer)
{
	player->Move(_cameraToPlayer);
}
/// <summary>
/// 攻撃
/// </summary>
void PlayerManager::Attack()
{
	player->Attack();
}
/// <summary>
/// 描画
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
/// 削除
/// </summary>
void PlayerManager::Final()
{
	// ３Ｄモデルの描画
	delete(player);
}
/// <summary>
/// 移動量補正
/// </summary>
void PlayerManager::FixMoveVec(const VECTOR _fixVec)
{
	player->FixMoveVec(_fixVec);
}
/// <summary>
/// HP計算
/// </summary>
void PlayerManager::CalcHP(const float _atk)
{
	//HP計算
	player->CalcHP(_atk);
}
/// <summary>
/// レベルアップ処理
/// </summary>
void PlayerManager::CalcExp(const float _expToGive)
{
	player->CalcExp(_expToGive);
}
/// <summary>
/// ステータス更新
/// </summary>
void PlayerManager::StatusUpdate()
{
	player->StatusUpdate();
}
void PlayerManager::DrawShadow(const int _stageModelHandle)
{
	player->DrawShadow(_stageModelHandle,player->GetPos(),SHADOW_HEIGHT,SHADOW_SIZE);
}