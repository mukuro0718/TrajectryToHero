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
	ground = NULL;
	//モデルのロード
	auto& load = Load::GetInstance();
	load.GetStageData(&model);
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
void StageManager::Delete()
{
	delete(ground);//地面の削除
}