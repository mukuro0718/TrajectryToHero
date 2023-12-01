//===========================================================================
//@brief オブジェクトベースクラス / 基底
//===========================================================================
#include"PlayerManager.h"
#include"SwordGirl.h"
#include"Common.h"
#include"Load.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerManager::PlayerManager()
{
	auto& load = Load::GetInstance();
	load.GetPlayerData(&model);
	player = new SwordGirl(model);
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
	player->Draw();
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
/// レベルアップメニューが表示されていたらほかの更新処理を止める
/// </summary>
/// <returns>true/false</returns>
//bool PlayerManager::IsStoppingUpdate()
//{
//	return player->IsStoppingUpdate();
//}