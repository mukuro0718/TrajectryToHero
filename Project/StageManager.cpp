//===========================================================================
//@brief ステージマネージャー/管理
//===========================================================================

#include"StageManager.h"
#include"FarmStage.h"
#include"Load.h"
/// <summary>
/// コンストラクタ
/// </summary>
StageManager::StageManager()
{
	farm = NULL;
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
void StageManager::Create()
{
	//インスタンスの生成
	farm = new FarmStage(farmStageData);
}
/// <summary>
/// 更新
/// </summary>
void StageManager::Update()
{
	farm->Update();
}
/// <summary>
/// 管理するすべてのオブジェクトを描画
/// </summary>
void StageManager::Draw()
{
	farm->Draw();
}
/// <summary>
/// 削除
/// </summary>
void StageManager::Delete()
{
	delete(farm);//地面の削除
}
const int StageManager::GetModelHandle()const 
{
	return farm->GetModelHandle();
}