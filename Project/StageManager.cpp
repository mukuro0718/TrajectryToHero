#include"StageManager.h"
#include"FarmStage.h"
#include"Bonfire.h"
#include"Load.h"
/// <summary>
/// コンストラクタ
/// </summary>
StageManager::StageManager()
	: farm(nullptr)
	, bonfire(nullptr)
{
	//モデルのロード
	auto& load = Load::GetInstance();
	load.GetStageData(&farmStageData);
	Create();
}
/// <summary>
/// デストラクタ
/// </summary>
StageManager::~StageManager()
{
	Delete();
}
/// <summary>
/// 生成
/// </summary>
const void StageManager::Create()
{
	//インスタンスの生成
	farm = new FarmStage(farmStageData);
	bonfire = new Bonfire();
}
/// <summary>
/// 更新
/// </summary>
const void StageManager::Update(const int _playerLv)
{
	farm->Update(_playerLv);
}
/// <summary>
/// 管理するすべてのオブジェクトを描画
/// </summary>
const void StageManager::Draw(const bool _isFarm)
{
	farm->Draw(_isFarm);
	bonfire->Draw();
}
/// <summary>
/// 削除
/// </summary>
const void StageManager::Delete()
{
	if (farm)
	{
		delete(farm);//地面の削除
		farm = nullptr;
	}
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
