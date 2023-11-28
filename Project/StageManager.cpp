//===========================================================================
//@brief ステージマネージャー/管理
//===========================================================================

#include"StageManager.h"
#include"Ground.h"
#include"Load.h"
/// <summary>
/// コンストラクタ
/// </summary>
StageManager::StageManager()
{
	ground = nullptr;
	//モデルのロード
	auto& load = Load::GetInstance();
	load.GetStageData(&model);
	CreateStage();
}
/// <summary>
/// デストラクタ
/// </summary>
StageManager::~StageManager()
{
	DestroyStage();
}
/// <summary>
/// 生成
/// </summary>
void StageManager::CreateStage()
{
	//インスタンスの生成
	ground = new Ground(model);
}
/// <summary>
/// 更新
/// </summary>
void StageManager::Update()
{
	ground->Update();
}
/// <summary>
/// 管理するすべてのオブジェクトを描画
/// </summary>
void StageManager::Draw()
{
	ground->Draw();
}
/// <summary>
/// 削除
/// </summary>
void StageManager::DestroyStage()
{
	delete(ground);//地面の削除
}